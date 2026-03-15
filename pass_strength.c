#include <stdio.h>
#include <string.h>
#include <ctype.h>

int analyze_password(const char *pass) {

    int score = 0;

    int has_lower = 0;
    int has_upper = 0;
    int has_digit = 0;
    int has_special = 0;

    char *weak[] = {"password", "123456", "admin"};

    int weak_count = 3;

    int len = strlen(pass);

    score += len;

    for (int i = 0; i < len; i++) {

        if (islower(pass[i])) has_lower = 1;
        else if (isupper(pass[i])) has_upper = 1;
        else if (isdigit(pass[i])) has_digit = 1;
        else has_special = 1;
    }

    if (has_lower) score += 10;
    if (has_upper) score += 10;
    if (has_digit) score += 15;
    if (has_special) score += 20;

    for (int i = 0; i < weak_count; i++) {

        if (strcmp(pass, weak[i]) == 0) {
            score -= 20;
        }
    }

    if (score > 100) score = 100;
    if (score < 0) score = 0;

    return score;
}

int main() {

    char password[100];

    printf("Enter password: ");
    scanf("%s", password);

    int result = analyze_password(password);

    printf("Password score: %d/100\n", result);

    return 0;
}