#include "libdatabase.h"
#include "libservo.h"
#include "wiringPi.h"

int identiteChat(char tagAnimal[MAX_ATR_SIZE*3+1])
{
    // chat existe-t-il ?
    int idAnimal = getIdAnimal(tagAnimal);

    if(idAnimal == -1) idAnimal=newTag(tagAnimal);

    return idAnimal;
}

void delivreCroquettes(int idAnimal)
{
    struct objetDistrib objet = getQuantiteTotale(idAnimal);

    if(objet.qte == 0) return;

    printf("%s",objet.heure.total);

    float qteTotale = objet.qte;

    float qteParSeconde = getQuantiteParSec();

    printf("\nQuantité (g): %f\nDébit (g/sec): %f",qteTotale,qteParSeconde);

    float tempsRota = qteTotale/qteParSeconde;

    printf("\nTemps rota: %f\n", tempsRota);

    rotationMoteur(tempsRota);

    updateDB(idAnimal, objet);
}



void onTagOn(char tagAnimal[MAX_ATR_SIZE*3+1])
{

    int idAnimal = identiteChat(tagAnimal);
    delivreCroquettes(idAnimal);

}
