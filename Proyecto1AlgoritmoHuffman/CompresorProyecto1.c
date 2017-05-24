/*
 *      Proyecto 1 de Sistemas Operativos
 *      ArbolCompresorProyecto1.h
 *      
 *      Cristian Díaz
 *      Alonso Aguilar
 * 
 */

// C program for Huffman Coding
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_TREE_HT 100
 
/* Estructuras */

typedef struct StructLetter {
  char value;
  int frequency;
} StructLetter;

typedef struct _nodo{
  StructLetter letter;
  struct _nodo *siguiente;
} tipoNodo;

struct HufmannTree {
  char data;
  unsigned freq;
  struct MinHeapNode *left, *right;
};

struct MinHeap {
  unsigned size;
  unsigned capacity;
  struct HufmannTree **array;  // Array del Nodo Arbol
};

struct Table{
  char letra;
  int codes[];
};

/* Variables Globales */

int x = 0;
int y = 0;
typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;
typedef struct Table TableCode;
Lista lista = NULL;

/* Metodos de CompresorProyecto1 */

struct HufmannTree* newNode(char data, unsigned freq);
struct MinHeap* createMinHeap(unsigned capacity);
struct HufmannTree* extractMin(struct MinHeap* minHeap);
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);

void Insertar(Lista *lista,  char value, int frequency);
int ListaVacia(Lista lista);
void MostrarLista(Lista lista);
void ordenaAlfabeticamente(Lista *lista, char letra);/*ordenar alfabeticamente la lista*/
int tamLista(Lista lista);
void minHeapify(struct MinHeap* minHeap, int idx);
void insertMinHeap(struct MinHeap* minHeap, struct HufmannTree* minHeapNode);
void buildMinHeap(struct MinHeap* minHeap);
void printArr(int arr[], int n);
void HuffmanCodes(Lista lista, int size);
void printCodes(struct HufmannTree* root, int arr[], int top);
void createLetterArray(char array[]);
void readFile();
void setValuesTable(char data, int code[],int n);
void showTable(TableCode* c1, int n);

/*Desarrollo de metodos de lista*/

StructLetter setData(char value, int frequency) {
  StructLetter data;
  data.value = value;
  data.frequency = frequency;
  return data;
}

struct HufmannTree* newNode(char data, unsigned freq) {
    struct HufmannTree* temp =
          (struct HufmannTree*) malloc(sizeof(struct HufmannTree));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0;  // current size is 0
    minHeap->capacity = capacity;
    minHeap->array =
     (struct HufmannTree**)malloc(minHeap->capacity * sizeof(struct HufmannTree*));
    return minHeap;
}

struct HufmannTree* extractMin(struct MinHeap* minHeap) {
  // Extrae el 1 del arreglo de las letras
  struct HufmannTree* temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];
  --minHeap->size;
  minHeapify(minHeap, 0);
  return temp;
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
  // Crea las hojas del arbol y los inserta al arreglo
  struct MinHeap* minHeap = createMinHeap(size);
  for (int i = 0; i < size; ++i)
    minHeap->array[i] = newNode(data[i], freq[i]);
  minHeap->size = size;
  buildMinHeap(minHeap);
  return minHeap;
}

struct HufmannTree* buildHuffmanTree(char data[], int freq[], int size) {
  struct HufmannTree *left, *right, *top;
  // Paso 1: Crear las hojas del arbol, sabiendo la cantidad.
  struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
 
  while (!isSizeOne(minHeap)) {
    // Paso 2: Extrae minimo 2 hojas del arbol
    left = extractMin(minHeap);
    right = extractMin(minHeap);

    // Paso 3: crea el nodo con la suma de las frecuencias y las asigna a cada lado.
    top = newNode('$', left->freq + right->freq);
    top->left = left;
    top->right = right;
    insertMinHeap(minHeap, top);
  }
 
