#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void caesar_decrypt(char *input, char *output, int key) {

    int len = strlen(input);

    for (int i = 0; i < len; i++) {
        char c = input[i];

        if (isupper(c)) {
            output[i] = (c-'A'-key + 26) % 26 + 'A';
        } else {
            output[i] = c; 
    
        }
    }
    output[len] = '\0';
}
void bruteforce_attack(char *cipher) {
        char buffer[256];
    
        printf("--- BRUTE FORCE REPORT ---");
    
        for (int k = 1; k < 26; k++) {
            caesar_decrypt(cipher, buffer, k);
            printf("[Key %02d]: %s\n", k, buffer);
    
    }
}

int main() {
    char cipher[] = "YVIBZM VM DOT ZVM ADMO VN D OZVXC D TJP V WPO";
    bruteforce_attack(cipher);
}