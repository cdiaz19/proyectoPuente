/*
 *      Proyecto 1 de Sistemas Operativos
 *      DescompresorProyecto1.c
 *      
 *      Cristian Díaz
 *      Alonso Aguilar
 * 
 */

#include <stdlib.h>
#include <stdio.h>

/* Estructuras */

/* Variables Globales */

int hufmman[1000000];
/* Metodos */

void readFile();

/* Desarrollo */

void readFile() {
  FILE *fileCompress = fopen("Archivo.txt.edy", "rb");

  if(!fileCompress){ printf("No existe el archivo\n"); }
  while (feof(fileCompress) == 0) {
    fgets(hufmman, 1000000, fileCompress);
  }

  fclose(fileCompress);
}

int main() {
  readFile();
  return 0;
}
