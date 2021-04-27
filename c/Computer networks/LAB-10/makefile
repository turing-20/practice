all: compile run_server
compile: server.out client.out
keys: private_key public_key

run_server: server.out
	./server.out 8082
run_client_1: client.out
	./client.out 127.0.0.1 8082 private_key_1.pem public_key_2.pem
run_client_2: client.out
	./client.out 127.0.0.1 8082 private_key_2.pem public_key_1.pem
	
client.out: client.c
	gcc client.c -lssl -lcrypto -o client.out

server.out: server.c
	gcc server.c -lssl -lcrypto -o server.out

private_key:
	openssl genrsa -out private_key_1.pem 4096
	openssl genrsa -out private_key_2.pem 4096
public_key:
	openssl rsa -in private_key_1.pem -outform PEM -pubout -out public_key_1.pem
	openssl rsa -in private_key_2.pem -outform PEM -pubout -out public_key_2.pem

clean:
	rm *.out