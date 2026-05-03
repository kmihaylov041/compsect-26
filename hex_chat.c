#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>

void handleErrors() {
    printf("Error\n");
    exit(1);
}

void to_hex(unsigned char *in, int len, char *out) {
    for(int i=0;i<len;i++)
        sprintf(out + i*2, "%02X", in[i]);
}

int from_hex(char *in, unsigned char *out) {
    int len = strlen(in)/2;
    for(int i=0;i<len;i++)
        sscanf(in + 2*i, "%2hhx", &out[i]);
    return len;
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

int main() {

    unsigned char key[16] = "0123456789012345";
    unsigned char iv[16]  = "1234567890123456";

    char input[256];

    while(1) {

        printf("Enter message: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if(strcmp(input, "EXIT") == 0)
            break;

        unsigned char ciphertext[256];
        char hex[512];

        int clen = encrypt((unsigned char*)input, strlen(input),
                           key, iv, ciphertext);

        to_hex(ciphertext, clen, hex);

        printf("[NETWORK SEND]: %s\n", hex);

        unsigned char received_bin[256];
        int bin_len = from_hex(hex, received_bin);

        unsigned char decrypted[256];
        int dlen = decrypt(received_bin, bin_len, key, iv, decrypted);
        decrypted[dlen] = '\0';

        printf("[NETWORK RECV]: %s\n\n", decrypted);
    }

    return 0;
}