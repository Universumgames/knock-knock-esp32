#include "Serial.h"
#include "unlock.h"



int app_main(){
    initSerial();

    phase01();
    phase02();
    phase03();
    phase04();
    phase05();
    //phase06();

    return 0;
}