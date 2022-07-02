#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dudas
{
    char nombre[25];
}*DUDA;

void dude(DUDA duda, char **aux);

int main()
{
    char *aux;
    DUDA duda;

    dude(duda, &aux);

    printf("dame el nombre: ");
    gets(duda->nombre);

    printf("El nombre es %s", aux);


    return 0;
}

void dude(DUDA duda, char **aux)
{
    *aux = duda->nombre;
}