/*
 *      Proyecto 2 de Sistemas Operativos
 *      tree.h
 *      
 *      David Ugalde
 *      Cristian Díaz
 * 
 */

#include "queue.h"
#include <sys/stat.h>
typedef struct HuffmanCode HuffmanCode;
static pthread_mutex_t mutex;
static HuffmanCode ** codes;
static int * codesCount;

typedef struct HuffmanCode{
	char * value;
	int bits;
	int code;
}HuffmanCode;

typedef struct Tree{
	Node * first;
}Tree;

typedef struct huffmanThreadArgs{
	Node * node;
	int code;
	int bits;
	int i;
}huffmanThreadArgs;

void printTreeNodeRLR(Node * node){
	if(node != NULL){
		if(node->left == NULL && node->right == NULL)
			printf("Value: %d, frequency: %d\n",node->data.value,node->data.frequency);
		else
			printf("Value: NULL, frequency: %d\n",node->data.frequency);
		printTreeNodeRLR(node->left);
		printTreeNodeRLR(node->right);
	}		
}

void printTreeRLR(Tree * tree){
	printTreeNodeRLR(tree->first);
}

void printTreeNodeLRR(Node * node){
	if(node != NULL){
		printTreeNodeLRR(node->left);
		if(node->data.value != NULL)
			printf("Value: %c, frequency: %d\n",node->data.value,node->data.frequency);
		else
			printf("Value: NULL, frequency: %d\n",node->data.frequency);
		printTreeNodeLRR(node->right);
	}		
}

void printTreeLRR(Tree * tree){
	printTreeNodeLRR(tree->first);
}

void printTreeNodeRRL(Node * node){
	if(node != NULL){
		printTreeNodeRRL(node->left);
		if(node->data.value != NULL)
			printf("Value: %c, frequency: %d\n",node->data.value,node->data.frequency);
		else
			printf("Value: NULL, frequency: %d\n",node->data.frequency);
		printTreeNodeRRL(node->right);
	}		
}

void printTreeRRL(Tree * tree){
	printTreeNodeRRL(tree->first);
}

Node * returnNode(Queue * q1,Queue * q2){
	Node * node;
	if(q1->size > 0 && q2->size > 0){
			if(q1->first->data.frequency > q2->first->data.frequency)
				node = dequeue(q2);
			else
				node = dequeue(q1);
		}
		else if(q1->size > 0){
			node = dequeue(q1);
		}
		else{
			node = dequeue(q2);
		}
		return node;
}

Node * mergeNode(Node * n1, Node * n2){
	Node * aux;
	aux = (Node*)malloc(sizeof(Node));
	aux->right = n2;
	aux->left = n1;
	aux->data.value = NULL;
	aux->data.frequency = n1->data.frequency + n2->data.frequency;
	return aux;
}

Tree * createTree(Data * vec, int size){
	Tree * tree = (Tree*)malloc(sizeof(Tree));
	Queue * q1, * q2;
	Node * n1, *n2, *aux;
	int i;
	q1 = createQueue();
	q2 = createQueue();
	for(i = 0; i < size; i++){
		enqueue(q1,vec[i]);
	}
	while(q1->size > 0 || q2->size != 1){
		n1 = returnNode(q1,q2);
		n2 = returnNode(q1,q2);
		aux = mergeNode(n1,n2);
		enqueueNode(q2,aux);
	}
	tree->first = dequeue(q2);
	return tree;
}
/*
void HuffmanCodeNode(Node * node,int code, int bits){
	if(node != NULL){
		if(node->left == NULL && node->right == NULL){
			codes[codesCount].value = node->data.value;
			codes[codesCount].bits = bits;
			codes[codesCount].code = code;
			
			codesCount++;
		}
		HuffmanCodeNode(node->left,(code<<1),bits+1);
		HuffmanCodeNode(node->right,((code<<1)+1),bits+1);
	}
}

void HuffmanCodes(Tree * tree,int size){
	codes = (HuffmanCode*) malloc(size * sizeof(HuffmanCode));
	codesCount = 0;
	HuffmanCodeNode(tree->first,0,0);
}
*/


