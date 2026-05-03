#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors() {
    printf("Error\n");
    exit(1);
}

int encrypt(unsigned char *plaintext, int plaintext_len,
            unsigned char *key, unsigned char *iv,
            unsigned char *ciphertext) {

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len, ciphertext_len;

    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len,
            unsigned char *key, unsigned char *iv,
            unsigned char *plaintext) {

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len, plaintext_len;

    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
    EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len);
    plaintext_len = len;

    if(EVP_DecryptFinal_ex(ctx, plaintext + len, &len) != 1)
        handleErrors();

    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return plaintext_len;
}

int main(int argc, char *argv[]) {

    if(argc != 5) {
        printf("Usage: %s [enc|dec] in out key\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[2], "rb");
    if(!f) { printf("File error\n"); return 1; }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    unsigned char *input = malloc(size);
    fread(input, 1, size, f);
    fclose(f);

    unsigned char key[16] = {0};
    memcpy(key, argv[4], strlen(argv[4]));

    unsigned char iv[16] = "1234567890123456";

    unsigned char *output = malloc(size + 32);
    int out_len;

    if(strcmp(argv[1], "enc") == 0) {
        out_len = encrypt(input, size, key, iv, output);
    } else {
        out_len = decrypt(input, size, key, iv, output);
    }

    FILE *out = fopen(argv[3], "wb");
    fwrite(output, 1, out_len, out);
    fclose(out);

    free(input);
    free(output);

    return 0;
}