#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned char rc4_second_byte(unsigned char *key, int keylen) {
    unsigned char S[256];
    int i, j = 0;
    unsigned char temp;

    for (i = 0; i < 256; i++) S[i] = i;

    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % keylen]) % 256;

        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    i = 0;
    j = 0;

    unsigned char byte;

    for (int k = 0; k < 2; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        byte = S[(S[i] + S[j]) % 256];
    }

    return byte; 
}

int main() {
    int count_zero = 0;
    int tests = 100000;

    srand(time(NULL));

    for (int t = 0; t < tests; t++) {

        unsigned char key[16];

        for (int i = 0; i < 16; i++) {
            key[i] = rand() % 256;
        }

        unsigned char second = rc4_second_byte(key, 16);

        if (second == 0x00) {
            count_zero++;
        }
    }

    printf("Zero count: %d\n", count_zero);
    printf("Probability: %f\n", (double)count_zero / tests);

    return 0;
}