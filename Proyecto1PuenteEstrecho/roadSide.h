/*
 *      Proyecto 1 de Sistemas Operativos
 *      roadSide.h
 *      
 *      David Ugalde
 *      Cristian Díaz
 * 
 */

#include <pthread.h>

typedef struct RoadSide{
	pthread_mutex_t wait;
	int createdCars;
	int next;
} RoadSide;

RoadSide createRoadSide(){
	pthread_mutexattr_t Attr;
	RoadSide roadSide;
	roadSide.createdCars = 0;
	roadSide.next = 0;
	pthread_mutex_init(&roadSide.wait, NULL);
	pthread_mutexattr_init(&Attr);
	pthread_mutexattr_settype(&Attr, PTHREAD_MUTEX_ERRORCHECK);
	pthread_mutex_init(&roadSide.wait, &Attr);
	return roadSide;
}