void HuffmanCodeNode(Node * node,int code, int bits, int i){
	if(node != NULL){
		if(node->left == NULL && node->right == NULL){
			codes[i][codesCount[i]].value = node->data.value;
			codes[i][codesCount[i]].bits = bits;
			codes[i][codesCount[i]].code = code;
			codesCount[i]++;
		}
		HuffmanCodeNode(node->left,(code<<1),bits+1,i);
		HuffmanCodeNode(node->right,((code<<1)+1),bits+1,i);
	}
}

void huffmanThread(huffmanThreadArgs * args){
	HuffmanCodeNode(args->node,args->code,args->bits,args->i);
	pthread_exit();
}

void HuffmanCodes(Tree * tree,int size){
	int i,j,y;
	pthread_t threads[4]; 
	huffmanThreadArgs * args; 
	codes = (HuffmanCode**) malloc(4 * sizeof(HuffmanCode*));
	for(i = 0; i < 4; i++){
		codes[i] = (HuffmanCode*) malloc(size * sizeof(HuffmanCode));
	}
	codesCount = (int *)malloc(4*sizeof(int));
	codesCount[0] = 0;
	codesCount[1] = 0;
	codesCount[2] = 0;
	codesCount[3] = 0;
	if(tree->first->left){
		if(!tree->first->left->left && !tree->first->left->right){
			args = (huffmanThreadArgs*)malloc(sizeof(huffmanThreadArgs));
			args->node = tree->first->left;
			args->code = 0;
			args->bits = 1;
			args->i = 0;
			pthread_create(&threads[0],NULL,huffmanThread,args);
		}
		else{
			if(tree->first->left->left){
				args = (huffmanThreadArgs*)malloc(sizeof(huffmanThreadArgs));
				args->node = tree->first->left->left;
				args->code = 0;
				args->bits = 2;
				args->i = 0;
				pthread_create(&threads[0],NULL,huffmanThread,args);
			}
			if(tree->first->left->right){
				args = (huffmanThreadArgs*)malloc(sizeof(huffmanThreadArgs));
				args->node = tree->first->left->right;
				args->code = 1;
				args->bits = 2;
				args->i = 1;
				pthread_create(&threads[1],NULL,huffmanThread,args);
			}
		}
	}
	if(tree->first->right){
		if(!tree->first->right->left && !tree->first->right->right){
			args = (huffmanThreadArgs*)malloc(sizeof(huffmanThreadArgs));
			args->node = tree->first->right;
			args->code = 1;
			args->bits = 1;
			args->i = 2;
			pthread_create(&threads[2],NULL,huffmanThread,args);
		}
		else{
			if(tree->first->right->left){
				args = (huffmanThreadArgs*)malloc(sizeof(huffmanThreadArgs));
				args->node = tree->first->right->left;
				args->code = 2;
				args->bits = 2;
				args->i = 2;
				pthread_create(&threads[2],NULL,huffmanThread,args);
			}
			if(tree->first->right->right){
				args = (huffmanThreadArgs*)malloc(sizeof(huffmanThreadArgs));
				args->node = tree->first->right->right;
				args->code = 3;
				args->bits = 2;
				args->i = 3;
				pthread_create(&threads[3],NULL,huffmanThread,args);
			}
		}
	}
	for(i=0;i<4;i++) {
		pthread_join(threads[i],NULL);			
	}
	j = 1;
	y = 0;
	for(i = codesCount[0]; i < size; i++){
		if(y == codesCount[j]){
			y = 0;
			j++;
		}
		codes[0][i] = codes[j][y];
		y++;
		codesCount[0]++;
	}
}

void makeTreeNode(Node * node ,HuffmanCode * code){
	Node * aux;
	if(code->bits> 0){
		if(code->code>>code->bits-1&1){
			if(node->right == NULL){
				node->right = (Node*)malloc(sizeof(Node));
				node->right->left = NULL;
				node->right->right = NULL;
			}
			aux = node->right;
		}
		else{
			if(node->left == NULL){
				node->left = (Node*)malloc(sizeof(Node));
				node->left->left = NULL;
				node->left->right = NULL;
			}
			aux = node->left;
		}
		aux->data.value = NULL;
		code->bits--;
		makeTreeNode(aux,code);
	}
	else{
		node->data.value = code->value;
	}
}

void makeTree(Tree * tree,HuffmanCode code){
	makeTreeNode(tree->first,&code);
}
