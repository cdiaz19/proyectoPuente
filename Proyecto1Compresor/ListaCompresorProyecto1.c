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
typedef struct _nodo
{
    int valor;
   struct _nodo *siguiente;

   //char letra;      /* Letra a la que hace referencia el nodo */
   //int frecuencia;  /* veces que aparece la letra en el texto o las letras */
                    /* de los nodos de las ramas cero y uno */
   //_nodo *sig;      /* Puntero a siguiente nodo de una lista enlazada */
   //_nodo *cero;     /* Puntero a la rama cero de un árbol */
   //_nodo *uno;      /* Puntero a la rama uno de un árbol */
} tipoNodo;         /* Nombre de tipo */


typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

/*Metodos de la lista*/

void Insertar(Lista *l,int v);
void Borrar(Lista *l,int v);
int ListaVacia(Lista l);
 
void BorrarLista(Lista *);
void MostrarLista(Lista l);

/*Desarrollo de metodos de lista*/

void Insertar(Lista *lista, int v) {
   pNodo nuevo, anterior;
 
   /* Crear un nodo nuevo */
   nuevo = (pNodo)malloc(sizeof(tipoNodo));
   nuevo->valor = v;
   
   /* Si la lista está vacía */
   if(ListaVacia(*lista) || (*lista)->valor > v) {
      /* Añadimos la lista a continuación del nuevo nodo */
      nuevo->siguiente = *lista; 
      /* Ahora, el comienzo de nuestra lista es en nuevo nodo */
      *lista = nuevo;
   } else {
      /* Buscar el nodo de valor menor a v */
      anterior = *lista;
      /* Avanzamos hasta el último elemento o hasta que el siguiente tenga 
         un valor mayor que v */
      while(anterior->siguiente && anterior->siguiente->valor <= v) 
         anterior = anterior->siguiente;
      /* Insertamos el nuevo nodo después del nodo anterior */
      nuevo->siguiente = anterior->siguiente;
      anterior->siguiente = nuevo;
   }
}

void Borrar(Lista *lista, int v) {
   pNodo anterior, nodo;
   
   nodo = *lista;
   anterior = NULL;
   while(nodo && nodo->valor < v) {
      anterior = nodo; 
      nodo = nodo->siguiente;
   }
   if(!nodo || nodo->valor != v) return;
   else { /* Borrar el nodo */
      if(!anterior) /* Primer elemento */
         *lista = nodo->siguiente;
      else  /* un elemento cualquiera */
         anterior->siguiente = nodo->siguiente;
      free(nodo);
   }   
}

int ListaVacia(Lista lista) {
   return (lista == NULL);
}

void BorrarLista(Lista *lista) {
   pNodo nodo;

   while(*lista) {
      nodo = *lista;
      *lista = nodo->siguiente;
      free(nodo);
   }
}

void MostrarLista(Lista lista) {
   pNodo nodo = lista;

   if(ListaVacia(lista)) printf("Lista vacía\n");
   else {
      while(nodo) {
         printf("%d -> ", nodo->valor);
         nodo = nodo->siguiente;
     }
     printf("\n");
   }
}
//main 
int main() {
   Lista lista = NULL;
   pNodo p;
 
   Insertar(&lista, 20);
   Insertar(&lista, 10);
   Insertar(&lista, 40);
   Insertar(&lista, 15);
   Insertar(&lista, 22);
   Insertar(&lista, 14);
   Insertar(&lista, 99);
   Insertar(&lista, 28);
   Insertar(&lista, 76);
   Insertar(&lista, 98);
   Insertar(&lista, 5);
   Insertar(&lista, 12);
   Insertar(&lista, 33);
   Insertar(&lista, 44);
  
   MostrarLista(lista);

   Borrar(&lista, 10);
   Borrar(&lista, 15);
   Borrar(&lista, 45);
   Borrar(&lista, 5);
   Borrar(&lista, 99);
   Borrar(&lista, 33);
   Borrar(&lista, 28);
   Borrar(&lista, 40);
   Borrar(&lista, 76);

   MostrarLista(lista);
   
   BorrarLista(&lista);

   return 0;
}

