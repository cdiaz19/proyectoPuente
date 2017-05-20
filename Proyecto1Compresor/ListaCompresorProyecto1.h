/*
 *      Proyecto 1 de Sistemas Operativos
 *      ListaCompresorProyecto1.c
 *      
 *      Cristian Díaz
 *      Alonso Aguilar
 * 
 */

#include <stdlib.h>
#include <stdio.h>

/* Estructuras */
typedef struct StructLetter {
  char value;
  int frequency;
} StructLetter;

typedef struct _nodo{
   StructLetter letter;
   struct _nodo *siguiente;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

/* Metodos de ListaCompresorProyecto1 */

void Insertar(Lista *l, char value, int frequency);
int ListaVacia(Lista l);
void MostrarLista(Lista l);
StructLetter setData(char value, int frequency);

/*Desarrollo de metodos de lista*/

StructLetter setData(char value, int frequency){
  StructLetter data;
  data.value = value;
  data.frequency = frequency;
  return data;
}

void Insertar(Lista *lista,  char value, int frequency) {
   pNodo nuevo, anterior;
 
   /* Crear un nodo nuevo */
   nuevo = (pNodo)malloc(sizeof(tipoNodo));
   nuevo->letter = setData(value, frequency);
   
   /* Si la lista está vacía */
   if(ListaVacia(*lista) || (*lista)->letter.frequency > frequency) {
      /* Añadimos la lista a continuación del nuevo nodo */
      nuevo->siguiente = *lista; 
      /* Ahora, el comienzo de nuestra lista es en nuevo nodo */
      *lista = nuevo;
   } else {
      /* Buscar el nodo de valor menor a v */
      anterior = *lista;
      /* Avanzamos hasta el último elemento o hasta que el siguiente tenga 
         un valor mayor que v */
      while(anterior->siguiente && anterior->siguiente->letter.frequency <= frequency) 
         anterior = anterior->siguiente;
      /* Insertamos el nuevo nodo después del nodo anterior */
      nuevo->siguiente = anterior->siguiente;
      anterior->siguiente = nuevo;
   }
}

int ListaVacia(Lista lista) {
   return (lista == NULL);
}

void MostrarLista(Lista lista) {
  pNodo nodo = lista;

  if(ListaVacia(lista)) printf("Lista vacía\n");
  else {
    while(nodo) {
      printf("Letra: %c - Frecuencia: %i. \n",nodo->letter.value, nodo->letter.frequency);
      nodo = nodo->siguiente;
    }
    printf("\n");
  }
}
