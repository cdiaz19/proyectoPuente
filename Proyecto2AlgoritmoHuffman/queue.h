/*
 *      Proyecto 2 de Sistemas Operativos
 *      queue.h
 *      
 *      David Ugalde
 *      Cristian Díaz
 * 
 */

#include <stdio.h> 
#include <stdlib.h>

typedef struct Data{
	char * value;
	int frequency;
}Data;

typedef struct Node{
	Data data;
	struct Node * next;
	struct Node * left;
	struct Node * right;
}Node;

typedef struct Queue{
	struct Node * first;
	struct Node * last;
	int size;
}Queue;

Node * createNode(Data data){
		Node * node = (Node*)malloc(sizeof(Node));
		node->left = NULL;
		node->right = NULL;
		node->next = NULL;
		node->data = data;
		return node;
}

Queue * createQueue(){
	Queue * queue = (Queue*)malloc(sizeof(Queue));
	queue->first = NULL;
	queue->last = NULL;
	queue->size = 0;
	return queue;
}

void enqueue(Queue * queue, Data data){
	if(!queue->first){
		queue->first = createNode(data);
		queue->last = queue->first;
	}
	else{
		queue->last->next = createNode(data);
		queue->last = queue->last->next;	
	}
	queue->size++;
}

void enqueueNode(Queue * queue, Node * node){
	if(!queue->first){
		queue->first = node;
		queue->last = queue->first;
	}
	else{
		queue->last->next = node;
		queue->last = queue->last->next;	
	}
	queue->size++;
}

Node * dequeue(Queue * queue){
	Node * aux = queue->first;
	if(queue->first != NULL){
		queue->first = queue->first->next;
		aux->next = NULL;
	}
	queue->size--;
	return aux;
}
