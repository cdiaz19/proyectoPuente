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

//Base para de decodificar
#define MAX_CARACTERES 255

// Decodificar
struct decode{
    int frecuencia;
    char letra;
    char codigo[10];
} nodo[MAX_CARACTERES];

// 
int nro_elementos=0;                            // Cantidad de elementos que contiene el Archivo.txt.huff.
int elementos_diccionario[MAX_CARACTERES];      // Almacena la info del Archivo.txt.huff.

// Metodos para decodificar
int longitud_codificado(char codificadotxt[20])
{
    int cont=0;
    char caracter;
    FILE * ;//archivo con el codigo

    codificado = fopen(codificadotxt, "r");
    if(!codificado)
    {
        printf("Archivo invalido...\n");        //Devuelve la longitud del archivo codificado.
    return;
    }

    if(codificado!=NULL)
    {
        while(feof(codificado)==0)
        {
            caracter=fgetc(codificado);
            cont++;
        }
    }
    fclose(codificado);
    return cont;
}

int verifica_igualdad(char cadena1[], char cadena2[], int longitud)
{
    int i=0, bandera=0;

    for(i=0; i<longitud; i++)
    {
        if(cadena1[i]==cadena2[i])
        {
            bandera=1;                          // Verifica si el codigo leido es igual al codigo de la letra evaluada.
        }
        else
        {
            bandera=0;
            return bandera;
        }
    }
    return bandera;
}

void vaciar_arreglo(char *comparar, int tamano)
{
    int i=0;

    // Vacia el arreglo para leer una letra nueva.
    for(i=0;i<=tamano;i++)
        comparar[i]='\0';
}

void guarda_diccionario(char diccionariotxt[20])
{
    int i=0;
    FILE * diccionario;

    diccionario = fopen(diccionariotxt, "r");       //Abrimos el diccionario para asignar cada campo a la estructura.
    if(!diccionario)
    {
        printf("Archivo invalido...\n");
        return;
    }
    if(diccionario != NULL)
    {
        while(!feof(diccionario)){          //Empieza a guardar cada campo.
            fscanf(diccionario, "%c (%d): %s", &nodo[nro_elementos].letra,&nodo[nro_elementos].frecuencia,&nodo[nro_elementos].codigo);
            nro_elementos++;
        }
        fclose(diccionario);
    }
}

void decodifica(char codificadotxt[20])
{
    int cont1=0, cont2=0, longitud=0;
    char caracter;
    FILE *codificado;

    codificado = fopen(codificadotxt, "r");     //Abrimos el archivo codificado para empezar a decodificar.
    if(!codificado)
    {
        printf("Archivo invalido...\n");
        return;
    }
    longitud=longitud_codificado(codificadotxt);
    char comparar[10];
    if(codificado != NULL)
    {
        while(feof(codificado) == 0)
        {
            caracter=fgetc(codificado);
            comparar[cont1]=caracter;
            for(cont2=0;cont2<nro_elementos;cont2++)
            {
                if(strncmp(comparar,nodo[cont2].codigo, 10) == 0)
                {
                    printf("%c", nodo[cont2].letra);
                    vaciar_arreglo(comparar, cont1);
                    cont1=-1;
                    goto salir;
                }
            }
            salir:
            cont1++;
        }
        fclose(codificado);
    }
    printf("\n");
}

void imprime_dicc()
{
    int i=0;
    for(i=0;i<nro_elementos;i++)
        printf("Caracter: %c Frecuencia:(%d): Codigo:%s\n", nodo[i].letra,nodo[i].frecuencia,nodo[i].codigo);
}


void main()
{
    char diccionariotxt[20], codificadotxt[20];
    printf("         |HUFFMAN|      \n");
    printf("Ingrese el nombre del archivo diccionario: ");
    scanf("%s", &diccionariotxt);
    printf("Ingrese el nombre del archivo codificado: ");
    scanf("%s", &codificadotxt);
    guarda_diccionario(diccionariotxt);
    decodifica(codificadotxt);
}