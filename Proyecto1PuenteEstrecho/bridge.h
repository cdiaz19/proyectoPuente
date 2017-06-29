/*
 *      Proyecto 1 de Sistemas Operativos
 *      bridge.c
 *      
 *      David Ugalde
 *      Cristian Díaz
 * 
 */

#include "queue.h"

/* Estructuras */

typedef struct Bridge{
	int size;
	int ew;
	int we;
	Queue * carQueue;
} Bridge;

/* Declaracion de Metodos */

Bridge createBridge(int size);

/* Desarrollo de Metodos */

Bridge createBridge(int size) {
	Bridge bridge;
	bridge.size = size;
	bridge.ew = 0;
	bridge.we = 0;
	bridge.carQueue = createQueue(size);
	return bridge;
}
