/*
 *      proyecto0.c
 *      
 *      Cristian Díaz Jiménez
 * 
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* Estructuras */
typedef struct StructDriver {
    int type;
    int direction;
} StructDriver;

/* Metodos */
int randomType(){
  return (rand() % 2); // Asigna los random 0 entre 1.
}

void createDiverArrays(int numCarsOE, int numCarsEO) {

  //Realiza array de Carros Oeste - Este
  printf( "Se Crean los %i Carros de [ O-E ]. \n", numCarsOE );
  StructDriver driversOE[numCarsOE];
  for(int i=0;i < numCarsOE; i++) {
    StructDriver QSEst;
    QSEst.type = randomType(); // Asigna los random del tipo de carro,[ 0 -> Normal / 1 -> Ambulancia ]
    QSEst.direction = 1;
    driversOE[i] = QSEst;
  }

  for (int i = 0; i < numCarsOE; i++) {
      printf( "Tipo: %i - Direccion: %i. \n", driversOE[i].type, driversOE[i].direction );
    }

  //Realiza array de Carros Oeste - Este
  printf( "Se Crean los %i Carros de [ E-O ]. \n", numCarsEO );
  StructDriver driversEO[numCarsEO];
  for(int i=0;i < numCarsEO; i++) {
    StructDriver QSEst;
    QSEst.type = randomType(); // Asigna los random del tipo de carro,[ 0 -> Normal / 1 -> Ambulancia ]
    QSEst.direction = 2;
    driversEO[i] = QSEst;
  }

  for (int i = 0; i < numCarsEO; i++) {
      printf( "Tipo: %i - Direccion: %i. \n", driversEO[i].type, driversEO[i].direction );
    }
}

int main(void) {
  srand(time(NULL));
  int numCarsOE = 0;
  int numCarsEO = 0;

  printf( "Cantidad de Carros con orientacion Oeste - Este: " );
  scanf( "%i", &numCarsOE );
  printf( "Cantidad de Carros con orientacion Este - Oeste: " );
  scanf( "%i", &numCarsEO );

  //Crea los Arreglos de Carros
  createDiverArrays(numCarsOE, numCarsEO);

  return 0;
}
