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
    int pobEdo, dpEdo, promDp;
    float egEdo, promEg, promPob;
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
            nuevo->sigEdo = *cabEdo;
            *cabEdo = nuevo;
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
        res = insMun(cabEdo->sigEdo, cEdo, cMun, nMun, pob, eg);
    return res;
}

int capturaEdo(EDO *cabEdo)
{
    int res;
    char clave[5], nombre[20];

    printf("Dame la clave del estado: ");
    scanf("%s", clave);
    printf("Dame el nombre del estado: ");
    gets(nombre);

    res = insEdoRec(cabEdo, clave, nombre);

    return res;
}

int capturaMun(EDO cabEdo)
{
    int res;

    char claEdo[5], claMun[5], nombre[20];
    int pob;
    float eg;

    printf("Dame la clave del estado: ");
    scanf(" %s", claEdo);
    printf("Dame la clave del municipio: ");
    scanf(" %s", claMun);
    printf("Dame el nombre del municipio: ");
    gets(nombre);
    printf("Dame la población del municipio: ");
    scanf("%d", &pob);
    printf("Dame la extension geografica: ");
    scanf("%d", &eg);

    res = insMun(cabEdo, claEdo, claMun, nombre, pob, eg);

    return res;
}

// Función iterativa para calcular y asignar el promedio de extensión geográfica de cada estado.
void calculaPromEg(EDO cabEdo)
{
    float suma, contador;
    MUN aux;
    for (; cabEdo; cabEdo = cabEdo->sigEdo)
    {
        suma = contador = 0;
        for (aux = cabEdo->cabMun; aux; aux = aux->sigMun, contador++)
            suma += aux->egMun;
        cabEdo->promEg = suma/contador;
    }
}

// Función recursiva para calcular y asignar el promedio de densidad de población de cada estado.
void calculaPromDp(EDO cabEdo)
{
    int contador, suma;
    MUN aux;
    if(cabEdo)
    {
        calculaPromDp(cabEdo->sigEdo);
        if(cabEdo->cabMun)
        {
            suma = contador = 0;
            for (aux = cabEdo->cabMun; aux; aux = aux->sigMun, contador++)
                suma += aux->dpMun;
            cabEdo->promDp = suma/contador;
        }
    }
}

// funciones iterativas para calcular y asignar el promedio de población de cada estado.
void calculaPromPob(EDO cabEdo)
{
    float contador, suma;
    MUN aux;
    for (; cabEdo; cabEdo = cabEdo->sigEdo)
    {
        suma = contador = 0;
        for (aux = cabEdo->cabMun; aux; aux = aux->sigMun, contador++)
            suma += aux->pobMun;
        asignaPromPob(aux, suma, contador);
    }
}

void asignaPromPob(EDO cabEdo, float sum, float cont)
{
    cabEdo->promPob = sum/cont;
}