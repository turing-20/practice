#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#define KEY_SIZE 10000

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Not enough arguments, Please give private key, encrypted file and output file\n");
        return 0;
    }
    char filename[100];
    bzero(filename, sizeof(filename));

    strcpy(filename, argv[1]);

    FILE *fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("Unable to open file %s \n", filename);
        return 0;
    }
    RSA *rsa = RSA_new();

    rsa = PEM_read_RSAPrivateKey(fp, &rsa, NULL, NULL);

    char decrypted[8 * KEY_SIZE];
    bzero(decrypted, sizeof(decrypted));

    char data[8 * KEY_SIZE];
    bzero(data, sizeof(data));

    FILE *fdata;
    if ((fdata = fopen(argv[2], "rb")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    fseek(fdata, 0, SEEK_END);
    int length = ftell(fdata);
    fseek(fdata, 0, SEEK_SET);
    fread(data, 1, length, fdata);

    int result;
    if ((result = RSA_private_decrypt(RSA_size(rsa), data, decrypted, rsa, RSA_PKCS1_PADDING)) == -1)
    {
        printf("decryption failed %d  %ld \n", length, strlen(data));
    }

    FILE *ouput;

    if ((ouput = fopen(argv[3], "w")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    fwrite(decrypted, strlen(decrypted), 1, ouput);

    return 0;
}
