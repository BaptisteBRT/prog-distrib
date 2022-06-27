#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void delay(unsigned milliseconds)
{
    clock_t pause;
    clock_t start;
    
    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    start = clock();

    while ((clock() - start) < pause);
}


void rotationMoteur(float tempsSec)
{

    clock_t time1, time2;

    if(tempsSec == 0) return;

    //TODO : ajouter la fonction démarrage servo

    tempsSec = tempsSec *1000;

    delay(tempsSec);
    
    //TODO : ajouter la fonction arrêt servo

}