#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h> 
//Carro
//speed = Velocidad a la que se mueve (mps)
//distance = posicion en carretera(distancia en m)
//varSpeed = Velocidad actual
//num = numero de carro
struct Car;

typedef struct Car{
	int speed;
	float distance;
	int varSpeed;
	int num;
	int side;
	int pos;
} Car;

//Velocidad generada aleatoriamente
int randomSpeed(int min, int max){
	return min + (rand() % (max+1 - min));
}

//Constructor de carro
Car * createCar(int num, int side, int min, int max){
	Car * car = (Car*)malloc(sizeof(Car));
	car->speed = randomSpeed(min,max);
	car->distance = 0;
	car->varSpeed = 0; 
	car->num = num;
	car->side = side;
	return car;
}












