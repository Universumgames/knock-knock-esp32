#include "Serial.h"


int app_main(){
    initSerial();

    int erste = 0;
    scanf("%d", &erste);
        if (erste == 1)
        {
            printf("Jovan arnaut\n");
        }


    int zweite = 1;
    scanf("%d", &zweite);
        if (zweite != 1)
        {
            printf("%2x\n", zweite);
        }


    int dritte = 0;
    int primenumbers[54] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251};
    scanf("%d", &dritte);
        if (dritte > 5 || dritte < 255)
        {
            for (int i = 0; i < 50; i++)
            {
                if (primenumbers[i] > dritte)
                {
                    printf("%d\n", primenumbers[i]);
                    break;
                }
            }
        }


    char monthdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char vier1[32];
    char vier2[32];
    scanf("%s", vier1);
    scanf("%s", vier2);

    int day = 0;
    int month = 0;
    int gesamt = 0;

    for (int i = 0; i < 31; i++)
    {
        if (vier1[i] == '*')
        {
            day++;
        }
        if (vier2[i] == '.')
        {
            month++;
        }
    }

    for (int i = month ; i <= 12; i++)
    {   
        if (i == month)
        {
            gesamt = gesamt + (monthdays[i-1] - day);
        }
        else
        {   
            if (i == 12)
            {
                gesamt = gesamt + 25;
                break;
            }
            gesamt = gesamt + monthdays[i-1];
        }
        
    }
    printf("%d\n", gesamt);
    
    char funf[2];
    scanf("%s", funf);
    int diff = 'J' - funf[0];
    char verschob[6] = "Jovan";
    for (int i = 0; i < 5; i++)
    {
        verschob[i] = verschob[i] - diff;
    }

    printf("%s\n", verschob);

    char sechs[2];
    scanf("%s", sechs);
    if (sechs[0] == '?')
    {
        printf("Das Projekt macht richtig viel Spaß, viel besser als eine stumpfe Klausur :D\n");
    }
    
    
    return 0;
}