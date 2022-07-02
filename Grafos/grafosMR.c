#include <stdio.h>
#include <stdlib.h>

/*
Grafos dinamicos
- Vertices - Elemntos que queremos relacionar
- Aristas - Indican cuando un elemento está relacionado con varios elemntos

Dos tipos de grafos:

- Dirigidos - Sus aristas tienen direcciones
- No Dirigido - Sus aristas son bidireccionales

    OPERACIONES BASICAS:
    - Inicializar
    - Insertar vertices + captura
    - Insertar relaciones + captura
    - Recorrido del grafo
    - eliminación de relación
    - eliminación de vertice
*/

typedef struct
{
    int rel;
    int valor;
}COSTO;

typedef struct
{
    int nmax, cv;
    int *vecVer;
    int **matRel; // Podemos usar costo para diferentes situaciones
}GRAFO_MR;

int iniGrafoMR(GRAFO_MR *g, int nm);
int asignaMemArrBi(int ***ptrArrBi, int nr, int nc);
int asignaMemArr(int **ptrArr, int n);
void capturaTam(GRAFO_MR *g);
int insVerMR(GRAFO_MR *g, int vr);
int insRelMR(GRAFO_MR g, int vo, int vd);
void capturaVertice(GRAFO_MR *g);
void capturaRel(GRAFO_MR *g);
void muestraGrafoMR(GRAFO_MR g);
void muestraVerticeNoRels(GRAFO_MR g);
int encuentraMasRel(GRAFO_MR g);
int hayRelMR(GRAFO_MR g, int ver0, int verd);
int hayRelRecMR(GRAFO_MR g, int ver0, int verd);
void muestraReldeVertice(GRAFO_MR g, int ver);
void muestraVerticeRel(GRAFO_MR g, int ver);
int hayCamino3(GRAFO_MR g, int vrA, int vrB, int vrC);
int camino3(GRAFO_MR g, int vrA, int vrB, int vrC);
int eliminaRelacion(GRAFO_MR g, int vr1, int vr2);
int elimVertice(GRAFO_MR *g, int vr);

int main()
{
    GRAFO_MR grafo;

    capturaTam(&grafo);
    capturaVertice(&grafo);
    capturaRel(&grafo);
    muestraGrafoMR(grafo);
}

// Elimina vertice
int elimVertice(GRAFO_MR *g, int vr)
{
    int res = 0, cont;
    for(cont = 0; vr < g->cv && vr != *(g->vecVer+cont); cont++);
    if(cont < g->cv)
    {
        for(cont = 0; cont < g->cv; cont++)
        {
            *(*(g->matRel + vr) + cont) = *(*(g->matRel + g->cv-1) + cont);
            *(*(g->matRel + cont) + vr) = *(*(g->matRel + cont) + g->cv-1);
        }
        *(*(g->matRel + vr) + vr) = *(*(g->matRel + g->cv-1) + g->cv-1);
        *(g->vecVer + vr) = *(g->vecVer + g->cv-1);
        g->cv--;
        res = 1;
    }
    return res;
}

// Elimina relación
int eliminaRelacion(GRAFO_MR g, int vr1, int vr2)
{
    int res = 0, col, ren;
    for(ren = 0; ren < g.cv && vr1 != *(g.vecVer+ren); ren++);
    if(ren < g.cv)
    {
        for(col = 0; col < g.cv && vr2 != *(g.vecVer+col); col++)
        if(col < g.cv)
        {
            res = *(*(g.matRel + ren)+col);
            if(res)
                *(*(g.matRel + ren)+col) = 0;
        }
    }
    return res;
}

