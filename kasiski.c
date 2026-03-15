#include <stdio.h>
#include <string.h>

int main() {

    char text[2000];

    FILE *f = fopen("encrypted.txt", "r");

    if (!f) {
        printf("File error\n");
        return 1;
    }

    fgets(text, sizeof(text), f);
    fclose(f);

    int len = strlen(text);

    for (int i = 0; i < len - 2; i++) {

        char trigram[4];

        strncpy(trigram, &text[i], 3);
        trigram[3] = '\0';

        for (int j = i + 1; j < len - 2; j++) {

            if (strncmp(trigram, &text[j], 3) == 0) {

                printf("Found \"%s\": Pos %d & Pos %d -> Distance: %d\n",
                       trigram, i, j, j - i);
            }
        }
    }

    return 0;
}