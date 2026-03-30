#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char encrypt_char(char c, int key) {
    if(isupper(c)) {
        return (c - 'A' + key) % 26 + 'A';
    }
    else if(islower(c)) {
        return (c - 'a' + key) % 26 + 'a';
    }
    return c;
}

int main() {
    FILE *in, *keyFile, *out;
    int key;
    int c;

    in = fopen("input.txt", "r");
    keyFile = fopen("key.txt", "r");
    out = fopen("output.txt", "w");

    if (!in || !keyFile || !out) {
        printf("Greshka");
    }

    fscanf(keyFile, "%d", &key);
    key = key % 26;

    while((c = fgetc(in)) != EOF) {
        fputc(encrypt_char(c,key), out);
    }

    fclose(in);
    fclose(keyFile);
    fclose(out);

    printf("Done");
    return 0;


}
