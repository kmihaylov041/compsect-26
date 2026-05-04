#include <stdio.h>
#include <string.h>
#include <crypt.h>
#include <openssl/md5.h>
//#define MD5_DIGEST_LENGTH = 16;

void md5_string (const char *str, char *output) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char*) str, strlen(str), digest);

    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(&output[i*2], "%02x", digest[i]);
    }
}

int main() {
    const char *tar = "9daae68368ac7be2d9902bb79b556c04";
    char input[20];
    char hash[33];

    for (int i = 0; i <= 9999; i++) {
        sprintf(input, "LAB_%04d", i);
    
        md5_string(input, hash);

        if (strcmp(hash, tar) == 0) {
            printf("PIN FOUND: %04d\n", i);
            printf("Full string: %s\n", input);
        }
    }
    printf("PIN Not Found.\n");
}