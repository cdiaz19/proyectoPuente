/*
 *      proyecto0.c
 *      
 *      Cristian Díaz Jiménez
 * 
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define BRIDGE_DIRECTION_EAST 0x01
#define BRIDGE_DIRECTION_WEST 0x02

int longbridge;
int arrivetime;
int traveltime;
int semaphore;
int carsOE;
int carsEO;

/* Estructuras */
typedef struct StructBridge {
    int cars;
    int direction;
    int oficial;
    pthread_mutex_t mutex;
    pthread_cond_t empty;
} QStructBridge;

int random(){
  return (rand() % 2);
}

static int runThread(int carsOE, int carsEO) {
  srand(time(NULL));
  int i = 0, n = carsEO + carsOE;
  pthread_t thread[n];
  int random = random(); 
  int cOE = carsOE;
  int cEO = carsEO;

  while (i < n) { 
    if(r == 2 && o > 0) {
      if (pthread_create(&thread[i], NULL,
                westo, &shared_bridgeo)) {
        fprintf(stderr, "thread creation failed\n");
        return EXIT_FAILURE;
      }
        cEO--;
        i++;
      }
      if(r == 1 && e > 0) {            
        if (pthread_create(&thread[i], NULL,
                easto, &shared_bridgeo)) {
          fprintf(stderr, "thread creation failed\n");
          return EXIT_FAILURE;
        }            
        cOE--;
        i++;
      }            
      r = rand() % 2 + 1;  
    }

    for (i = 0; i < n; i++) {
      if (thread[i]) pthread_join(thread[i], NULL);
    }
    return EXIT_SUCCESS;
}

void loadArchivo() {
  FILE *ptr_file;
  char buf;
  int variables[6];
  int i = 0;
  int decimal = 10;
  int numeroanterior;

  ptr_file = fopen("parametros", "r");
  if (!ptr_file) {
    printf("No se encontro el archivo");
    return;
  }

  while (feof(ptr_file) == 0) {
    buf = fgetc(ptr_file);
    if (buf == ' ') {
      numeroanterior = 0;
      decimal = 10;
      i++;
      
    } else {
      if (isdigit(buf)) {
        numeroanterior = buf;
        variables[i] = numeroanterior;
      }
    }
  }

  fclose(ptr_file);
  longbridge = variables[0];
  arrivetime = variables[1];
  traveltime = variables[2];
  semaphore = variables[3];
  carsOE = variables[4];
  carsEO = variables[5];
}

int main(void) {

  loadArchivo();
  int c, nw = carsOE, ne = carsEO;

  return runThread(nw, ne);
}
