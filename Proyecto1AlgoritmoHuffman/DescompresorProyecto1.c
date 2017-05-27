/*
 *      Proyecto 1 de Sistemas Operativos
 *      ArbolCompresorProyecto1.h
 *      
 *      Cristian Díaz
 *      Alonso Aguilar
 * 
 */



#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
   char letra;             //Letra
   unsigned long int bits; //Codigo
   char nbits;             /* Número de bits de la codificación */
   nodo *cero;            /* Rama cero de un árbol */
   nodo *uno;             /* Puntero a la rama uno de un árbol */
} tipoNodo;                

int main(int argc, char *argv[]){

   tipoNodo *Arbol;        /* Arbol de codificación */
   long int Longitud;      /* Longitud de fichero */
   int nElementos;         /* Elementos de árbol */
   unsigned long int bits; /* Almacenamiento de bits para decodificación */
   FILE *fe, *fs;          /* entrada y salida*/

   tipoNodo *p, *q;        /* variables auxiliares */
   unsigned char a;
   int i, j;









}

