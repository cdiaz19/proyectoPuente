/*
 *      Proyecto 1 de Sistemas Operativos
 *      ArbolCompresorProyecto1.h
 *      
 *      Cristian Díaz
 *      Alonso Aguilar
 * 
 */



#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
   char letra;             //Letra
   unsigned long int bits; //Codigo
   char nbits;             /* Número de bits de la codificación */
   nodo *cero;            /* Rama cero de un árbol */
   nodo *uno;             /* Puntero a la rama uno de un árbol */
} tipoNodo;                

int main(int argc, char *argv[]){

   tipoNodo *Arbol;        /* Arbol de codificación */
   long int Longitud;      /* tamano del fichero */
   int nElementos;         /* Cantidad de elementos de árbol */
   unsigned long int bits; /* Almacenamiento de bits para decodificación */
   FILE *fe, *fs;          /* entrada y salida*/

   tipoNodo *p, *q;        /* variables auxiliares */
   unsigned char a;
   int i, j;


 /* Crear un arbol con la información de la tabla */
   Arbol = (tipoNodo *)malloc(sizeof(tipoNodo)); /* un nodo nuevo */
   Arbol->letra = 0;
   Arbol->uno = Arbol->cero = NULL;
   fe = fopen(argv[1], "rb");
   fread(&Longitud, sizeof(long int), 1, fe); /* Lee el número de caracteres */
   fread(&nElementos, sizeof(int), 1, fe); /* Lee el número de elementos */

for(i = 0; i < nElementos; i++) /* Lee los elementos */
   {
      p = (tipoNodo *)malloc(sizeof(tipoNodo)); //crea nuevo nodo
      fread(&p->letra, sizeof(char), 1, fe); //lee el caracter
      fread(&p->bits, sizeof(unsigned long int), 1, fe); //lee el codigo
      fread(&p->nbits, sizeof(char), 1, fe); //lee la longitud
      p->cero = p->uno = NULL;
      //ingresa el nodo en su lugar
      j = 1 << (p->nbits-1);
      q = Arbol;

while(j > 1)
      {
         if(p->bits & j) /* es un uno*/
            if(q->uno) q = q->uno;  //si el nodo esta nos movemos hacia el 
            else                     //si no existe se crea
            {
               q->uno = (tipoNodo *)malloc(sizeof(tipoNodo)); //se crea el nodo si no existe;
               q = q->uno;
               q->letra = 0;
               q->uno = q->cero = NULL;
            }
         else /* es un cero */
            if(q->cero) q = q->cero; /* Si el nodo existe, nos movemos a él */
            else                     /* Si no existe, lo creamos */
            {
               q->cero = (tipoNodo *)malloc(sizeof(tipoNodo)); /* un nodo nuevo */
               q = q->cero;
               q->letra = 0;
               q->uno = q->cero = NULL;
            }
         j >>= 1;  /* Siguiente bit */
      }
      /* Ultimo Bit */
      if(p->bits & 1) /* es un uno*/
         q->uno = p;
      else            /* es un cero */
         q->cero = p;
   }
   /* Leer datos comprimidos y extraer al fichero de salida */
   bits = 0;
   fs = fopen(argv[2], "w");
   /* Lee los primeros cuatro bytes en la dobel palabra bits */
   fread(&a, sizeof(char), 1, fe);
   bits |= a;
   bits <<= 8;
   fread(&a, sizeof(char), 1, fe);
   bits |= a;
   bits <<= 8;
   fread(&a, sizeof(char), 1, fe);
   bits |= a;
   bits <<= 8;
   fread(&a, sizeof(char), 1, fe);
   bits |= a;
   j = 0; /* Cada 8 bits leemos otro byte */
   q = Arbol;
   /* Bucle */
   do {
      if(bits & 0x80000000) q = q->uno; else q = q->cero; /* Rama adecuada */
      bits <<= 1;           /* Siguiente bit */
      j++;
      if(8 == j)            /* Cada 8 bits */
      {
         i = fread(&a, sizeof(char), 1, fe); /* Leemos un byte desde el fichero */
         bits |= a;                    /* Y lo insertamos en bits */
         j = 0;                        /* No quedan huecos */
      }                                
      if(!q->uno && !q->cero)          /* Si el nodo es una letra */
      {
         putc(q->letra, fs);           /* La escribimos en el fich de salida */
         Longitud--;                   /* Actualizamos longitud que queda */
         q=Arbol;                      /* Volvemos a la raiz del árbol */
      }
   } while(Longitud);                  /* Hasta que acabe el fichero *//*de aqui para bajo se puede borrar*/
   /* Procesar la cola */

   fclose(fs);                         /* Cerramos ficheros */
   fclose(fe);

   BorrarArbol(Arbol);                 /* Borramos el árbol */
   return 0;


}

