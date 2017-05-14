/*
 *      Proyecto 1 de Sistemas Operativos
 *      CompresorProyecto1.c
 *      
 *      Cristian Díaz
 *      Alonso Aguilar
 * 
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Estructuras */
typedef struct StructLetter {
  char value;
  int frequency;
} StructLetter;

StructLetter arreglo2[100];
int a = 0;
int x = 0;
int y = 0;

/* Metodos */

/* Crea un vector con objetos Letter (value, frequency) */
void createLetterArray(char array[]) {
  char flag = array[0];

  while(x < strlen(array)) {
    int contador = 0;

    for (int i = 0; i < strlen(arreglo2); i++) {
      if(flag == arreglo2[i].value) {
        contador++;
      }
    }

    if(contador != 1) {
      int cont = 0;
      for(int j = 0; j < strlen(array); j++) {
        if(array[j] == flag) {
        cont++;
        }
      }
      StructLetter QEst;
      QEst.value = flag;
      QEst.frequency = cont;
      arreglo2[a] = QEst;
      a++;
    }
    y++;
    flag = array[y];
    x++;
  }
}

/* Elimina los espacios en blanco de la frase */
void copyArrays(char array[]) {
  char letters[100];

  int i,j;

  for (i=j=0; array[i] != '\0'; i++) {
    if (!isspace(array[i]))
      letters[j++] = array[i];
  }
  letters[j] = '\0';
  printf("\n");
  createLetterArray(letters);
}

/* Lee la frase del archivo */
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
  copyArrays(phrase);
}

int main () {
  readFile();
  printf("----\n"); 
  FILE *create = fopen ("tablaHuffman", "wb");
  for(int i = 0; i < strlen(arreglo2); i++) {
    fprintf(create,"Letra: %c - Frecuencia: %i. \n",arreglo2[i].value, arreglo2[i].frequency);
  }

  /* Falta crear archivo */

  fclose(create);
  return 0;
}
