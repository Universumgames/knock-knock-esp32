#include "lock_open.h"
// #include "driver/gpio.h"
#include "DigitalGPIO.h" // Datei von Tom PINMODE, DIGITALWRITE, DIGITALREAD

void openLock(void)
{
    setupDigitalGPIO(GPIO_NUM_2, GPIO_MODE_OUTPUT);
}