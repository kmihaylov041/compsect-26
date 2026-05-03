#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>

void handleErrors() {
    printf("OpenSSL error\n");
    exit(1);
}

int encrypt(unsigned char *plaintext, int plaintext_len,
            unsigned char *key, unsigned char *iv,
            unsigned char *ciphertext) {

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len, ciphertext_len;

    if(!ctx) handleErrors();

    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
        handleErrors();

    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len,
            unsigned char *key, unsigned char *iv,
            unsigned char *plaintext) {

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len, plaintext_len;

    if(!ctx) handleErrors();

    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
        handleErrors();

    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return plaintext_len;
}

int main() {

    unsigned char key[16] = "0123456789012345";
    unsigned char iv[16]  = "1234567890123456";

    unsigned char *text = (unsigned char *)"CyberSecurity Lab";

    unsigned char ciphertext[128];
    unsigned char decrypted[128];

    printf("Original: %s\n", text);

    int clen = encrypt(text, strlen((char*)text), key, iv, ciphertext);

    printf("Encrypted: ");
    for(int i=0;i<clen;i++) printf("%02x", ciphertext[i]);
    printf("\n");

    int dlen = decrypt(ciphertext, clen, key, iv, decrypted);
    decrypted[dlen] = '\0';

    printf("Decrypted: %s\n", decrypted);

    return 0;
}