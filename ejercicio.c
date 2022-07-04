/*
  INSTRUCCIONES
  1.- Escribir el código correspondiente a cada función.
  2.- ** Solo ** implementar las partes de código faltantes, ** no ** modificar el código ya escrito.
  3.-  No agregar mas funciones, solo son necesarias las incluidas.
  
  Nombre del alumno: "Leonel Zamarrón Rangel"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estructura ingrediente */
typedef struct nodoIngre
{ 
  char nomIngre[25];
  struct nodoIngre *sigIngre;
} *LISTA_INGRE;

/* Estructura receta */
typedef struct nodoRece
{
  char nomRece[25];
  LISTA_INGRE cabIngre;
  struct nodoRece *sigRece;
} *LISTA_RECE;

/* Estructura tipo receta */
typedef struct nodoTipo
{
  char nomTipo[25];
  LISTA_RECE cabRece;
  struct nodoTipo *sigTipo;
} *RECETARIO;

/* Esta función inicializa el recetario */
void iniRecetario(RECETARIO *r);

/* Esta función creará un nodo ingrediente */
int creaNodoIngre(LISTA_INGRE *nuevo, char *ingre);

/* Esta función creará un nodo receta */
int creaNodoRece(LISTA_RECE *nuevo, char *rece);

/* Esta función creará un nodo tipo-receta */
int creaNodoTipo(RECETARIO *nuevo, char *tipo);

/* Esta función busca el tipo de receta donde según la receta se insertará el ingrediente */
int insIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre);

/* Esta función busca la receta donde insertará el ingrediente */
int insIngreBuscaRece(LISTA_RECE lr, char *rece, char *ingre);

/* Esta función inserta el ingrediente */
int insIngre(LISTA_INGRE *li, char *ingre);

/* Esta función busca el tipo de receta donde se inserta la receta */
int insReceta(RECETARIO r, char *tipo, char *rece);

/* Esta función inserta una receta */
int insRece(LISTA_RECE *lr, char *rece);

/* Esta función inserta un tipo de receta */
int insTipo(RECETARIO *r, char *tipo);

/* Esta Función captura los tipos de recetas, para insertarlos en el recetario */
void capturaTipos(RECETARIO *r);

/* Esta Función captura las recetas, para insertarlas en el recetario */
void capturaRecetas(RECETARIO r);

/* Esta Función captura los ingredientes, para insertarlos en el recetario */
void capturaIngredientes(RECETARIO r);

/* Esta función muestra toda la información del rcetario */
void muestraRecetario(RECETARIO r);

/* Esta función muestra las recetas de un tipo de receta */
void muestraRecetasTipo(RECETARIO r, char *tipo);

/* Esta función muestra los ingredientes de una receta */
void muestraIngredientesReceta(RECETARIO r, char *tipo, char *rece);

/* Esta función muestra el No. de receta que tiene cada tipo de receta */
void muestraNoReceXtipo(RECETARIO r);

void muestraNoRece(RECETARIO r);

/* Esta función muestra el No. de ingredientes de cadad receta */
void muestraNoIngreXrece(RECETARIO r);

void muestraNoIngre(RECETARIO r);

/* Esta función calcula y retorna cuantos tipos de recta tiene un recetario */
int cuentaTipos(RECETARIO r);

/* Esta función busca el tipo de receta para contar cuantas recetas tiene
   se usa como base para la siguiente función 
  */
int cuentaRecetas(RECETARIO r, char *tipo);

/* Esta función cuenta el No. de recetas de un tipo previamente buscado */
int cuentaRece(LISTA_RECE lr);

/* Esta función busca el tipo de receta como base para la siguiente función */
int cuentaIngredientes(RECETARIO r, char *tipo, char *rece);

/* Esta función busca una receta para poder contar cuantas recetas tiene
   se usa como base para la siguiente función 
 */
int cuentaIngreBuscaRece(LISTA_RECE lr, char *rece);

/* Esta función cuenta el No. de ingredientes de una receta previamente buscada,
   que pertece a un tipo también previamente buscado.
 */
