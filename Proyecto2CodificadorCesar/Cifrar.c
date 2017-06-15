#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 30

/* Variables globales */

pthread_t thread1,thread2,thread3,thread4;
static pthread_mutex_t candado;
static pthread_cond_t producido;
static pthread_cond_t consumido;

static char buffer[BUFSIZE];
static char* frase;
static char* Llave;
static int entrada=0;
static int salida=0;
static int contador=0;
static int posFrase=0;
static int posLlave=0;

/* Declaracion de Metodos */

void init();
void getElement();
void putElement();
void produce();
void consume();

/* Implementacion de Metodos */

void init(){
  pthread_mutex_init(&candado,NULL);
  pthread_cond_init(&producido,NULL);
  pthread_cond_init(&consumido,NULL);
}

void getElement(){
  pthread_mutex_lock(&candado); 
  
  while(contador==0) {//buffer vacio
    pthread_cond_wait(&producido,&candado); //esperando
  }

  contador = contador-1;
  
  printf("\n");
  printf("sacando del buffer: %c", buffer[salida]);
  printf("\n");
  
  salida=(salida+1)%BUFSIZE;
  pthread_cond_signal(&consumido); //señaliza la extraccion de datos
  pthread_mutex_unlock(&candado);
  return;
}

void putElement(){
  pthread_mutex_lock(&candado); 
  
  while(contador==BUFSIZE) {//buffer lleno
	  pthread_cond_wait(&consumido,& candado);//esperando
  }
 
  contador=contador+1;
  buffer[entrada] = frase[posFrase] - Llave[posLlave]==0?frase[posFrase]:frase[posFrase]-Llave[posLlave];

  printf("\n");
  printf("metiendo al buffer: %c ", buffer[entrada]);
  printf("\n");

  posLlave=(posLlave+1)%strlen(Llave);
  posFrase=posFrase+1; // aqui lo hace pero iterando hasta finalizar el arreglo no todo el archivo

  entrada=(entrada+1)%BUFSIZE;
  pthread_cond_signal(&producido);//señaliza que metio datos
  pthread_mutex_unlock(&candado);
  return;
}

void produce() {
  while(posFrase<strlen(frase)-1) {
    putElement();
  }
}

void consume() {
  while(contador!=0 && strlen(buffer)!=0 && posFrase!=strlen(frase)){
    getElement();
  }
}

int main(int argc,char *argv[]) {
  frase="solo se que no se nada";
  Llave=" ";

  init();

  pthread_create (&thread1,NULL,produce,NULL);
  pthread_create (&thread2,NULL,produce,NULL);
  pthread_create (&thread3,NULL,consume,NULL);
  pthread_create (&thread4,NULL,consume,NULL);


  pthread_join(thread1,NULL);
  pthread_join(thread2,NULL);
  pthread_join(thread3,NULL);
  pthread_join(thread4,NULL);

  pthread_exit (NULL);
}
