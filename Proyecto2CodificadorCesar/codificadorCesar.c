/*
 *      Proyecto 2 de Sistemas Operativos
 *      CodificadorCesar.c
 *      
 *      Cristian Díaz
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Varaibles Globales */

char* encryptedPhrase;
char* keyPhrase;

/* Metodos */

void readFile();
void readKey();
void compareArrays(char arrayPhrase[], char arrayKey[]);
/* Desarrollo de metodos */

void compareArrays(char arrayPhrase[], char arrayKey[]) {

  for (int i = 0; i < strlen(arrayPhrase); ++i) {
    for (int j = 0; j < strlen(arrayKey); ++j) {
      /* code */
    }
  }
}

void readKey() {
  keyPhrase = (char*)malloc(sizeof(char));

  printf("Introduzca la llave del cifrado: ");
  scanf("%s", &keyPhrase);
}

void readFile() {
  encryptedPhrase = (char*)malloc(sizeof(char));

  FILE *encrypted = fopen("texto", "rb");

  if(!encrypted) {
    printf("El archivo no se existe\n");
    return 1;
  }

  fscanf(encrypted, "%s" ,encryptedPhrase);

  fclose(encrypted);
}

int main(){
  
  readFile();

  readKey();

  printf("Texto del Archivo=> %s \n", encryptedPhrase);
  printf("Llave para Cifrado=> %s \n", &keyPhrase);

  printf("------------\n");
  compareArrays(encryptedPhrase, &keyPhrase);

  return 0;
}