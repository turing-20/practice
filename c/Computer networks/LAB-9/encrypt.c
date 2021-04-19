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
        printf("Not enough arguments, Please give public key, input file and encrypted file\n");
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

    rsa = PEM_read_RSA_PUBKEY(fp, &rsa, NULL, NULL);

    char encrypted[8 * KEY_SIZE];
    bzero(encrypted, sizeof(encrypted));

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
    if ((result = RSA_public_encrypt(length, data, encrypted, rsa, RSA_PKCS1_PADDING)) == -1)
    {
        printf("encryption failed\n");
    }

    FILE *ouput;

    if ((ouput = fopen(argv[3], "w")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    fwrite(encrypted, sizeof(encrypted), 1, ouput);

    return 0;
}
