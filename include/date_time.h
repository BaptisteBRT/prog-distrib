#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct dateHeure 
{
   int minute;
   int seconde;
   int heure;
   char total[9];
   char date[20];
};



int compare_dates (struct dateHeure d1, struct dateHeure d2)
{
    if (d1.heure < d2.heure)
       return -1;

    else if (d1.heure > d2.heure)
       return 1;

    if (d1.heure == d2.heure)
    {
         if (d1.minute<d2.minute)
              return -1;
         else if (d1.minute>d2.minute)
              return 1;
         else if (d1.seconde<d2.seconde)
              return -1;
         else if(d1.seconde>d2.seconde)
              return 1;
         else
              return 0;
    }
}







struct dateHeure dateTime(){

     // variables to store the date and time components
    int hours, minutes, seconds, day, month, year;

    char * sqlDateTime = malloc(20);
    //char sqlDateTime[20];
    char * buffer = malloc(20);
 
    // `time_t` is an arithmetic time type
    time_t now;
 
    // Obtain current time
    // `time()` returns the current time of the system as a `time_t` value
    time(&now);
 
    // Convert to local time format and print to stdout
    //printf("Today is %s", ctime(&now));
 
    // localtime converts a `time_t` value to calendar time and
    // returns a pointer to a `tm` structure with its members
    // filled with the corresponding values
    struct tm *local = localtime(&now);
 
    hours = local->tm_hour;         // get hours since midnight (0-23)
    minutes = local->tm_min;        // get minutes passed after the hour (0-59)
    seconds = local->tm_sec;        // get seconds passed after a minute (0-59)
 
    day = local->tm_mday;            // get day of month (1 to 31)
    month = local->tm_mon + 1;      // get month of year (0 to 11)
    year = local->tm_year + 1900;   // get year since 1900
 
    // print local time
    if (hours < 12) {    // before midday
        //printf("Time is %02d:%02d:%02d am\n", hours, minutes, seconds);
    }
    else {    // after midday
        //printf("Time is %02d:%02d:%02d pm\n", hours - 12, minutes, seconds);
    }
 
    // print the current date
    //printf("Date is: %02d/%02d/%d\n", day, month, year);

    //ltoa(hours,buffer,10);

    sprintf(buffer,"%d",year);

    strcpy(sqlDateTime,buffer);
    strcat(sqlDateTime,"-");

    sprintf(buffer,"%d",month);

    strcat(sqlDateTime,buffer);
    strcat(sqlDateTime,"-");

    sprintf(buffer,"%d",day);

    strcat(sqlDateTime,buffer);
    strcat(sqlDateTime," ");

    sprintf(buffer,"%d",hours);

    strcat(sqlDateTime,buffer);
    strcat(sqlDateTime,":");
    
    sprintf(buffer,"%d",minutes);

    strcat(sqlDateTime,buffer);
    strcat(sqlDateTime,":");

    sprintf(buffer,"%d",seconds);

    strcat(sqlDateTime,buffer);

    //printf("%s",sqlDateTime);

    struct dateHeure d1;
 
    d1.heure = hours;
    d1.minute = minutes;
    d1.seconde = seconds;

    sprintf(d1.total, "%d:%d:%d", d1.heure,d1.minute,d1.seconde);
    sprintf(d1.date,"%s",sqlDateTime);

    return d1;
}

struct dateHeure changeHourTime(struct dateHeure d1, int heure, int minute, int seconde)
{
    d1.heure = heure;
    d1.minute = minute;
    d1.seconde = seconde;
   
    sprintf(d1.total, "%d:%d:%d", d1.heure,d1.minute,d1.seconde);

    return d1;
}