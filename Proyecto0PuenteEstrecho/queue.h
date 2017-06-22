#include "car.h"
#include <pthread.h>

/* Estructuras */
typedef struct Node{
	Car * car;
	struct Node * next;
}Node;

typedef struct Queue{
	struct Node * first;
	struct Node * last;
	int size;
	pthread_mutex_t wait;
}Queue;

/* Declaracion de Metodos */

Node * createNode(Car * car);
Queue * createQueue();
void enqueue(Queue * queue, Car * car);
void update(Queue * queue);
void update(Queue * queue);
Car * dequeue(Queue * queue);
Car * get(Queue * queue, int pos);

/* Desarrollo de Metodos */

Node * createNode(Car * car) {
	Node * node = (Node*)malloc(sizeof(Node));
	node->next = NULL;
	node->car = car;
	return node;
}

Queue * createQueue() {
	Queue * queue = (Queue*)malloc(sizeof(Queue));
	pthread_mutexattr_t Attr;
	queue->first = NULL;
	queue->last = NULL;
	queue->size = 0;
	pthread_mutexattr_init(&Attr);
	pthread_mutexattr_settype(&Attr, PTHREAD_MUTEX_ERRORCHECK);
	pthread_mutex_init(&queue->wait, &Attr);
	return queue;
}

void enqueue(Queue * queue, Car * car) {
	car->pos = queue->size;
	if(!queue->first){
		queue->first = createNode(car);
		queue->last = queue->first;
	}
	else{
		queue->last->next = createNode(car);
		queue->last = queue->last->next;	
	}
	queue->size++;
}

void update(Queue * queue) {
	Node * aux = queue->first;
	Car * car;
	int i;
	for(i = 0; i < queue->size; i++){
		car = aux->car;
		car->pos--;
		aux = aux->next;
	}
}

Car * dequeue(Queue * queue) {
	pthread_mutex_lock(&queue->wait);
	if(queue->size > 0){
		Node * aux = queue->first;
		Car * car = aux->car;
		queue->first = queue->first->next;
		queue->size--;
		free(aux);
		update(queue);
		pthread_mutex_unlock(&queue->wait);	
		return car;
	}
	else{
		return NULL;
	}
}

Car * get(Queue * queue, int pos) {
	Node * aux = queue->first;
	int i;
	if(aux){
		if(pos > -1 && pos < queue->size){
			for(i = 0; i < pos; i++){
				aux = aux->next;
			}
			return aux->car;
		}
		else{
			return NULL;
		}
	}
	else{
		return NULL;
	}
}
