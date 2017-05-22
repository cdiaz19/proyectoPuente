/*
 *      Proyecto 1 de Sistemas Operativos
 *      CompresorProyecto1.c
 *      
 *      Cristian Díaz
 *      Alonso Aguilar
 * 
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ListaCompresorProyecto1.h"

/* Variables Globales */
Lista lista = NULL;
int x = 0;
int y = 0;

/* Metodos de CompresorProyecto1 */
void createLetterArray(char array[]);
void readFile();

/*Desarrollo de metodos de lista*/

void createLetterArray(char array[]) {
  char flag = array[0];
  pNodo nodo = lista;
  int contador = 1;

  while(x < strlen(array)) {

    if(ListaVacia(lista)) {
      int cont = 0;
      for(int j = 0; j < strlen(array); j++) {
        if(array[j] == flag) {
        cont++;
        }
      }
      Insertar(&lista, flag, cont);
    } else {
      pNodo nodo = lista;
      int contador = 0;

      /* Valida si la letra ya se encuentra en la lista */
      while(nodo) {
        if(flag == nodo->letter.value) {
          contador++;
        }
        nodo = nodo->siguiente;
      }

      if(contador != 1) {
      int cont = 0;
      /* Saca la Frecuencia del Valor en el vector */
      for(int j = 0; j < strlen(array); j++) {
        if(array[j] == flag) {
        cont++;
        }
      }
      /* Inserta en la lista */
      Insertar(&lista, flag, cont);
      }
    }
    y++;
    flag = array[y];
    x++;
  }
}

void readFile() {
  FILE *readText = fopen("texto", "r");
  char phrase[100];

  if(!readText){
    printf("El archivo no existe..");
  }
  
  while (feof(readText) == 0) {
    fgets(phrase,100,readText);
    printf("Frase en el Archivo: %s",phrase);
  }

  fclose(readText);
  createLetterArray(phrase);
}

int main () {
  readFile();
  printf("\n ----\n"); 
  MostrarLista(lista);

  return 0;
}