  // Paso 4: El nodo restante es el nodo raíz y el árbol está completo.
  return extractMin(minHeap);
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

int tamLista(Lista lista) {
  pNodo nodo = lista;
  int size = 0;
  while(nodo) {
    size++;
    nodo = nodo->siguiente;
  }
  return size;
}

void swapMinHeapNode(struct HufmannTree** a, struct HufmannTree** b) {
    struct HufmannTree* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
      smallest = right;
 
    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap) { return (minHeap->size == 1); }

void insertMinHeap(struct MinHeap* minHeap, struct HufmannTree* minHeapNode) {
  //Inserta el nodo en el arbol
  ++minHeap->size;
  int i = minHeap->size - 1;
  while (i && minHeapNode->freq < minHeap->array[(i - 1)/2]->freq) {
    minHeap->array[i] = minHeap->array[(i - 1)/2];
    i = (i - 1)/2;
  }
  minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
  //construye el nodo hoja del arbol
  int n = minHeap->size - 1;
  int i;
  for (i = (n - 1) / 2; i >= 0; --i)
    minHeapify(minHeap, i);
}

void printArr(int arr[], int n) {
  int i;
  for (i = 0; i < n; ++i)
    printf("%d", arr[i]);
  printf("\n");
}

int isLeaf(struct HufmannTree* root) { return !(root->left) && !(root->right); }

/*Metodo que se encarga de crear un Table code */
TableCode* newTAbleCode(char letter, int code[],int n){ /*n tamano del vector*/  
  TableCode* TC;
  int TAM=n;
  TC->letra=letter;
  for (int i=0;i<TAM;i++){ 
    TC->codes[i]=code[i];
  }
  return TC;
}

void showTable(TableCode* c1, int n) {
  printf("Letra: %c ",c1->letra);
  for (int i=0;i<n;i++){
    printf("%d", c1->codes[i]);
  }
  printf("\n-------\n");
}
 
void printCodes(struct HufmannTree* root, int arr[], int top) {
  // Imprime el codigo de huffman
  // Asigna y retorna 0 en la hoja izquierda
  if (root->left) {
    arr[top] = 0;
 
    printCodes(root->left, arr, top + 1);
  }
 
  // Asigna y retorna 1 en la hoja izquierda
  if (root->right) {
    arr[top] = 1;
    printCodes(root->right, arr, top + 1);
  }

  // Si se trata de un nodo hoja, entonces contiene uno de los 
  // caracteres, imprime el carácter y su código de arr []
  if (isLeaf(root)) {
    TableCode* t1= newTAbleCode(root->data, arr, top);
    showTable(t1, top);
  }
}

// Funcion principal de Huffman
void HuffmanCodes(Lista lista, int size) {
  pNodo nodo = lista;
  int x = 0;
  int y = 0;
  char arrayValues[1000];
  int arrayFrequency[1000];
  
  while(nodo) {
    arrayFrequency[y] = nodo->letter.frequency;
    arrayValues[x] = nodo->letter.value;
    y++;
    x++;
    nodo = nodo->siguiente;
  }

  //  Construccion del Arbol de Huffman
  struct HufmannTree* root = buildHuffmanTree(arrayValues, arrayFrequency, size);
 
  // Imprime el codigo con el arbol
  int arr[MAX_TREE_HT], top = 0;
  printCodes(root, arr, top);
}

void createLetterArray(char array[]) {
  char flag = array[0];
  pNodo nodo = lista;
  int contador = 1;

  while(x < strlen(array)) {

    if(ListaVacia(lista)) {
      int cont = 0;
      for(int j = 0; j < strlen(array); j++) {
        if(array[j] == flag) {
        cont++;
        }
      }
      Insertar(&lista, flag, cont);
    } else {
      pNodo nodo = lista;
      int contador = 0;

      /* Valida si la letra ya se encuentra en la lista */
      while(nodo) {
        if(flag == nodo->letter.value) {
          contador++;
        }
        nodo = nodo->siguiente;
      }

      if(contador != 1) {
      int cont = 0;
      /* Saca la Frecuencia del Valor en el vector */
      for(int j = 0; j < strlen(array); j++) {
        if(array[j] == flag) {
        cont++;
        }
      }
      /* Inserta en la lista */
      Insertar(&lista, flag, cont);
      }
    }
    y++;
    flag = array[y];
    x++;
  }
}

void readFile() {
  FILE *readText = fopen("texto", "r");
  char phrase[100];

  if(!readText){
    printf("El archivo no existe..");
  }
  
  while (feof(readText) == 0) {
    fgets(phrase,100,readText);
    printf("Frase en el Archivo: %s",phrase);
  }

  fclose(readText);
  createLetterArray(phrase);
}

int main() {
  readFile();
  printf("\n-------\n");
  MostrarLista(lista);
  int size = tamLista(lista);
  printf("\n-------\n");
  HuffmanCodes(lista, size);

  return 0;
}
 