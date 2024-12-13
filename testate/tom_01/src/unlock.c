//
// Created by Tom Arlt on 13.12.24.
//

#include "unlock.h"


int number;

#define FIRSTNAME "Tom"
#define LASTNAME "arlt"
#define NAME FIRSTNAME " " LASTNAME

bool phase01() {
    scanf("%d", &number);
    if (number != 1) return false;
    printf(NAME "\n");
    return true;
}

bool phase02() {
    scanf("%d", &number);
    if (number == 1) return false;
    printf("%0x\n", number);
    return true;
}

#define PRIME_COUNT 55
const int primeNumbers[PRIME_COUNT] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
    127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
    233, 239, 241, 251, 257
};

bool phase03() {
    scanf("%d", &number);
    if (number < 5 || number > 255) return false;
    int nextPrimeIndex = 0;
    for (int i = 0; i < PRIME_COUNT; i++) {
        if (primeNumbers[i] > number) {
            nextPrimeIndex = i;
            break;
        }
    }
    printf("%d\n", primeNumbers[nextPrimeIndex]);
    return true;
}


bool phase04() {
    char daysStars[32] = {0};
    char monthsStars[13] = {0};
    scanf("%s", daysStars);
    scanf("%s", monthsStars);
    int days = strlen(daysStars);
    int months = strlen(monthsStars);
    //printf("Day %d Month %d\n", days, months);
    if (days < 1 || days > 31 || months < 1 || months > 12) return false;
    int daysUntilChristmas = daysUntilDate(months, days, 12, 24);
    printf("%d\n", daysUntilChristmas);
    return true;
}

bool phase05() {
    char chiffre[8];
    scanf("%s", chiffre);
    char chiffreDelta = chiffre[0] - NAME[0];
    char* encrypted = calloc(sizeof(char), strlen(FIRSTNAME) + 1);
    for (int i = 0; i < strlen(FIRSTNAME); i++) {
        encrypted[i] = NAME[i] + chiffreDelta;
    }
    printf("%s\n", encrypted);
    free(encrypted);
    return true;
}

bool phase06() {
    char question;
    scanf("%c", &question);
    if (question != '?') return false;
    printf("Die Vorlesung ist \n");
    return true;
}