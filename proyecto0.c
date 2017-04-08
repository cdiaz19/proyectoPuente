/*
 *      proyecto0.c
 *      
 *      Cristian Díaz Jiménez
 * 
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct StructDriver {
    int type;
    int direction;

} StructDriver;

void createDiverArrays(int numCars) {

  for(int i=0;i < numCars; i++) {
    typeDriver();
  }
}

void typeDriver() {
 
  StructDriver QSEst;
  QSEst.type = randomType(); // Asigna los random del tipo de carro,[ 0 -> Normal / 1 -> Ambulancia ]
  QSEst.direction = randomType(); // Asigna los random de la direccion del carro,[ 0 -> O-E / 1 -> E-O ]

  printf( "Datos del carro creado: %i %i. \n", QSEst.type, QSEst.direction );
}

int randomType(){
  return (rand() % 2);
}

int main(void) {
  srand(time(NULL));
  int numCars = 0;

  printf( "Cantidad de Carros a crear: " );
  scanf( "%i", &numCars );

  createDiverArrays(numCars);

  return 0;
}