// *Recorrido: determinar si 3 vertices forman un camino relacionando los 3
int camino3(GRAFO_MR g, int vrA, int vrB, int vrC)
{
    int res = 0, cont1, cont2, cont3;
    for(cont1 = 0; cont1 < g.cv && vrA != *(g.vecVer+cont1); cont1++);
    if(cont1 < g.cv)
    {
        for(cont2 = 0; cont2<g.cv && vrB != *(g.vecVer+cont2); cont2++);
        if(cont2<g.cv)
        {
            for(cont3 = 0; cont3<g.cv && vrC != *(g.vecVer+cont3); cont3++);
            if(cont3 < g.cv)
                res = *(*(g.matRel + cont1)+cont2) && *(*(g.matRel + cont2)+cont3);
        }
    }
    return res;
}

// *Recorrido: determinar si 3 vertices forman un camino
int hayCamino3(GRAFO_MR g, int vrA, int vrB, int vrC)
{
    int ren, col, res = 0;
    for (ren = 0; ren < g.cv && vrA != *(g.vecVer+ren); ren++);
    if(ren < g.cv)
    {
        for(col = 0; col < g.cv && vrB != *(g.vecVer+col); col++);
        if(col<g.cv)
            res = *(*(g.matRel+ren)+col);
        if(res)
        {
            ren = col;
            for(col = 0; col < g.cv && vrC != *(g.vecVer+col); col++);
            if(col<g.cv)
                res = *(*(g.matRel+ren)+col);
        }
    }
    return res;
}

// *Recorrido: mostrar los vertices que se relacionan con un vertice dado
void muestraVerticeRel(GRAFO_MR g, int ver)
{
    int col, ren;
    for (col = 0; ren < g.cv && ver != *(g.vecVer+col); col++);
    if(col<g.cv)
        for (ren = 0; ren < g.cv; ren++)
            if(*(*(g.matRel + ren) + col))
                printf("Esta relacionado con: %d ", *(g.vecVer+ren)); 
}

// *Recorrido: mostrar las relaciones de un vertice
void muestraReldeVertice(GRAFO_MR g, int ver)
{
    int col, ren;
    for (ren = 0; ren < g.cv && ver != *(g.vecVer+col); ren++);
    if(ren<g.cv)
        for (col = 0; col < g.cv; col++)
            if(*(*(g.matRel + ren) + col))
                printf("Esta relacionado con: %d ", *(g.vecVer+col));  
}

// *Recorrido: determinar si 2 vertices tienen una relación reciproca
int hayRelRecMR(GRAFO_MR g, int ver0, int verd)
{
    int ren, col, res = 0;
    for (ren = 0; ren < g.cv && ver0 != *(g.vecVer+ren); ren++);
    if(ren < g.cv)
    {
        for(col = 0; col < g.cv && verd != *(g.vecVer+col); col++);
        if(col<g.cv)
            res = *(*(g.matRel+ren)+col) && *(*(g.matRel+col)+ren);
    }
    return res;
}

// *Recorrido: determinar si hay relación entre 2 vertices dados
int hayRelMR(GRAFO_MR g, int ver0, int verd)
{
    int ren, col, res = 0;
    for (ren = 0; ren < g.cv && ver0 != *(g.vecVer+ren); ren++);
    if(ren < g.cv)
    {
        for(col = 0; col < g.cv && verd != *(g.vecVer+col); col++);
        if(col<g.cv)
            res = *(*(g.matRel+ren)+col);
    }
    return res;
}

// *Recorrido: encontrar el vertice mas relacionado
int encuentraMasRel(GRAFO_MR g)
{
    int ren, col, cont, masRel = 0, verMasRel = -1;
    for (ren = 0; ren < g.cv; ren++)
    {
        cont = 0;
        for(col = 0; col < g.cv; col++)
            cont += *(*(g.matRel + ren)+ col);
            if(masRel < cont)
            {
                masRel = cont;
                verMasRel = *(g.vecVer + ren);
            }
    }
    return verMasRel;
}

// *Recorrido: mostrar los vertices con su numero de relaciones
void muestraVerticeNoRels(GRAFO_MR g)
{
    int ren, col, cont;
    for (ren = 0; ren < g.cv; ren++)
    {
        cont = 0;
        for(col = 0; col < g.cv; col++)
            cont += *(*(g.matRel + ren)+ col); // Nos ahorramos el if
        printf("%d tiene %d relaciones. \n", *(g.vecVer+ren), cont);
    }
}

