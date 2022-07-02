#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodoRel
{
    struct nodoVer *verRel;
    struct nodoRel *sigRel;
}*REL;

typedef struct nodoVer
{
    int ver;
    REL cabRel;
    struct nodoVer *sigVer;
}*GRAFO_EN;

//-------------------------OPERACIONES BASICAS-----------------//
/*
    **Inicialización
*/

void iniGrafo(GRAFO_EN *cab)
{
    *cab = NULL;
}

int creaNodoVer(GRAFO_EN *nuevo, int dato)
{
    int res = 0;
    *nuevo = (GRAFO_EN)malloc(sizeof(struct nodoVer));
    if(*nuevo)
    {
        (*nuevo)->ver = dato;
        (*nuevo)->sigVer = NULL;
        (*nuevo)->cabRel = NULL;
        res = 1;
    }
    return res;
}

int creaNodoRel(REL *nuevo, GRAFO_EN dato)
{
    int res = 0;
    *nuevo = (REL)malloc(sizeof(struct nodoRel));
    if(*nuevo)
    {
        (*nuevo)->verRel = dato;
        (*nuevo)->sigRel = NULL;
        res = 1;
    }
    return res;
}

int insRel(GRAFO_EN cab, int vo, int vd)
{
    int res = 0;
    GRAFO_EN aux;

    for(aux = cab; aux && aux->ver < vd; aux = aux->sigVer);
    if(aux && aux->ver == vd)
    {
        for(; cab && cab->ver < vo; cab = cab->sigVer);
        if(cab && cab->ver == vo)
            res = insRelAux(cab->cabRel, aux);
    }
    return res;
}

int insRelAux(REL *cabRel, GRAFO_EN vd)
{
    REL nuevo, aux, ant;
    int res = 0;

    for(aux = *cabRel; aux && aux->verRel < vd ; aux->sigRel, ant = aux);
    if(!aux || aux->verRel > vd)
    {
        res = creaNodoRel(&nuevo, vd);
        if(res)
        {
            nuevo->sigRel = aux;
            if(aux == *cabRel)
                *cabRel = nuevo;
            else
                ant->sigRel = nuevo;
        }
    }
    return res;
}

int insVer(GRAFO_EN *cab, int dato)
{
    int res;
    GRAFO_EN nuevo;
    if(!*cab || dato < (*cab)->ver)
    {
        res = creaNodoVer(&nuevo, dato);
        if(res)
        {
            nuevo->sigVer = *cab;
            *cab = nuevo;
        }
    }
    else if((*cab)->ver == dato)
        res = 0;
    else
        res = insVer(&(*cab)->sigVer, dato);
        
    return res;
}

int capturaVer(GRAFO_EN *cab)
{
    int res, dato;
    do
    {
        printf("Dame un dato: ");
        scanf("%d", &dato);
        
    } while (dato == -1);
    return res;
}

int insertaRel()
{

}

void muestraGrafoEN(GRAFO_EN g)
{
    REL aux;
    while (g)
    {
        printf("%d: ", g->ver);
        aux = g->cabRel;
        while (aux)
        {
            printf("%d ", aux->verRel->ver);
            aux = aux->sigRel;
        }
        g = g->sigVer;
    }
}

void contVer(GRAFO_EN g)
{
    REL aux;
    int cont;
    while (g)
    {
        cont = 0;
        aux = g->cabRel;
        while (aux)
        {
            cont++;
            aux = aux->sigRel;
        }
        printf("El vertice %d tiene %d.", g->ver, cont);
        g = g->sigVer;
    }
}

// Funcion para saber cual vertices tienes mas relaciones
int mayorNoVertices(GRAFO_EN g)
{
    REL aux;
    int cont, may = 0;
    while (g)
    {
        cont = 0;
        aux = g->cabRel;
        while (aux)
        {
            cont++;
            aux = aux->sigRel;
        }
        if(cont > may)
            may = cont;
        g->sigVer;
    }
    return may;
}

// *Determinar si hay relaciones entre 2 vertices
void hayRelVer(GRAFO_EN g, int vo, int vd)
{
    int res = 0;
    REL aux;
    for(; g && g->ver < vo; g = g->sigVer);
    if(g && g->ver == vo)
    {
        aux = g->cabRel;
        for(;aux && aux->verRel->ver != vd; aux = aux->sigRel);
        if(aux)
            res = 1;
    }
    return res;
}

// Contar el número de vértices que están relacionados con todos los demás.
int contadorVerRel(GRAFO_EN g)
{
    int cont = 0;

    for(; g; g = g->sigVer)
        if(g->cabRel)
            cont++;
}