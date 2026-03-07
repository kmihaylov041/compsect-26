#include <stdio.h>
#include <ctype.h>
#include <string.h>

char decrypt_char(char c, int key) {

    if (isupper(c))
        return (c - 'A' - key + 26) % 26 + 'A';

    return c;
}

void decrypt_text(char *text, int key) {

    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", decrypt_char(text[i], key));
    }

    printf("\n");
}

int main() {

    char text[] = "WKLV LV D VHFUHW PHVVDJH";

    printf("Brute force results:\n\n");

    for (int key = 1; key <= 25; key++) {

        printf("Key %d: ", key);
        decrypt_text(text, key);
    }

    return 0;
}