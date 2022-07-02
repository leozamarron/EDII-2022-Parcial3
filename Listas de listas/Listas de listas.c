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
       (*cabEdo)->cabMun = NULL;
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

void muestraLxL(EDO cabEdo)
{
    MUN auxMun;

    while (cabEdo)
    {
        printf("%s %s %d %.2f %d\n", cabEdo->claEdo, cabEdo->nomEdo, cabEdo->pobEdo, cabEdo->egEdo, cabEdo->dpEdo);
        while (auxMun)
        {
            printf("%s %s %d %.2f %d\n", auxMun->claMun, auxMun->nomMun, auxMun->pobMun, auxMun->egMun, auxMun->dpMun);
            auxMun = auxMun->sigMun;
        }
        cabEdo = cabEdo->sigEdo;
    }
}

void muestraMun(MUN cabMun)
{
    while (cabMun)
    {
        printf("%s %s %d %.2f %d\n", cabMun->claMun, cabMun->nomMun, cabMun->pobMun, cabMun->egMun, cabMun->dpMun);
        cabMun = cabMun->sigMun;
    }
}

void muestraTodo(EDO cabEdo)
{
    MUN auxMun;
    while (cabEdo)
    {
        printf("%s %s %d %.2f %d\n", cabEdo->claEdo, cabEdo->nomEdo, cabEdo->pobEdo, cabEdo->egEdo, cabEdo->dpEdo);
        muestraMun(cabEdo->cabMun);
        cabEdo = cabEdo->sigEdo;
    }   
}

void muestraTodoRec(EDO cabEdo)
{
    if(cabEdo)
    {
        printf("%s %s %d %.2f %d\n", cabEdo->claEdo, cabEdo->nomEdo, cabEdo->pobEdo, cabEdo->egEdo, cabEdo->dpEdo);
        muestraMunRec(cabEdo->sigEdo);
        muestraTodoRec(cabEdo->sigEdo);
    }
}

void muestraMunRec(MUN cabMun)
{
    if(cabMun)
    {
        printf("%s %s %d %.2f %d\n", cabMun->claMun, cabMun->nomMun, cabMun->pobMun, cabMun->egMun, cabMun->dpMun);
        muestraMunRec(cabMun->sigMun);
    }
}

// Mostras los estados con su numero de municipios
void muestraEdoMun(EDO cabEdo)
{
    MUN aux;
    int cont;
    for(;cabEdo;cabEdo = cabEdo->sigEdo)
    {
        for(cont = 0, aux = cabEdo->cabMun; aux; aux = aux->sigMun, cont++);
            printf("Estado: %s (%d)", cabEdo->nomEdo, cont);
    }
}

// Encontrar(entregar) el nombre del estado con mas municipios
char *estadoMayorMun(EDO cabEdo)
{
    MUN auxMun;
    int i, j = 0;
    char *aux;
    for(;cabEdo; cabEdo = cabEdo->sigEdo)
    {
        for(i = 0, auxMun = cabEdo->cabMun; auxMun; auxMun = auxMun->sigMun, i++)
            if(i>j)
            {
                j = i;
                aux = cabEdo->nomEdo;
            }
    }
    return aux;
}

// Calcular "dp" para cada municipio
void calculaDp(EDO cabEdo)
{
    MUN auxMun;
    while (cabEdo)
    {
        auxMun = cabEdo->cabMun;
        while(auxMun)
        {
            auxMun->dpMun = auxMun->pobMun/auxMun->egMun;
            auxMun = auxMun->sigMun;
        }
    }
}

// Calcula los datos para cada estado
void calculaDatos(EDO cabEdo)
{
    MUN auxMun;
    int pobEdoC, dpEdoC;
    float egEdoC;
    for(;cabEdo; cabEdo = cabEdo->sigEdo)
    {
        for(auxMun = cabEdo->cabMun, pobEdoC = 0, dpEdoC = 0, egEdoC = 0; auxMun; auxMun->sigMun)
        {
            pobEdoC += auxMun->pobMun;
            dpEdoC += auxMun->dpMun;
            egEdoC += auxMun->egMun;
        }
        cabEdo->pobEdo = pobEdoC;
        cabEdo->dpEdo = dpEdoC;
        cabEdo->egEdo = egEdoC;
    }
}

//Calcular el numero de estados que tienen igual el numero de municipios - tarea----------------//

// Eliminacion
int elimMun(EDO cabEdo, char *clEdo, char *clMun)
{
    int res;
    if(!cabEdo || strcmp(cabEdo->claEdo, clEdo) > 0)
        res = 0;
    else if(strcmp(cabEdo->claEdo, clEdo) == 0)
        res = elimMunAux(cabEdo->cabMun, clMun);
    else
        res = elimMun(cabEdo->sigEdo, clEdo, clMun);
    return res;
}

int elimMunAux(MUN *cabMun, char *clMun)
{
    int res = 0;
    MUN aux, ant;

    aux = *cabMun;
    while (aux && strcmp(aux->claMun, clMun)>0)
    {
        ant = aux;
        aux = aux->sigMun;
    }
    if(aux && strcmp(aux->claMun, clMun) == 0)
    {
        if(aux == *cabMun)
            *cabMun = aux->sigMun;
        else    
            ant->sigMun = aux->sigMun;
        free(aux);
        res = 1;
    }
    return res;
}