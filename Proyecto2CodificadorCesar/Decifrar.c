#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#define BUFFERSIZE 3 // tamano del buffer 

/* Variables globales */
pthread_mutex_t candado; //mutex de acceso compartido al buffer
pthread_cond_t producido; // condicion de llenado del buffer
pthread_cond_t consumido; // condicion de vaciado del buffer
char buffer[BUFFERSIZE]; //buffer comun
int contador; //numero de elementos en el buffer
int entrada;
int salida;
int posFrase;
int posLlave;
int producidos;
int consumidos;
FILE *file;
FILE *cesar;
char *llave;

/* Declaracion de Metodos */

void get_Element(void);
void put_Element(void);
void Init();
int ReadChar(FILE *file);
void WriteChar(FILE *Cesar, char dato);
int getTamFile(FILE *file);

/* Implementacion de Metodos */

void WriteChar(FILE *Cesar, char dato) {
  fprintf(Cesar, "%c", dato);
}

int ReadChar(FILE *file) {
  return fgetc(file);
}

int getTamFile(FILE *file) {
  fseek(file, 0, SEEK_END);
  int aux = ((ftell(file)) - 1);
  fseek(file, 0, SEEK_SET);
  return aux;
}

void Init() {
  printf("inicializando variables \n");
  entrada = 0;
  salida = 0;
  contador = 0;
  posLlave = 0;
  consumidos = getTamFile(file);
  producidos = getTamFile(file);

  pthread_mutex_init(&candado, NULL);
  pthread_cond_init(&producido, NULL);
  pthread_cond_init(&consumido, NULL);
}

void createCesarFile(char dato) {
  FILE *fp = fopen("Archivo.txt.cesar", "a");
  fprintf(fp, "%c ", dato);
  fclose(fp);
}

void get_Element(void) {
  while (consumidos != 0) {
    pthread_mutex_lock(&candado);
    while (contador == 0) {//buf vacio
      pthread_cond_wait(&producido, &candado); //esperando
    }
    if (consumidos > 0) {
      char dato = buffer[salida];
      salida = (salida + 1) % BUFFERSIZE;
      contador = contador - 1;
      consumidos = consumidos > 0 ? (consumidos - 1) : 0;

      WriteChar(cesar, dato);
      //pthread_cond_broadcast(&producido);
      //fflush(stdout);
      //   printf("%c",dato);
    }
    pthread_mutex_unlock(&candado);
    pthread_cond_signal(&consumido); //señaliza la extraccion de datos
  }

}

void put_Element(void) {
  while (!feof(file)) {
    pthread_mutex_lock(&candado);
    while (contador == BUFFERSIZE) {//buffer lleno
      pthread_cond_wait(&consumido, &candado); //esperando 
    }
    if (!feof(file)) {
      int val = ReadChar(file);
      char dato = val - llave[posLlave] == 0 ? val : val - llave[posLlave];

      buffer[entrada] = dato;
      posLlave = (posLlave + 1) % strlen(llave);
      producidos = producidos - 1;
      entrada = (entrada + 1) % BUFFERSIZE;
      contador = contador + 1;
    }
    //pthread_cond_broadcast(&producido);
    pthread_mutex_unlock(&candado);
    pthread_cond_signal(&producido); //señaliza que metio datos
  }
}

int main(int argc, char **argv) {

  file = fopen("txt", "rb");
  if (!file) {
    printf("El archivo no existe..");
  }
  else {
    cesar = fopen("Archivo.txt.cesar", "w");
    Init();
    printf("Inicio del programa \n");

    printf("Digite la llave para el cifrado del archivo: ");
    llave = (char*) malloc(sizeof (char*));
    scanf("%[^\n]", llave);
    fflush(stdin);
    fflush(stdout);

    int numHilos;
    printf("Digite el numero de hilos: ");
    scanf("%i", &numHilos);
    fflush(stdin);
    fflush(stdout);
    pthread_t thread[numHilos];

    printf("Codificando Archivo");

    for (int i = 1; i <= numHilos; i++) {
      if (i % 2 == 0) {
        pthread_create(&thread[i], NULL, (void *) &get_Element, NULL);
      } else {
        pthread_create(&thread[i], NULL, (void *) &put_Element, NULL);
      }
    }

    for (int i = 1; i <= numHilos; i++) {
      pthread_join(thread[i], NULL);
    }

    pthread_mutex_destroy(&candado);
    pthread_cond_destroy(&producido);
    pthread_cond_destroy(&consumido);

    free(llave);
    fclose(file);
    fclose(cesar);
  }
  printf("\n<=Archivo Codificado=>");
  return 0;
}
