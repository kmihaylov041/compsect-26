#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>

#define MAX 256

void sha256(const char *input, char outputHex[65]) {

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int len;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();

    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, input, strlen(input));
    EVP_DigestFinal_ex(ctx, hash, &len);

    EVP_MD_CTX_free(ctx);

    for(unsigned int i = 0; i < len; i++)
        sprintf(outputHex + (i * 2), "%02x", hash[i]);

    outputHex[64] = '\0';
}

int main(int argc, char *argv[]) {

    if(argc != 3) {
        printf("Usage: %s shadow.txt dictionary.txt\n", argv[0]);
        return 1;
    }

    FILE *shadow = fopen(argv[1], "r");
    FILE *dict = fopen(argv[2], "r");

    if(!shadow || !dict) {
        printf("File error\n");
        return 1;
    }

    char line[MAX];

    printf("--- Results ---\n");

    while(fgets(line, sizeof(line), shadow)) {

        char user[MAX], hash[MAX];

        sscanf(line, "%[^:]:%s", user, hash);

        int cracked = 0;

        rewind(dict);
        char word[MAX];
        char testHash[65];

        while(fgets(word, sizeof(word), dict)) {

            word[strcspn(word, "\n")] = 0;

            sha256(word, testHash);

            if(strcmp(testHash, hash) == 0) {
                printf("%s : %s (dictionary)\n", user, word);
                cracked = 1;
                break;
            }
        }

        if(!cracked) {

            char pin[5];
            char testHash2[65];

            for(int i = 0; i <= 9999; i++) {

                sprintf(pin, "%04d", i);
                sha256(pin, testHash2);

                if(strcmp(testHash2, hash) == 0) {
                    printf("%s : %s (brute-force)\n", user, pin);
                    cracked = 1;
                    break;
                }
            }
        }

        if(!cracked) {
            printf("%s : [NOT CRACKED]\n", user);
        }
    }

    fclose(shadow);
    fclose(dict);

    return 0;
}