int cuentaIngre(LISTA_INGRE li);

/* Esta función encuentra el nombre del tipo de receta con mas recetas(TMR) */
void encuentraTMR(RECETARIO r, char *nomTMR);

/* Esta función encuentra el nombre de la receta con mas ingredientes (RMI) 
   así como también el tipo al que pertenece */
void encuentraRMI(RECETARIO r, char *tipoRMI, char *nomRMI);

/* Esta función cuenta el número de recetas que usan un ingrediente */
int cuentaReceIngre(RECETARIO r, char *ingre);

/* Esta función elimina un ingrediente, despues de haber encontrado su
   receta y tipo al que pertenece */
int eliminaIngre(LISTA_INGRE *li, char *ingre);

/* Esta función busca la receta para poder eliminar el ingrediente */
int eliminaReceIngre(LISTA_RECE lr, char *rece, char *ingre);

/* Esta función busca el tipo de receta, para ubicar la lista de recetas
   donde se ubica el ingrediente a eliminar 
 */
int eliminaIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre);

/* Esta función elimina todos los ingredientes de una receta */
void eliminaIngredientes(LISTA_INGRE *li);

/* Función para buscar una receta y poder eliminar sus ingredientes */
int eliminaIngresBuscaReceXreceta(LISTA_RECE *lr, char *rece);

/* Esta función elimina todas las recetas de un tipo, eliminando
   previamente todos los ingredientes  */
void eliminaRecetas(LISTA_RECE lr);

int eliminaReceta(RECETARIO r, char *tipo, char *rece);

/* Esta función elimina un tipo de receta */
int eliminaTipo(RECETARIO *r, char *tipo);

/* Esta función elimina un recetario completo */
void eliminaRecetario(RECETARIO *r);

//#include "evalua/evaluar.h"

int main()
{
  /* Puede escribir a continuación el código necesario para probar sus funciones
     aunque no es necesario */ 
   RECETARIO recetario;
   char TMR[25];
   char tipoRMI[25], nomRMI[25], cont;

   iniRecetario(&recetario);
   capturaTipos(&recetario);
   capturaTipos(&recetario);
   capturaRecetas(recetario);
   capturaRecetas(recetario);
   capturaIngredientes(recetario);
   capturaIngredientes(recetario);
   capturaIngredientes(recetario);
   capturaIngredientes(recetario);
   muestraRecetario(recetario);
   cont = cuentaTipos(recetario);
   printf("Numero de tipos son %d.\n", cont);
   cont = cuentaRecetas(recetario, "Huevo");
   printf("Numero de recetas son %d.\n", cont);
   cont = cuentaIngredientes(recetario, "Huevo", "Frijoles");
   printf("Numero de ingredientes son %d.\n", cont);
   muestraNoRece(recetario);
   muestraNoIngre(recetario);
   encuentraTMR(recetario, TMR);
   printf("El tipo que tiene mas recetas es %s\n", TMR);
   encuentraRMI(recetario, tipoRMI, nomRMI);
   printf("La receta con mas ingredientes es %s le pertence a %s\n", nomRMI, tipoRMI);
   cont = cuentaReceIngre(recetario, "chile");
   printf("Numero de veces que se usa un ingrediente son %d.\n", cont);
   eliminaIngrediente(recetario, "Huevo", "Frijoles", "chile")? printf("Se elimino\n"):printf("No se elimino\n");
   eliminaReceta(recetario, "Huevo", "Frijoles")? printf("Se elimino\n"):printf("No se elimino\n");
   eliminaTipo(&recetario, "Huevo")? printf("Se elimino\n"):printf("No se elimino\n");
   eliminaRecetario(&recetario);

   return 0;  
 /* NO BORRAR ESTA LINEA */
//  evaluar();    
}

/* Función para inicualizar la estructura principal */
void iniRecetario(RECETARIO *r)
{
    *r = NULL;
}

