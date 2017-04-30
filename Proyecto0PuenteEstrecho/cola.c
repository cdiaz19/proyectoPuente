#include <stdio.h>

#include <stdlib.h>

#include <time.h>

struct nodo{
	int dato;
	struct nodo*siguiente;
};
struct nodo* agregar(struct nodo *cola,int valor);

struct nodo* siguiente(struct nodo **cola);



int main(){
struct nodo* cola=NULL;
struct nodo *proximo=NULL;
/*srand(time(NULL));*/
	cola=agregar(cola,1);
	cola=agregar(cola,2);
	cola=agregar(cola,3);
	cola=agregar(cola,4);
	proximo=siguiente(&cola);

	cola=agregar(cola,proximo->dato);
	
	
	proximo=siguiente(&cola);
	cola=agregar(cola,proximo->dato);

	proximo=siguiente(&cola);
	printf("Elemento: %i\n",proximo->dato);
	proximo=siguiente(&cola);
	printf("Elemento: %i\n",proximo->dato);
	proximo=siguiente(&cola);
	printf("Elemento: %i\n",proximo->dato);
	proximo=siguiente(&cola);
	printf("Elemento: %i\n",proximo->dato);

	return 0;
}

struct nodo * agregar(struct nodo *cola,int valor){
	struct  nodo *temporal=calloc(sizeof(struct nodo),1);
	struct nodo *pivote;
	temporal->dato=valor;
	
	if (cola!=NULL){
		pivote=cola;
      while(pivote->siguiente!=NULL){
      	pivote=pivote->siguiente;
      }
      pivote->siguiente=temporal;
      printf("Agregando valor despues de %i\n",pivote->dato);
      return cola;
	}
	else{
		printf("Agregando el primer valor %i\n",temporal->dato);
      return temporal;

	}
}
struct nodo *siguiente(struct nodo **cola){
    struct nodo *real=cola[0];
    struct nodo *temporal;
    if(real==NULL){
    	printf("No quedan elementos en la cola  \n");
    	return NULL;
    }
    else{
    	temporal=real;
    	cola[0]=real->siguiente;
    	real->siguiente=NULL;
    	return temporal;
    }

}
