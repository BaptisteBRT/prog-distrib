//
// Created by louis on 24/05/22.
//
#include <stdio.h>
#include "date_time.h"
#include <mysql/mysql.h>

#define MAX_ATR_SIZE 33
#ifndef IOT_DB_CONNECTOR_H
#define IOT_DB_CONNECTOR_H
#endif

#define DB_HOST "localhost"
#define DB_LOGIN "admin"
#define DB_PW "mysql"
#define DB_DB "datadistributeur"


struct objetDistrib{

    float qte;
    struct dateHeure heure;

};

MYSQL * DB_connect(char* addr, char* user, char* password, char* database){
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    if (mysql_real_connect(con, addr, user, password, database, 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    return con;
}

MYSQL_RES * DB_sendQuery(MYSQL *con, char* query){
    mysql_query(con, query);
    return mysql_store_result(con);

}

void DB_close(MYSQL *con){
    mysql_close(con);
}


// RENVOIE -1 si le chat n'existe pas, renvoie le champ idAnimal si il existe
int getIdAnimal(char tagAnimal[MAX_ATR_SIZE*3+1])
{
    // CONNEXION BDD ET RECUPERATION idAnimal
    MYSQL* con = DB_connect(DB_HOST, DB_LOGIN, DB_PW, DB_DB);
    MYSQL_RES *res;
    MYSQL_ROW row;
    char * query = malloc(1500);

    strcpy(query,"SELECT `idAnimal` FROM `Animaux` WHERE `tag` = '");
    strcat(query,tagAnimal);
    strcat(query,"'");

    res = DB_sendQuery(con, query);
    if (mysql_num_rows(res) > 0) 
    {
        row = mysql_fetch_row(res);
        return atoi(row[0]);
    }
    else return -1;
}


struct objetDistrib getQuantiteTotale(int idAnimal)
{
    // CONNEXION BDD ET RECUPERATION idAnimal
    char * query = malloc(1500);
    struct dateHeure heure, midi;
    midi = changeHourTime(midi,12,0,0);

    heure = dateTime();

    struct objetDistrib objet;
    objet.heure = heure;

    char * buffer = malloc(10);
    sprintf(buffer, "%d", idAnimal);

    strcpy(query,"SELECT SUM(quantite) FROM `Programme` WHERE `idAnimal` = '");
    strcat(query,buffer);
    strcat(query,"' AND `heure` BETWEEN ");


    if(compare_dates(heure,midi) >= 0){

        //printf("ICI");
        strcat(query,"'12:00:00' AND '");
        strcat(query,heure.total);

    }
    else{

        //printf("ICI");
        strcat(query,"'00:00:00' AND '");
        strcat(query,heure.total);
        
    }
    strcat(query, "' AND `distribue` = 0");

    MYSQL* con = DB_connect(DB_HOST, DB_LOGIN, DB_PW, DB_DB);
    MYSQL_RES *res;
    MYSQL_ROW row;

    res = DB_sendQuery(con, query);
    row = mysql_fetch_row(res);

    DB_close(con);

    if(row[0] == NULL)
    {
        objet.qte = 0;
        return objet;
    } 
    else 
    {
        objet.qte = atof(row[0]);
        return objet;
    }
}


void updateDB(int idAnimal, struct objetDistrib objet)
{
     // CONNEXION BDD ET RECUPERATION idAnimal
    char * query = malloc(1500);
    char * buffer = malloc(10);
    char * bufferQte = malloc(10);
    sprintf(buffer, "%d", idAnimal);
    sprintf(bufferQte, "%f", objet.qte);

    struct dateHeure midi;
    midi = changeHourTime(midi,12,0,0);

    strcpy(query,"UPDATE `Programme` SET `distribue` = 1  WHERE `idAnimal` = '");
    strcat(query,buffer);
    strcat(query,"' AND `heure` BETWEEN ");


    if(compare_dates(objet.heure,midi) >= 0){

        //printf("ICI");
        strcat(query,"'12:00:00' AND '");
        strcat(query,objet.heure.total);

    }
    else{

        //printf("ICI");
        strcat(query,"'00:00:00' AND '");
        strcat(query,objet.heure.total);
        
    }
    strcat(query, "'");

    

    MYSQL* con = DB_connect(DB_HOST, DB_LOGIN, DB_PW, DB_DB);
    MYSQL_RES *res;
    MYSQL_ROW row;

    res = DB_sendQuery(con, query);


    strcpy(query,"INSERT INTO Repas (date,quantite,idAnimal,idCroquette) VALUES('");
    strcat(query,objet.heure.date);
    strcat(query,"',");
    strcat(query,bufferQte);
    strcat(query,",'");
    strcat(query,buffer);
    strcat(query,"','");
    strcat(query,"1");
    strcat(query,"')");

    res = DB_sendQuery(con, query);

    printf("DB à jour !\n");

    DB_close(con);

}


float getQuantiteParSec()
{

    // CONNEXION BDD ET RECUPERATION idAnimal
    MYSQL* con = DB_connect(DB_HOST, DB_LOGIN, DB_PW, DB_DB);
    MYSQL_RES *res;
    MYSQL_ROW row;
    char * query = malloc(1500);

    strcpy(query,"SELECT `qteParSec` FROM `Croquettes` WHERE `actif` = '1'");

    res = DB_sendQuery(con, query);
    if (mysql_num_rows(res) > 0) 
    {
        row = mysql_fetch_row(res);
        return atoi(row[0]);
    }
    else return -1;

}


int newTag(char tagAnimal[MAX_ATR_SIZE*3+1])
{
    // CONNEXION BDD ET RECUPERATION idAnimal
    MYSQL* con = DB_connect(DB_HOST, DB_LOGIN, DB_PW, DB_DB);
    MYSQL_RES *res;
    MYSQL_ROW row;

    char * query = malloc(1500);

    strcpy(query,"INSERT INTO Animaux (tag) VALUES ('");
    strcat(query,tagAnimal);
    strcat(query,"')");

    DB_sendQuery(con, query);

    int idAnimal = getIdAnimal(tagAnimal);

    char * buffer = malloc(10);
    sprintf(buffer, "%d", idAnimal);

    strcpy(query,"UPDATE `Animaux` SET `nom`='chat");
    strcat(query,buffer);
    strcat(query,"' WHERE `tag`='");
    strcat(query,tagAnimal);
    strcat(query,"'");

    DB_sendQuery(con,query);

    DB_close(con);

    return idAnimal;

}
/*
void pushRepas(float tempsRota, char tagAnimal[MAX_ATR_SIZE*3+1])
{
    // CONNEXION BDD ET RECUPERATION idAnimal
    MYSQL* con = DB_connect(DB_HOST, DB_LOGIN, DB_PW, DB_DB);
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[1500] = "SELECT `idAnimal` FROM `Annimaux` WHERE `tag` = '";
    strcat(query,tagAnimal);
    strcat(query,"'");

    res = DB_sendQuery(con, query);
    int num_fields = mysql_num_fields(res);

    row = mysql_fetch_row(res);
    char idAnimal[20];
    strcpy(idAnimal,row[0]);

    mysql_free_result(res);

    char * sqlDateTime = malloc(20);
    sqlDateTime = dateTime();


    char* buffer = malloc(20);

    // QUANTITE CROQUETTES
    float qtePer360=20;
    float timePer360=3;

    float qteRota=tempsRota*qtePer360/timePer360;

    sprintf(buffer,"%f",qteRota);

    // QUERY INSERT INTO
    char query2[1500] = "INSERT INTO Repas (horaire,quantite,idAnimal,idCroquette) VALUES('";
    strcat(query2,sqlDateTime);
    strcat(query2,"','");

    strcat(query2,buffer);
    strcat(query2,"','");

    strcat(query2,idAnimal);
    strcat(query2,"','");
    
    strcat(query2,"1')");

    res = DB_sendQuery(con, query2);
    
    DB_close(con);
}
*/