/* Función para crear un nodo ingrediente */
int creaNodoIngre(LISTA_INGRE *nuevo, char *ingre)
{
   int res = 0;
   *nuevo = (LISTA_INGRE)malloc(sizeof(struct nodoIngre));
   if(*nuevo)
   {
      (*nuevo)->sigIngre = NULL;
      strcpy((*nuevo)->nomIngre, ingre);
      res = 1;
   }
   return res;
}

/* Función para crear un nodo receta */
int creaNodoRece(LISTA_RECE *nuevo, char *rece)
{
   int res = 0;
   *nuevo = (LISTA_RECE)malloc(sizeof(struct nodoRece));
   if(*nuevo)
   {
      strcpy((*nuevo)->nomRece, rece);
      (*nuevo)->cabIngre = NULL;
      (*nuevo)->sigRece = NULL;
      res = 1;
   }
   return res;
}

/* Función para crear un nodo tipo */
int creaNodoTipo(RECETARIO *nuevo, char *tipo)
{
   int res = 0;
   *nuevo = (RECETARIO)malloc(sizeof(struct nodoTipo));
   if(*nuevo)
   {
      strcpy((*nuevo)->nomTipo, tipo);
      (*nuevo)->cabRece = NULL;
      (*nuevo)->sigTipo = NULL;
      res = 1;
   }
   return res;
}

/* Inserta ingrediente: Función para insertar el ingrediente */
int insIngre(LISTA_INGRE *li, char *ingre)
{
   int res;
   LISTA_INGRE nuevo;

   if(*li && strcmp((*li)->nomIngre, ingre) == 0)
      res = 0;
   else if(!*li || strcmp((*li)->nomIngre, ingre)>0)
   {
      res = creaNodoIngre(&nuevo, ingre);
      if(res)
      {
         nuevo->sigIngre = *li;
         *li = nuevo;
      }
   }
   else
      res = insIngre(&(*li)->sigIngre, ingre);

   return res;
}

/* Inserta ingrediente: Función para buscar la receta */
int insIngreBuscaRece(LISTA_RECE lr, char *rece, char *ingre)
{
   int res = 0;

   for(; lr && strcmp(lr->nomRece, rece) < 0; lr = lr->sigRece);
   if(lr && strcmp(lr->nomRece, rece) == 0)
      res = insIngre(&lr->cabIngre, ingre);

   return res;
}

/* Inserta ingrediente: Función para buscar el tipo */
int insIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre)
{
   int res = 0;

   for(; r && strcmp(r->nomTipo, tipo) < 0; r = r->sigTipo);
   if(r && strcmp(r->nomTipo, tipo) == 0)
      res = insIngreBuscaRece(r->cabRece, rece, ingre);

   return res;
}

/* Inserta receta: Función para insertar la receta */
int insRece(LISTA_RECE *lr, char *rece)
{
   int res;
   LISTA_RECE nuevo;

   if(*lr && strcmp((*lr)->nomRece, rece) == 0)
      res = 0;
   else if(!*lr || strcmp((*lr)->nomRece, rece)>0)
   {
      res = creaNodoRece(&nuevo, rece);
      if(res)
      {
         nuevo->sigRece = *lr;
         *lr = nuevo;
      }
   }
   else
      res = insRece(&(*lr)->sigRece, rece);

   return res;
}

/* Inserta receta: Función para buscar el tipo de la receta */
int insReceta(RECETARIO r, char *tipo, char *rece)
{
   int res = 0;

   for(; r && strcmp(r->nomTipo, tipo) < 0; r = r->sigTipo);
   if(r && strcmp(r->nomTipo, tipo) == 0)
      res = insRece(&r->cabRece, rece);

   return res;
}

/*Función para insertar un tipo de receta */
int insTipo(RECETARIO *r, char *tipo)
{
   int res;
   RECETARIO nuevo;

   if(*r && strcmp((*r)->nomTipo, tipo) == 0)
      res = 0;
   else if(!*r || strcmp((*r)->nomTipo, tipo)>0)
   {
      res = creaNodoTipo(&nuevo, tipo);
      if(res)
      {
         nuevo->sigTipo = *r;
         *r = nuevo;
      }
   }
   else
      res = insTipo(&(*r)->sigTipo, tipo);

   return res;
}

