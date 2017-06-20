#include"queue.h"
//Puente
//size = tamaño del puente
typedef struct Bridge{
	int size;
	int ew;
	int we;
	Queue * carQueue;
} Bridge;

//Constructor del puente
Bridge createBridge(int size){
	Bridge bridge;
	bridge.size = size;
	bridge.ew = 0;
	bridge.we = 0;
	bridge.carQueue = createQueue(size);
	return bridge;
}










