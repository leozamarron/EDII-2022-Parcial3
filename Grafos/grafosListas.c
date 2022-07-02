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
    int *vecVer;
    int **matRel; //podemos usar costo para diferentes situaciones
}GRAFO_MR;

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

int insVerVR(GRAFO_VR *g, int vr)
{
    int res = 0, cont;
    if(g->cv < g->nmax) // Checar si esta lleno
    {
        for(cont = 0; cont < g->cv && vr != (g->vecVer+cont)->ver; cont++); // Comprueba si no hay uno igual y al mismo tiempo lo recorre al final
        if(cont == g->cv)
        {
            (g->vecVer + cont)->ver = vr;
            (g->vecVer + cont)->cabRel = NULL;
            g->cv++;
            res = 1;
        }
    }
    return res;
}

int creaNodo(LST_REL *nuevo, int rel)
{
    int res = 0;
    *nuevo = (LST_REL)malloc(sizeof(struct nodoRel));
    if(*nuevo)
    {
        (*nuevo)->sigRel = NULL;
        (*nuevo)->verRel = rel;
        res = 1;
    }
    return res;
}

int insRelOrdVR(GRAFO_VR g, int vo, int vd)
{
    int res = 0, cont;
    for(cont = 0; g.vecVer->ver > cont && (g.vecVer+cont)->ver != vd; cont++);
    if(cont < g.cv)
    {
        for(cont = 0; g.vecVer->ver > cont && (g.vecVer + cont)->ver != vo; cont++);
        if(cont < g.cv)
            res = insRelAuxVR(&(g.vecVer + cont)->cabRel, vd);
    }
    return res;
}

int insRelAuxVR(LST_REL vo, int vd)
{

}

// *Recorrido: muestra grafo
void muestraGrafoVR(GRAFO_VR g)
{
    int cont;
    LST_REL aux;

    for(cont = 0; cont < g.cv; cont++)
    {
        printf("%d: ", (g.vecVer+cont)->ver);
        for(aux = (g.vecVer + cont)->cabRel; aux; aux = aux->sigRel)
            printf("%d ", aux->verRel);
        printf("\n");
    }
}

// Contador relaciones
void contadorRel(GRAFO_VR g)
{
    int cont, contRel;
    LST_REL aux;

    for(cont = 0; cont < g.cv; cont++)
    {
        for(aux = (g.vecVer + cont)->cabRel, contRel = 0; aux; aux = aux->sigRel, contRel++);
        printf("El vertice %d tiene %d relaciones.\n", cont, contRel);
    }
}

// mayor numero de vertices
void mayoNoVer(GRAFO_VR g)
{
    int cont, contRel, may = 0;
    LST_REL aux;

    for(cont = 0; cont < g.cv; cont++)
    {
        for(aux = (g.vecVer + cont)->cabRel, contRel = 0; aux; aux = aux->sigRel, contRel++)
            if(may < contRel)
                may = contRel;
    }
}

// *Determinar si hay relaciones entre 2 vertices
int relVertices(GRAFO_VR g, int vo, int vd)
{
    int res = 0, cont;
    LST_REL aux;

    for(cont = 0; g.vecVer->ver > cont && (g.vecVer+cont)->ver != vo; cont++);
    if(cont < g.cv)
    {
        for(aux = (g.vecVer+cont)->cabRel; aux->verRel < vd && aux; aux->sigRel);
        if(aux && aux->verRel == vd)
            res = 1;
    }
    return res;
}


// *Determinar si hay relaciones reciprocas entre 2 vertices 
void relVerRec(GRAFO_VR g, int vo, int vd)
{
    int res = 0, cont;
    LST_REL aux;

    for(cont = 0; cont<g.cv && (g.vecVer+cont)->ver != vo; cont++);
    if(cont < g.cv)
    {
        for(aux = (g.vecVer+cont)->cabRel; aux && aux->verRel < vd; aux->sigRel);
        if(aux && aux->verRel == vd)
        {
            for(cont = 0; (g.vecVer+cont)->ver != vd; cont++);
            
            for(aux = (g.vecVer+cont)->cabRel; aux  && aux->verRel < vo; aux->sigRel);
            if(aux && aux->verRel == vo)
                res = 1;
        }
    }
    return res;
}

// Eliminacion de relacion
int elimRelVR(GRAFO_VR g, int vo, int vd)
{
    int res = 0, cont;
    for(cont = 0; cont < g.cv && vo != (g.vecVer + cont)->ver; cont++);
    if(cont<g.cv)
        res = elimRelVRaux(&(g.vecVer+cont)->cabRel, vd);
    return res;
}

int elimRelVRaux(LST_REL *vo, int vd)
{
    int res = 0;
    LST_REL aux, ant;

    aux = *vo;
    while (aux && aux->verRel < vd)
    {
        ant = aux;
        aux = aux->sigRel;
    }
    if(aux && aux->verRel == vd)
    {
        if(aux == *vo)
            *vo = aux->sigRel;
        else
            ant->sigRel = aux->sigRel;
        free(aux);
        res = 1;
    }
    return res;
}

// Eliminacion de vértice
int elimVerVR(GRAFO_VR *g, int vr)
{
    int res = 0, cont;
    LST_REL aux;

    for(cont = 0; cont < g->cv && vr != (g->vecVer+cont)->ver; cont++);
    if(cont<g->cv)
    {
        while ((g->vecVer+cont)->cabRel)
        {
            while ((g->vecVer+cont)->cabRel)
            {
                aux = (g->vecVer+cont)->cabRel;
                (g->vecVer+cont)->cabRel = aux->sigRel;
                free(aux);
            }
            *(g->vecVer+cont) = *(g->vecVer+g->cv-1);
            g->cv--;
            for(cont = 0; cont<g->cv; cont++)
                elimRelVRaux(&(g->vecVer+cont)->cabRel, vr);
            res = 1;
        }
    }
    return res;
}

// *"Convertir" un grafoMR a grafoVR
int mrToVr(GRAFO_MR g, GRAFO_VR *gVR)
{
    int res, ren, col;
    
    res = iniGrafoVR(gVR, g.nmax);
    if(res)
    {
        for(ren = 0; ren < g.cv; ren++)
            insVerVR(gVR, *(g.vecVer+ren));
        for(ren = 0; res && ren < g.cv; ren++)
            for(col = 0; res && col < g.cv; col++)
                if(*(*(g.matRel+ren)+col))
                    res = insRelOrdVR(*gVR, *(g.vecVer+ren) ,*(g.vecVer+col));
        if(!res)
            borraTodo(gVR);
    }
    return res;
}