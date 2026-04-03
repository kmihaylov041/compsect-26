#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 256

void rc4_init(unsigned char *S, const unsigned char *key, int keylen) {
    int i, j = 0;
    unsigned char temp;

    for (i = 0; i < N; i++)
        S[i] = i;

    for (i = 0; i < N; i++) {
        j = (j + S[i] + key[i % keylen]) % N;

        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
}

void rc4_crypt(unsigned char *data, int len, const unsigned char *key, int keylen) {
    unsigned char S[N];
    rc4_init(S, key, keylen);

    int i = 0, j = 0, k;
    unsigned char temp;

    for (k = 0; k < len; k++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        unsigned char rnd = S[(S[i] + S[j]) % N];
        data[k] ^= rnd;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s input output key\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "rb");
    if (!fin) {
        perror("Input file error");
        return 1;
    }

    FILE *fout = fopen(argv[2], "wb");
    if (!fout) {
        perror("Output file error");
        fclose(fin);
        return 1;
    }

    // Определяне размер
    fseek(fin, 0, SEEK_END);
    long size = ftell(fin);
    rewind(fin);

    unsigned char *buffer = malloc(size);
    if (!buffer) {
        printf("Memory error\n");
        fclose(fin);
        fclose(fout);
        return 1;
    }

    fread(buffer, 1, size, fin);

    rc4_crypt(buffer, size, (unsigned char *)argv[3], strlen(argv[3]));

    fwrite(buffer, 1, size, fout);

    free(buffer);
    fclose(fin);
    fclose(fout);

    printf("Done.\n");
    return 0;
}