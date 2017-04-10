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

#define numCarsOE 6
#define numCarsEO 6

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Estructuras */
typedef struct StructDriver {
    int type;
    int direction;
} QStructDriver;

/* Metodos */
int randomType(){
  return (rand() % 2); // Asigna los random 0 entre 1.
}

void *createDiverThread(QStructDriver *QSEst) {

  QSEst->type = randomType(); // Asigna los random del tipo de carro,[ 0 -> Normal / 1 -> Ambulancia ]
  QSEst->direction = 1;
  printf( "Tipo: %i - Direccion: %i. \n", QSEst->type, QSEst->direction );
}

int main(void) {
  srand(time(NULL));
  pthread_t thread;
  int arrayDriverOE[numCarsOE];
  int arrayDriverEO[numCarsEO]; 
  QStructDriver QSEst;

  //Realiza hilos de Carros Oeste - Este
  printf( "Se Crean los %i Carros de [ O-E ]. \n", numCarsOE );

  for ( int i = 0 ; i < numCarsOE ; i ++ ) {
    arrayDriverOE[i] = pthread_create( &thread, NULL, createDiverThread, (void*) &QSEst );
    pthread_join ( thread , NULL );
  }

  //Realiza hilos de Carros Oeste - Este
  printf( "\nSe Crean los %i Carros de [ E-O ]. \n", numCarsEO );
  for ( int i = 0 ; i < numCarsEO ; i ++ ) {
    arrayDriverEO[i] = pthread_create ( &thread, NULL, createDiverThread, (void*) &QSEst ) ;
    pthread_join ( thread, NULL );
  }

  return 0;
}
