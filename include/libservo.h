#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>

int run (void)
{
  if (wiringPiSetup() == -1)
    exit (1) ;

  pinMode(1,PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(1920);
  pwmSetRange(200);
  
  // SI TOURNE DANS LE MAUVAIS SENS, METTRE (1,10)
  pwmWrite(1,20); //tourne dans un sens
  
  return 0;
}

int stop (void)
{
  if (wiringPiSetup() == -1)
    exit (1) ;

  pinMode(1,PWM_OUTPUT);
  pwmWrite(1,0); //stop
    
  return 0;
}

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
    run();

    tempsSec = tempsSec *1000;

    delay(tempsSec);
    
    //TODO : ajouter la fonction arrêt servo
    stop();

}
