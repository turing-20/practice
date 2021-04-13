#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

SSL_CTX* InitCTX(){
	SSL_METHOD *method;
	SSL_CTX *ctx;

	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	method = TLSv1_2_client_method();
	ctx = SSL_CTX_new(method);

	if(ctx == NULL){
		ERR_print_errors_fp(stderr);
		abort();
	}

	return ctx;
}

int main(int argc, char const *argv[]) {

	int socket_fd;
	int err;
	int portno;
	char url[80];
	char domain[80];
	char path[100];
	char filename[80];
	char request[200];
	char server_response[5000];
	char* header_end;
	int header_len;
	struct sockaddr_in sadr; 
	SSL_CTX *ctx;
	SSL *ssl;

	// clear every buffer
	bzero(url, 80);
	bzero(domain, 80);
	bzero(request, 200);
	bzero(server_response, 5000);

	// input arguements domain name, filename
	if(argc != 2){
		printf("Incorrect number of arguements passed\n");
		exit(0);
	}

	// Take inputs
	strcpy(url, argv[1]);

	// check if url is https
	char *is_https = strstr(url, "https://");
	if(is_https != NULL){
		// Initialize ssl
		SSL_library_init();
		ctx = InitCTX();
	}

	// get domain from url
	char *prefix_end = strstr(url, "https://");
	if(prefix_end == NULL){
		prefix_end = strstr(url, "http://");
		prefix_end += 7;
	}
	else{
		prefix_end += 8;
	}


	char *domain_end = strstr(prefix_end, "/");
	if(domain_end == NULL){
		strcat(url, "/");
		domain_end = strstr(prefix_end, "/");
	}

	strncpy(domain, prefix_end, domain_end - prefix_end);

	// get path from url
	strcpy(path, domain_end);

	// get host address from domain
	struct hostent *host_addr = 0;
	host_addr = gethostbyname(domain);
	if(host_addr == NULL){
		herror("Failure in gethostbyname");
		exit(0);
	}

	// socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1){
		perror("Socket Failed"); 
		exit(0);
	}

	sadr.sin_addr = *((struct in_addr *) host_addr -> h_addr_list[0]);
	sadr.sin_family = AF_INET; 
	if(is_https == NULL)
		sadr.sin_port = htons(80); // https port
	else
		sadr.sin_port = htons(443);

	// connect to server
	err = connect(socket_fd, (struct sockaddr *)&sadr, sizeof(sadr));
	if(err < 0){
		perror("Server Cannot be reached");
		exit(0);
	}

	if(is_https != NULL){
		ssl = SSL_new(ctx);
		SSL_set_fd(ssl, socket_fd);

		if(SSL_connect(ssl) == -1){
			SSL_get_error(ssl, -1);
			ERR_print_errors_fp(stdout);
			printf("SSL connection error\n");
			exit(0);
		}
	}

	char get_template[] = "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n";
	sprintf(request, get_template, path, domain);

	printf("GET reqeust sent to server\n%s", request);

	if(is_https == NULL)
		write(socket_fd, request, 200); 
	else
		SSL_write(ssl, request, 200);

	bzero(request, 200);

	if(is_https == NULL)
		err = read(socket_fd, server_response, 5000);
	else
		err = SSL_read(ssl, server_response, 5000);

	// check if header code is not 200
	char* http_version = strstr(server_response, "HTTP/1.1");
	if(http_version == NULL){
		printf("http not found in header\n");
		exit(0);
	}


	char response_code[10]; 
	strncpy(response_code, http_version + 9, 4);
	if(atoi(response_code) != 200){
		printf("Some error occured. Response code %d\n", atoi(response_code));
		exit(0);
	}

	header_len = 0;
	header_end = strstr(server_response, "\r\n\r\n");
	if(header_end != NULL){
		header_end += 4;
		header_len = header_end - server_response;
	}

	/*
	// printing header for debugging
	for(int i = 0; i < header_len; i++){
		printf("%c", server_response[i]);
	}
	*/

	FILE *fptr;
	// find last occurence of forward slash and consider the next part as filename
	// remove the leading forward slash
	char output_filename[100];
	bzero(output_filename, 100);
	char* filename_start = strrchr(path, '/');
	if(filename_start == NULL){
		exit(0);
	}

	filename_start += 1;

	strcpy(output_filename, filename_start);

	if(strcmp(output_filename, "") == 0){
		strcpy(output_filename, "Server Response File");
	}

	fptr = fopen(output_filename, "w");
	if(fptr == NULL){
		printf("file opening failed\n");
	}

	printf("Saving data in file %s\n", output_filename);

	while(1){
		for(int i = header_len; i < err; i++){
			fprintf(fptr, "%c", server_response[i]);
		}

		bzero(server_response, 5000);
		header_len = 0;
		if(is_https == NULL)
			err = read(socket_fd, server_response, 5000);
		else
			err = SSL_read(ssl, server_response, 5000);
		if(err <= 0)
			break;
	}

	fclose(fptr);
	if(is_https){
		SSL_CTX_free(ctx);
	}
	close(socket_fd);
	exit(0);

} 
