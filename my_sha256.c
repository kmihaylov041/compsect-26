#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if(!file) {
        printf("Cannot open file\n");
        return 1;
    }

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if(!mdctx) {
        printf("Error creating context\n");
        return 1;
    }

    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);

    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        EVP_DigestUpdate(mdctx, buffer, bytesRead);
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    EVP_DigestFinal_ex(mdctx, hash, &hash_len);

    EVP_MD_CTX_free(mdctx);
    fclose(file);

    for(unsigned int i = 0; i < hash_len; i++) {
        printf("%02x", hash[i]);
    }
    printf("  %s\n", argv[1]);

    return 0;
}