/*
 *      Proyecto 0 de Sistemas Operativos
 *      OficialProyecto0.c
 *      
 *      Cristian Díaz
 *      Alonso Aguilar
 * 
 */
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#define BRIDGE_DIRECTION_EAST 0x01
#define BRIDGE_DIRECTION_WEST 0x02

int longbridge;
int arrivetime;
int traveltime;
int semaphore;
int carsOE;
int carsEO;

/* Estructuras */
typedef struct StructBridge {
  int cars;
  int direction;
  /*int oficial;*/
  pthread_mutex_t mutex;
  pthread_cond_t empty;
} QStructBridge;

static QStructBridge shared_bridgeo = {
  .cars = 0,
  .direction = BRIDGE_DIRECTION_WEST,
  /*.oficial = 0,*/
  .mutex = PTHREAD_MUTEX_INITIALIZER,
  .empty = PTHREAD_COND_INITIALIZER,
};
 
struct nodo{
  pthread_t dato;
  struct nodo*siguiente;
};

/*
Metodos de la cola de carros
*/


struct nodo * agregar(struct nodo *cola,pthread_t valor){
  struct  nodo *temporal=calloc(sizeof(struct nodo),1);
  struct nodo *pivote;
  temporal->dato=valor;
  
  if (cola!=NULL){
    pivote=cola;
      while(pivote->siguiente!=NULL){
        pivote=pivote->siguiente;
      }
      pivote->siguiente=temporal;
      printf("Agregando hilo despues de %i\n",pivote->dato);
      return cola;
  }
  else{
    printf("Agregando el primer hilo %i\n",temporal->dato);
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



static void arrive(QStructBridge *bridge, int direction,struct nodo* n) {
  
  /*bridge->oficial++;*/
  clock_t CPU_time = clock();
  

  if(direction == 1) { fprintf(stderr, "Carro esperando en Este %ju\n", CPU_time); }
  if(direction == 2) { fprintf(stderr, "Carro esperando en Oeste %ju\n", CPU_time); }
  pthread_mutex_lock(&bridge->mutex);
  
  while ((bridge->cars > 0) && (bridge->cars > 1 || bridge->direction != direction /*|| bridge->oficial > 4*/)) {
    pthread_cond_wait(&bridge->empty, &bridge->mutex);
    /*bridge->oficial--;*/
  }
  if ((bridge->cars == 0) /*|| (bridge->oficial>3)*/) {
    bridge->direction = direction;
    /*bridge->oficial=0;*/
  }
    
  bridge->cars++;
  pthread_mutex_unlock(&bridge->mutex);
}
static void cross(QStructBridge *bridge) {
  clock_t CPU_time = clock();

  printf("%s\n", "-------------------------" );
  if(bridge->direction == 1) { fprintf(stderr, "Carro entra del Este %ju\n", CPU_time); }
  if(bridge->direction == 2) { fprintf(stderr, "Carro entra del Oeste %ju\n", CPU_time); }
  sleep(2);
}

static void leave(QStructBridge *bridge) {
  clock_t CPU_time = clock();
  pthread_mutex_lock(&bridge->mutex);
  bridge->cars--;
  pthread_cond_signal(&bridge->empty);
  pthread_mutex_unlock(&bridge->mutex);
  
  if(bridge->direction == 1) { fprintf(stderr, "***Carro sale por Oeste %ju***\n", CPU_time); }
  if(bridge->direction == 2) { fprintf(stderr, "***Carro sale por Este %ju***\n", CPU_time); }
}

static void drive(QStructBridge *bridge, int direction) {
  arrive(bridge, direction);
  cross(bridge);
  leave(bridge);
}

static void* east(void *data) {
  drive((QStructBridge *) data, BRIDGE_DIRECTION_EAST);
  return NULL;
}

static void* west(void *data) {
  drive((QStructBridge *) data, BRIDGE_DIRECTION_WEST);
  return NULL;
}
static int runThread(int carsOE, int carsEO) {
  srand(time(NULL));
  int i = 0, n = carsEO + carsOE;
  pthread_t thread[n];
  int random = rand() % 2 + 1;; 
  int cOE = carsOE;
  int cEO = carsEO;

 struct nodo* colaE=NULL;
 struct nodo* colaW=NULL;
 struct pthread_t proximo=NULL;

  while (i < n) { 
    if(random == 2 && cEO > 0) {
      if (pthread_create(&thread[i], NULL,
                /*west,*/ &shared_bridgeo)) {
        fprintf(stderr, "Error al crear hilo\n");
        return EXIT_FAILURE;
      }
      cEO--;
      i++;
      colaW=agregar(colaW,&thread[i]);
      
     
     
    }
    if(random == 1 && cOE > 0) {            
      if (pthread_create(&thread[i], NULL,
                east, &shared_bridgeo)) {
        fprintf(stderr, "Error al crear hilo\n");
        return EXIT_FAILURE;
      }            
      cOE--;
      i++;
      colaE=agregar(colaE,&thread[i]);
      
      
    }            
    random = rand() % 2 + 1;  
  }

  for (i = 0; i < n; i++) {
    if (thread[i]) pthread_join(thread[i], NULL);
  }
  return EXIT_SUCCESS;
}

void loadArchivo() {
  FILE *ptr_file;
  char buf;
  int variables[6];
  int i = 0;
  int decimal = 10;
  int numeroanterior;

  ptr_file = fopen("Parametros", "r");
  if (!ptr_file) {
    printf("No se encontro el archivo");
    return;
  }

  while (feof(ptr_file) == 0) {
    buf = fgetc(ptr_file);
    if (buf == ' ') {
      numeroanterior = 0;
      decimal = 10;
      i++;
      
    } else {
      if (isdigit(buf)) {
        numeroanterior = buf;
        variables[i] = numeroanterior;
      }
    }
  }

  fclose(ptr_file);
  longbridge = variables[0];
  arrivetime = variables[1];
  traveltime = variables[2];
  semaphore = variables[3];
  carsOE = variables[4];
  carsEO = variables[5];
}

int main(void) {

  loadArchivo();
  int c, carOE = carsOE, carEO = carsEO;

  return runThread(carOE, carEO);
}
