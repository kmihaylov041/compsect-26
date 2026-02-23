#include <stdio.h>
#include <ctype.h> 
char caesar_encrypt_char(char p, int k) {
if (isupper(p)) {
    return ( (p - 'A' + k) % 26 ) + 'A';
}
    return p;
}
char caesar_decrypt_char(char c, int k) {
if (isupper(c)) {
    return((c - 'A' - k + 26) % 26) + 'A';
}
    return c;
}
int main() {
    char text[] = "HELLO";
    int key = 3;
    printf("%s\n", text);
    for (int i = 0; text[i] != '\0'; i++) {
    char e = caesar_encrypt_char(text[i], key);
    printf("%c", e);
    text[i] = e;
    }
    printf("\n");
    for (int i = 0; text[i] != '\0'; i++) {
    char d = caesar_decrypt_char(text[i], key);
    printf("%c", d);
    text[i] = d;
    }
}