// Muestra grafo
void muestraGrafoMR(GRAFO_MR g)
{
    int ren, col;

    for(ren = 0; ren < g.cv; ren ++)
    {
        printf("%d:", *(g.vecVer + ren));
        for (col = 0; col < g.cv; col++)
            if(*(*(g.matRel + ren)+col))
                printf("%d ", *(g.vecVer + col));
        printf("\n");
    }
}

// Captura las relaciones hasta que se introduzca un 0
void capturaRel(GRAFO_MR *g)
{
    int resp, vro, vrd;

    do
    {
        printf("Dame el vertice origen: ");
        scanf("%d", &vro);
        printf("Dame el vertice origen: ");
        scanf("%d", &vrd);
        resp = insRelMR(*g, vro, vrd);
        resp? printf("Relacion agregada\n"):printf("Error no se pudo agregar\n");
    } while (vro && vrd);
}

//Agrega relaciones
int insRelMR(GRAFO_MR g, int vo, int vd)
{
    int res = 0, col, ren;
    for(ren = 0; ren < g.cv && vo != *(g.vecVer + ren); ren++);
    if(ren < g.cv)
    {
        for(col = 0; col < g.cv && vd != *(g.vecVer+col); col++);
        if(col < g.cv)
            res = *(*(g.matRel + ren) + col) = 1;
    }
    return res;
}

// Captura el vertice hasta que se introduzca un 0
void capturaVertice(GRAFO_MR *g)
{
    int resp, ver;

    do
    {
        printf("Dame el vertice que desea agregar: ");
        scanf("%d", &ver);
        resp = insVerMR(g, ver);
        resp? printf("Vertice agregado\n"):printf("Error no se pudo agregar\n");
    } while (ver);
}

//Inserta vertices
int insVerMR(GRAFO_MR *g, int vr)
{
    int res = 0, i;
    if(g->nmax > g->cv)
    {
        for(i=0; i < g->cv && vr != *(g->vecVer + i); i++);
        if (i == g->cv)
        {
            *(g->vecVer + g->cv) = vr;
            for (i = 0; i <= g->cv; i++)
                *(*(g->matRel + g->cv)+i) = *(*(g->matRel + i)+g->cv) = 0;
            g->cv++;
            res = 1;
        }
    }
    return res;
}

// Captura el tamaño de los vertices
void capturaTam(GRAFO_MR *g)
{
    int tam, res;

    printf("Dame el tamaño maximo de los vertices: ");
    scanf("%d", &tam);

    res = iniGrafoMR(g, tam);
    res? printf("Tamaño aceptado\n"):printf("Tamaño no aceptado\n");
}

//Inicializa el grafo
int iniGrafoMR(GRAFO_MR *g, int nm)
{
    int res;

    res = asignaMemArr(&g->vecVer, nm);

    if(res)
    {
        res = asignaMemArrBi(&g->matRel, nm, nm);
        if(res)
        {
            g->nmax = nm;
            g->cv = 0;
        }
        else
            free(g->vecVer);
    }
    return res;
}

int asignaMemArrBi(int ***ptrArrBi, int nr, int nc)
{
    int res = 0, i;

    *ptrArrBi = (int**)malloc(nr * sizeof(int*)); 
    if(*ptrArrBi)
    {
        res = 1;
        for (i = 0; i < nr && res; i++)
        {
            *(*ptrArrBi+i) = (int*)malloc(nc * sizeof(int)); 
            if (!*(*ptrArrBi+i))
            {
                while (--i >= 0)
                    free(*(*ptrArrBi+i));
                free(*ptrArrBi);
                res = 0;
            }
        }
    }
    return res; 
}

int asignaMemArr(int **ptrArr, int n)
{
    int res = 0;
    *ptrArr = (int*)malloc(n * sizeof(int));
    if (*ptrArr)
        res = 1;
    return res;
}