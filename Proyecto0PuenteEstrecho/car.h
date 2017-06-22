#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h> 

/* Estructuras */
typedef struct Car{
	int speed;
	float distance;
	int varSpeed;
	int num;
	int side;
	int pos;
} Car;

/* Globales */

struct Car;

/* Declaracion de Metodos */

int randomSpeed(int min, int max);
Car * createCar(int num, int side, int min, int max);

/* Desarrollo de Metodos */

int randomSpeed(int min, int max) {
	return min + (rand() % (max+1 - min));
}

Car * createCar(int num, int side, int min, int max) {
	Car * car = (Car*)malloc(sizeof(Car));
	car->speed = randomSpeed(min,max);
	car->distance = 0;
	car->varSpeed = 0; 
	car->num = num;
	car->side = side;
	return car;
}
