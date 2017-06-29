/*
 *      Proyecto 2 de Sistemas Operativos
 *      main.c
 *      
 *      David Ugalde
 *      Cristian Díaz
 * 
 */

#include <stdio.h> 
#include <stdlib.h>
int main(int argc,char *argv[])
{
	char value;
	int i;
	FILE * read = fopen(argv[1],"rb");
	while ( fscanf(read, "%c", &value) == 1){
		for(i = 7; i >= 0; i --){
			printf("%d",value>>i&1);
		}
		printf("\n");
	}
	return 0;
}
