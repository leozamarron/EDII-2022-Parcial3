#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Repaso 1
typedef struct nodoVend
{
    int claveVen;
    char nombreVen;
    float vendidoVen;
    struct nodoVend *sigVen;
}*VEND;

typedef struct nodoSucu
{
    char claveSuc[5];
    char nombreSuc[15];
    VEND cabVen;
    struct nodoSucu sigSuc;
}*SUC;

typedef struct nodoPais
{
    char clavePais[5];
    char nombrePais[15];
    SUC cabVend;
    struct sigPais;
}*PAIS;

//Repaso 2

typedef struct nodoCli
{
    char claveCli[10];
    char nomCli[10];
    float monto;
    struct nodoCli *sigCli;
}*CLI;

typedef struct nodoSuc
{
    char claveSuc[10];
    char nomSuc[10];
    CLI cabCli;
    struct nodoSuc *sigSuc;
}*SUC;

typedef struct nodoEdo
{
    char claveEdo[10];
    char nomEdo[10];
    SUC cabSuc;
    struct nodoEdo *sigEdo;
}*EDO;

// con base a las estructuras anteriores, escriba funciomes iterativas(3) 
// para mostrar toda la informacion de la estructura

void muestraTodo(EDO cabEdo)
{
    while (cabEdo)
    {
        printf("El estado es: %s\n", cabEdo->nomEdo);
        muestraSuc(cabEdo->cabSuc);
        cabEdo = cabEdo->sigEdo;
    }
}

void muestraSuc(SUC cabSuc)
{
    while (cabSuc)
    {
        printf("La sucursal es: %s\n", cabSuc->nomSuc);
        muestraCli(cabSuc->cabCli);
        cabSuc = cabSuc->cabCli;
    }
}

void muestraCli(CLI cabCli)
{
    printf("Los clientes son:\n");
    while (cabCli)
    {
        printf("%s\n", cabCli->nomCli);
        cabCli = cabCli->sigCli;
    }
}

// Repaso 3

typedef struct nodoProd
{
    char claveProd[10];
    char nomProd[10];
    float pCompra, pVenta;
    int exis;
    struct nodoProd *sigProd;
}*PROD;

typedef struct nodoSuc
{
    char claveSuc[10];
    char nomSuc[10];
    PROD cabProd;
    struct nodoSuc *sigSuc;
}*SUC;

typedef struct nodoPais
{
    char clavePais[10];
    char nomPais[10];
    float totGanancia;
    SUC cabSuc;
    struct nodoPais *sigPais;
}*PAIS;

void calculaGan(PAIS cabPais)
{
    SUC auxSuc;
    PROD auxProd;
    float suma;

    while (cabPais)
    {
        suma = 0;
        auxSuc = cabPais->cabSuc;
        while (auxSuc)
        {
            auxProd = auxSuc->cabProd;
            while (auxProd)
            {
                if (auxProd->exis)
                {
                    suma += auxProd->pVenta - auxProd->pCompra;
                }
            }
            auxProd = auxProd->sigProd;
        }
        cabPais->totGanancia = suma;
        cabPais = cabPais->sigPais;
    }
}

// Repaso 4

int hayCamino(GRAFO_EN g, int v1, int v2, int v3)
{
    GRAFO_EN aux1, aux2;
    REL auxRel;
    int res = 0;

    for(aux2 = g; aux2 && aux2->ver != v3; aux2 = aux2->sigVer);
    if (aux2)
    {
        for(aux1 = g; aux1 && aux1->ver != v2; aux1 = aux1->sigVer);
        if(aux1)
        {
            for(; g && g->ver != v1; g = g->sigVer);
            if(g)
            {
                for(auxRel = aux1->ver; g && g->verRel->ver != auxRel; g = g->sigRel);
                if (g)
                {
                    for(auxRel = aux2->ver; aux1 && aux1->verRel->ver != auxRel; aux1 = aux1->sigRel);
                    if(aux1)
                    {
                        for(; auxRel && auxRel->verRel->ver != aux2->ver; auxRel = auxRel->sigRel);
                        if(auxRel)
                            res = 1;
                    }
                }
            }
        }
    }
    return res;
}