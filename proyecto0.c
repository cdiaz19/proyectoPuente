/*
 *      proyecto0.c
 *      
 *      Cristian Díaz Jiménez
 * 
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define numCarsOE 12
#define numCarsEO 10
#define NumVector 8

static pthread_mutex_t mutexes[NumVector];

/* Estructuras */
typedef struct StructDriver {
    int type;
    int direction;
} QStructDriver;

typedef struct StructBridge {
    int size;
} QStructBridge;

/* Metodos */
int randomType(){
  return (rand() % 2);
}

void *createDiverThread(QStructDriver *QSEst) {

  QSEst->type = randomType(); 
  QSEst->direction = 1;
  printf( "Tipo: %i - Direccion: %i. \n", QSEst->type, QSEst->direction );
}

void bridgeMutex(int arra1[]) {
  //Crea el vector de Mutex
  printf( "\nVector de Mutex. \n" );
  for (int i = 0; i < NumVector; i++) {
    pthread_mutex_init(&mutexes[i], NULL);
  }

  for (int i=0; i < numCarsOE; i++) {
    printf("%i ", arra1[i] );
  }
}

int main(void) {
  srand(time(NULL));
  QStructDriver QSEst;
  pthread_t thread;
  int arrayDriverOE[numCarsOE];
  int arrayDriverEO[numCarsEO];

  //Realiza hilos de Carros Oeste - Este
  printf( "Se Crean los %i Carros de [ O-E ]. \n", numCarsOE );

  for ( int i = 0 ; i < numCarsOE ; i ++ ) {
    arrayDriverOE[i] = pthread_create( &thread, NULL, createDiverThread, (void*) &QSEst );
    pthread_join ( thread , NULL );
  }

  //Realiza hilos de Carros Oeste - Este
  printf( "\nSe Crean los %i Carros de [ E-O ]. \n", numCarsEO );
  for ( int i = 0 ; i < numCarsEO ; i ++ ) {
    arrayDriverEO[i] = pthread_create ( &thread, NULL, createDiverThread, (void*) &QSEst );
    pthread_join ( thread, NULL );
  }

  bridgeMutex(arrayDriverOE);

  return 0;
}
