#include "helper.h"

#define MONTHS 12

int daysInMonths[MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int daysUntilDate(int month1, int day1, int month2, int day2){
    int days = 0;
    days += daysInMonths[month1] - day1;
    for (int i = month1 + 1; i < month2; i++){
        days += daysInMonths[i % MONTHS];
    }
    days += day2 - 1;
    return days;
}