/* Función para capturar Tipos de recetas, inserlos en el recetario */
void capturaTipos(RECETARIO *r)
{
   char tipo[25];
   int res;
   fflush(stdin);
   printf("Dame el nombre del tipo de receta: ");
   scanf("%[^\n]", tipo);

   res = insTipo(r, tipo);

   res? printf("Dato aceptado\n"):printf("Dato no aceptado\n");
}

/* Función para captura las recetas, insertarlas en recetario en el tipo al que pertenecen */
void capturaRecetas(RECETARIO r)
{
   char tipo[25];
   char rece[25];
   fflush(stdin);
   printf("Dame el tipo de receta: ");
   scanf("%[^\n]", tipo);
   fflush(stdin);
   printf("Dame el nombre de la receta que quiera agregar: ");
   scanf("%[^\n]", rece);
   insReceta(r, tipo, rece);
}

/* Esta Función captura los ingredientes, para insertarlos en el recetario */
void capturaIngredientes(RECETARIO r)
{
   char tipo[25];
   char rece[25];
   char ingre[25];
   fflush(stdin);
   printf("Dame el tipo de receta: ");
   scanf("%[^\n]", tipo);
   fflush(stdin);
   printf("Dame el nombre de la receta: ");
   scanf("%[^\n]", rece);
   fflush(stdin);
   printf("Dame el nombre del ingrediente que quiera agregar: ");
   scanf("%[^\n]", ingre);

   insIngrediente(r, tipo, rece, ingre);
}

/* Función para mostrar el recetario completo */
void muestraRecetario(RECETARIO r)
{
   LISTA_RECE auxReceta;
   LISTA_INGRE auxIngrediente;

   while (r)
   {
      printf("El tipo de receta es: %s\n", r->nomTipo);
      auxReceta = r->cabRece;
      while (auxReceta)
      {
         printf("La receta es: %s\n", auxReceta->nomRece);
         auxIngrediente = auxReceta->cabIngre;
         printf("Los ingredientes de la receta son:\n");
         while (auxIngrediente)
         {
            printf("%s\n", auxIngrediente->nomIngre);
            auxIngrediente = auxIngrediente->sigIngre;
         }
         
         auxReceta = auxReceta->sigRece;
      }
      r = r->sigTipo;
   }
}

/* Función para contar el No. de tipos de recetas */
int cuentaTipos(RECETARIO r)
{
   int cont = 0;
   while (r)
   {
      cont++;
      r = r->sigTipo;
   }
   return cont;
}

/* Cuenta Recetas: Función para contar las recetas */
int cuentaRece(LISTA_RECE lr)
{
   int cont = 0;
   while (lr)
   {
      cont++;
      lr = lr->sigRece;
   }
   return cont;
}

/* Cuenta Recetas: Función para buscar el tipo de las recetas a contar*/
int cuentaRecetas(RECETARIO r, char *tipo)
{
   int cont = 0;
   for(;r && strcmp(r->nomTipo, tipo) < 0; r = r->sigTipo);
   if(r && strcmp(r->nomTipo, tipo) == 0)
      cont = cuentaRece(r->cabRece);

   return cont;
}

/* Cuenta ingredientes:Función para buscar el tipo */
int cuentaIngredientes(RECETARIO r, char *tipo, char *rece)
{
   int cont = 0;
   for(;r && strcmp(r->nomTipo, tipo) < 0; r = r->sigTipo);
   if(r && strcmp(r->nomTipo, tipo) == 0)
      cont = cuentaIngreBuscaRece(r->cabRece, rece);

   return cont;
}

/* Cuenta ingredientes: Función para buscar la receta */
int cuentaIngreBuscaRece(LISTA_RECE lr, char *rece)
{
   int cont = 0;
   for(;lr && strcmp(lr->nomRece, rece) < 0; lr = lr->sigRece);
   if(lr && strcmp(lr->nomRece, rece) == 0)
      cont = cuentaIngre(lr->cabIngre);

   return cont;
}

