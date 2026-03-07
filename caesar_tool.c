#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char encrypt_char(char c, int key) {
    if (isupper(c))
        return (c - 'A' + key) % 26 + 'A';

    if (islower(c))
        return (c - 'a' + key) % 26 + 'a';

    return c;
}

char decrypt_char(char c, int key) {
    if (isupper(c))
        return (c - 'A' - key + 26) % 26 + 'A';

    if (islower(c))
        return (c - 'a' - key + 26) % 26 + 'a';

    return c;
}

int main(int argc, char *argv[]) {

    if (argc != 5) {
        printf("Usage:\n");
        printf("./caesar_tool -e input.txt key.txt output.txt\n");
        printf("./caesar_tool -d input.txt key.txt output.txt\n");
        return 1;
    }

    char mode = argv[1][1];

    FILE *input = fopen(argv[2], "r");
    FILE *keyFile = fopen(argv[3], "r");
    FILE *output = fopen(argv[4], "w");

    if (input == NULL || keyFile == NULL || output == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int key;
    fscanf(keyFile, "%d", &key);

    char c;

    while ((c = fgetc(input)) != EOF) {

        if (mode == 'e')
            c = encrypt_char(c, key);

        else if (mode == 'd')
            c = decrypt_char(c, key);

        else {
            printf("Invalid mode.\n");
            return 1;
        }

        fputc(c, output);
    }

    fclose(input);
    fclose(keyFile);
    fclose(output);

    printf("Operation completed.\n");

    return 0;
}