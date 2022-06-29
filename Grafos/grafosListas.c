/*
Grafos dinamicos
- Vertices - Elemntos que queremos relacionar
- Aristas - Indican cuando un elemento está relacionado con varios elemntos

Dos tipos de grafos:

- Dirigidos - Sus aristas tienen direcciones
- No Dirigido - Sus aristas son bidireccionales

    OPERACIONES BASICAS:
    - Inicializar
    - crea nodo
    - Insertar vertices + captura
    - Insertar relaciones + captura
    - Recorrido del grafo
    - eliminación de relación
    - eliminación de vertice
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct nodoRel
{
    int verRel;
    struct nodoRel *sigRel;
}*LST_REL;

typedef struct
{
    int ver;
    LST_REL cabRel;
}VER;

typedef struct
{
    int nmax, cv;
    VER *vecVer;
}GRAFO_VR;

int iniGrafoVR(GRAFO_VR *g, int n)
{
    int res = 0;

    g->vecVer = (VER*)malloc(n * sizeof(VER));

    if(g->vecVer)
    {
        g->nmax = n;
        g->cv = 0;
        res = 1;
    }
    return res;
}