/* Función para contar los ingredientes */
int cuentaIngre(LISTA_INGRE li)
{
   int cont = 0;
   while (li)
   {
      cont++;
      li = li->sigIngre;
   }
   return cont;
}

/* Función para contar y mostrar el No. de recetas en cada tipo */
void muestraNoRece(RECETARIO r)
{
   int cont;
   while (r)
   {
      cont = cuentaRece(r->cabRece);
      printf("El tipo %s tiene %d receta(s).\n", r->nomTipo, cont);
      r = r->sigTipo;
   }
}

/* Función para contar y mostrar el No. de ingredientes por cada receta */
void muestraNoIngre(RECETARIO r)
{
   int cont;
   LISTA_RECE auxRec;
   LISTA_INGRE auxIngre;
   while (r)
   {
      auxRec = r->cabRece;
      while (auxRec)
      {
         cont = 0;
         auxIngre = auxRec->cabIngre;
         while (auxIngre)
         {
            cont++;
            auxIngre = auxIngre->sigIngre;
         }
         printf("La receta %s tiene %d ingrediente(s).\n", auxRec->nomRece, cont);
         auxRec = auxRec->sigRece;
      }
      r = r->sigTipo;
   }
}

/* Función para encontrar el nombre del Tipo de receta con Mas Recetas(TMR) */
void encuentraTMR(RECETARIO r, char *nomTMR)
{
   int cont, may = 0;
   LISTA_RECE auxRec;
   while (r)
   {
      auxRec = r->cabRece;
      cont = 0;
      while (auxRec)
      {
         cont += cuentaRece(auxRec);
         auxRec = auxRec->sigRece;
      }
      if(may < cont)
      {
         may = cont;
         strcpy(nomTMR, r->nomTipo);
      }
      r = r->sigTipo;
   }
}

/* Función para encontrar el nombre de la Receta con Mas Ingredientes(RMI) 
   así como también el tipo al que pertenece */
void encuentraRMI(RECETARIO r, char *tipoRMI, char *nomRMI)
{
   int cont, may = 0;
   LISTA_RECE auxRec;
   LISTA_INGRE auxIngre;

   while (r)
   {
      auxRec = r->cabRece;
      while (auxRec)
      {
         cont = 0;
         auxIngre = auxRec->cabIngre;
         while (auxIngre)
         {
            cont++;
            auxIngre = auxIngre->sigIngre;
         }
         if(may < cont)
         {
            may = cont;
            strcpy(nomRMI, auxRec->nomRece);
            strcpy(tipoRMI, r->nomTipo);
         }
         auxRec = auxRec->sigRece;
      }
      r = r->sigTipo;
   }
}

/* Función para contar el número de recetas que usan un ingrediente */
int cuentaReceIngre(RECETARIO r, char *ingre)
{
   int cont = 0, flag;
   LISTA_RECE auxRec;
   LISTA_INGRE auxIngre;

   while (r)
   {
      auxRec = r->cabRece;
      while (auxRec)
      {
         auxIngre = auxRec->cabIngre;
         flag = 0;
         while (auxIngre && !flag)
         {
            if(strcmp(auxIngre->nomIngre, ingre) == 0)
            {
               cont++;
               flag = 1;
            }
            auxIngre = auxIngre->sigIngre;
         }
         auxRec = auxRec->sigRece;
      }
      r = r->sigTipo;
   }
   return cont;
}

/* Función para elimina un ingrediente, despues de haber encontrado su receta
   y tipo al que pertenece */
int eliminaIngre(LISTA_INGRE *li, char *ingre)
{
   int res = 0;
   LISTA_INGRE aux, ant;

   aux = *li;
   while (aux && strcmp(aux->nomIngre, ingre) < 0)
   {
      ant = aux;
      aux = aux->sigIngre;
   }
   if(aux && strcmp(aux->nomIngre, ingre) == 0)
   {
      if(aux == *li)
         *li = aux->sigIngre;
      else    
         ant->sigIngre = aux->sigIngre;
      free(aux);
      res = 1;
   }
   return res;
}

