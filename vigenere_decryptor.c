#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decrypt_vigenere(char *cipher, char *key, char *plain) {
    int key_len = strlen(key);
    int j = 0;

    for (int i = 0; cipher[i] != '\0'; i++) {

        if (isalpha(cipher[i])) {

            char C = toupper(cipher[i]) - 'A';
            char K = toupper(key[j % key_len]) - 'A';

            char P = (C - K + 26) % 26;

            plain[i] = P + 'A';

            j++;
        }
        else {
            plain[i] = cipher[i];
        }
    }

    plain[strlen(cipher)] = '\0';
}

int main() {

    FILE *f1 = fopen("encrypted.txt", "r");
    FILE *f2 = fopen("key.txt", "r");

    if (!f1 || !f2) {
        printf("Error opening files\n");
        return 1;
    }

    char cipher[1000];
    char key[100];
    char plain[1000];

    fgets(cipher, sizeof(cipher), f1);
    fgets(key, sizeof(key), f2);

    key[strcspn(key, "\n")] = 0;

    decrypt_vigenere(cipher, key, plain);

    FILE *out = fopen("decrypted.txt", "w");

    fprintf(out, "%s", plain);

    fclose(f1);
    fclose(f2);
    fclose(out);

    printf("Decryption complete. Check decrypted.txt\n");

    return 0;
}