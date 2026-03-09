#include <stdio.h>
#include <string.h>
#include <ctype.h>

void print_histogram(const char *text) {
    int counts[26] = {0};
    int total_letters = 0;
   
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            int index = toupper(text[i]) - 'A';
            counts[index]++;
            total_letters++;
        }
    }
    
    printf("\n--- FREQUENCY HISTOGRAM ---\n");
    
    for (int i = 0; i < 26; i++) {
        if (counts[i] > 0) {
            printf("%c (%3d): ", 'A' + i, counts[i]);
    
    for (int j = 0; j < counts[i]; j++) {
        printf("*");
        }
        printf("\n");
        }
    }
}

int main() {
    char text[] = "Text messaging, or texting, is the act of composing and sending" 
    "electronic messages, typically consisting of alphabetic and numeric characters,"
    "between two or more users of mobile phones, tablet computers, smartwatches, "
    "desktops/laptops, or another type of compatible computer. ";

    print_histogram(text);
}