#include "mini.h"

uint32_t max(uint32_t numberA, uint32_t numberB) {
    if (numberA > numberB) {
        return numberA;
    }
    return numberB;
}

uint32_t min(uint32_t numberA, uint32_t numberB) {
    if (numberA < numberB) {
        return numberA;
    }
    return numberB;
}