/* Función para buscar la receta a la que pertenece el ingrediente a eliminar*/
int eliminaIngreBuscaRece(LISTA_RECE lr, char *rece, char *ingre)
{
   int res = 0;

   for(; lr && strcmp(lr->nomRece, rece) < 0; lr = lr->sigRece);
   if(lr && strcmp(lr->nomRece, rece) == 0)
      res = eliminaIngre(&lr->cabIngre, ingre);

   return res;
}

/* Esta función busca el tipo de receta, al que pertenece la receta del
   ingrediente a eliminar */
int eliminaIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre)
{
   int res = 0;

   for(; r && strcmp(r->nomTipo, tipo) < 0; r = r->sigTipo);
   if(r && strcmp(r->nomTipo, tipo) == 0)
      res = eliminaIngreBuscaRece(r->cabRece, rece, ingre);

   return res;
}

/* Función para eliminar todos los ingredientes de una receta */
void eliminaIngredientes(LISTA_INGRE *li)
{
   LISTA_INGRE aux;

   while(*li)
   {
      aux = *li;
      *li = aux->sigIngre;
      free(aux);
   }
}

/* Función para buscar una receta y poder eliminar sus ingredientes */
int eliminaXreceta(LISTA_RECE *lr, char *rece)
{
   int res = 0;
   LISTA_RECE aux;

   for(aux = *lr; aux && strcmp(aux->nomRece, rece) < 0; aux = aux->sigRece);
   if(aux && strcmp(aux->nomRece, rece) == 0)
   {
      eliminaIngredientes(&aux->cabIngre);
      res = 1;
   }

   return res;
}

/* Función para buscar tipo de la receta a eliminar */
int eliminaReceta(RECETARIO r, char *tipo, char *rece)
{
   int res = 0;

   for(; r && strcmp(r->nomTipo, tipo) < 0; r = r->sigTipo);
   if(r && strcmp(r->nomTipo, tipo) == 0)
   {
      eliminaXreceta(&r->cabRece, rece);
      res = 1;
   }

   return res;
}

/* Funciòn para eliminar las todas las recetas de un tipo, eliminando
   previamente todos los ingredientes
   */
void eliminaRecetas(LISTA_RECE lr)
{
   while(lr)
   {
      eliminaIngredientes(&lr->cabIngre);
      lr = lr->sigRece;
   }
}

/* Función para eliminar un tipo de receta */
int eliminaTipo(RECETARIO *r, char *tipo)
{
   int res = 0;
   RECETARIO auxRecetario, ant;
   LISTA_RECE auxRece;

   for(auxRecetario = *r; auxRecetario && strcmp((*r)->nomTipo, tipo) < 0; ant = auxRecetario, auxRecetario = auxRecetario->sigTipo);
   if(auxRecetario && strcmp(auxRecetario->nomTipo, tipo) == 0)
   {
      eliminaRecetas(auxRecetario->cabRece);
      
      while (auxRecetario->cabRece)
      {
         auxRece = auxRecetario->cabRece;
         auxRecetario->cabRece = auxRece->sigRece;
         free(auxRece);
      }

      if(auxRecetario == *r)
         *r = auxRecetario->sigTipo;
      else    
         ant->sigTipo = auxRecetario->sigTipo;
      free(auxRecetario);

      res = 1;
   }

   return res;
}

/* Función para eliminar un recetario completo */
void eliminaRecetario(RECETARIO *r)
{
   LISTA_RECE auxReceta;
   RECETARIO auxCab;

   while (*r)
   {
      eliminaRecetas((*r)->cabRece);
      while ((*r)->cabRece)
      {
         auxReceta = (*r)->cabRece;
         (*r)->cabRece = auxReceta->sigRece;
         free(auxReceta);
      }
      auxCab = *r;
      *r = auxCab->sigTipo;
      free(auxCab);
   }
}