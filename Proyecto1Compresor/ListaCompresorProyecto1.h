/*
 *      Proyecto 1 de Sistemas Operativos
 *      ListaCompresorProyecto1.h
 *      
 *      Cristian Díaz
 *      Alonso Aguilar
 * 
 */

#include <stdlib.h>
#include <stdio.h>

/* Estructuras */
typedef struct StructLetter {
  char value;
  int frequency;
} StructLetter;

typedef struct _nodo{
  StructLetter letter;
  struct _nodo *siguiente;
} tipoNodo;

// A Huffman tree node
struct MinHeapNode {
  char data;  // One of the input characters
  unsigned freq;  // Frequency of the character
  struct MinHeapNode *left, *right; // Left and right child of this node
};

// A Min Heap:  Collection of min heap (or Hufmman tree) nodes
struct MinHeap {
  unsigned size;    // Current size of min heap
  unsigned capacity;   // capacity of min heap
  struct MinHeapNode **array;  // Attay of minheap node pointers
};

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

/* Metodos de ListaCompresorProyecto1 */

StructLetter setData(char value, int frequency);
void Insertar(Lista *l, char value, int frequency);
int ListaVacia(Lista l);
void MostrarLista(Lista l);

/*Desarrollo de metodos de lista*/

// A utility function allocate a new min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp =
          (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// A utility function to create a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;  // current size is 0
    minHeap->capacity = capacity;
    minHeap->array =
     (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// A utility function to swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// The standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx , Lista lista) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->lista[left]->freq < minHeap->lista[smallest]->freq)
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->lista[right]->freq < minHeap->lista[smallest]->freq)
      smallest = right;
 
    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->lista[smallest], &minHeap->lista[idx]);
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// A standard function to extract minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}






















































StructLetter setData(char value, int frequency) {
  StructLetter data;
  data.value = value;
  data.frequency = frequency;
  return data;
}

void Insertar(Lista *lista,  char value, int frequency) {
  pNodo nuevo, anterior;
 
  /* Crear un nodo nuevo */
  nuevo = (pNodo)malloc(sizeof(tipoNodo));
  nuevo->letter = setData(value, frequency);
   
  /* Si la lista está vacía */
  if(ListaVacia(*lista) || (*lista)->letter.frequency > frequency) {
    /* Añadimos la lista a continuación del nuevo nodo */
    nuevo->siguiente = *lista; 
    /* Ahora, el comienzo de nuestra lista es en nuevo nodo */
    *lista = nuevo;
  } else {
    /* Buscar el nodo de valor menor a v */
    anterior = *lista;
    /* Avanzamos hasta el último elemento o hasta que el siguiente tenga 
      un valor mayor que v */
    while(anterior->siguiente && anterior->siguiente->letter.frequency <= frequency) 
      anterior = anterior->siguiente;
    /* Insertamos el nuevo nodo después del nodo anterior */
    nuevo->siguiente = anterior->siguiente;
    anterior->siguiente = nuevo;
  }
}

int ListaVacia(Lista lista) { return (lista == NULL); }

void MostrarLista(Lista lista) {
  pNodo nodo = lista; 

  if(ListaVacia(lista)) printf("Lista vacía\n");
  else {
    while(nodo) {
      printf("Letra: %c - Frecuencia: %i. \n",nodo->letter.value, nodo->letter.frequency);
      nodo = nodo->siguiente;
    }
    printf("\n");
  }
}
