//LISTAS DE LISTAS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct nodoMun{
    char claMun[5], nomMun[20];
    int pobMun, dpMun;
    float egMun;
    struct nodoMun *sigMun;
}*MUN;

typedef struct nodoEdo{
    char claEdo[5], nomEdo[30];
    int pobEdo, dpEdo;
    float egEdo;
    MUN cabMun;
    struct nodoEdo *sigEdo;
}*EDO;

void iniEdos(EDO *cabEdo)
{
    *cabEdo = NULL;
}

int creaNodoEdo(EDO *cabEdo, char *clave, char *nombre)
{
    int res = 0;
    *cabEdo = (EDO)malloc(sizeof(struct nodoEdo));
    if(*cabEdo)
    {
       (*cabEdo)->sigEdo = NULL;
       strcpy((*cabEdo)->claEdo, clave);
       strcpy((*cabEdo)->nomEdo, nombre);
       (*cabEdo)->dpEdo = 0;
       (*cabEdo)->pobEdo = 0;
       (*cabEdo)->egEdo = 0;
       res = 1;
    }
    return res;
}

int creaNodoMun(MUN *cabMun, EDO *cabEdo, char *clave, char *nombre, int poblacion, int dp, float eg)
{
    int res = 0;
    *cabMun = (MUN)malloc(sizeof(struct nodoMun));
    if(*cabEdo)
    {
       (*cabMun)->sigMun = NULL;
       strcpy((*cabMun)->claMun, clave);
       strcpy((*cabMun)->nomMun, nombre);
       (*cabMun)->pobMun = poblacion;
       (*cabMun)->dpMun = dp;
       (*cabMun)->egMun = eg;
       res = 1;
    }
    return res;
}

int insEdoRec(EDO *cabEdo, char *clave, char *nombre)
{
    int res;
    EDO nuevo;

    if(!*cabEdo || strcmp((*cabEdo)->claEdo, clave)>0){
        res = creaNodoEdo(&nuevo, clave, nombre);
        if(res){
            nuevo->sigEdo = cabEdo;
            cabEdo = nuevo;
        }
    }
    else if(strcmp((*cabEdo)->claEdo, clave)==0)
        res = 0;
    else
        res = insEdoRec(&(*cabEdo)->sigEdo, clave, nombre);

    return res;
}

int insMun(EDO cabEdo, char *cEdo, char *cMun, char *nMun, int pob, float eg)
{
    int res;

    if(!cabEdo || strcmp(cabEdo->claEdo, cEdo)>0)
        res = 0;
    else if(strcmp(cabEdo->claEdo, cEdo) == 0)
        res = insMunAux(&cabEdo->cabMun, cMun, nMun, pob, eg);
    else
        res = insMun(cabEdo->cabMun, cEdo, cMun, nMun, pob, eg);
    return res;
}



