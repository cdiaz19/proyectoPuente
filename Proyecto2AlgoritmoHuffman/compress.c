/*
 *      Proyecto 2 de Sistemas Operativos
 *      compress.c
 *      
 *      David Ugalde
 *      Cristian Díaz
 * 
 */

#include "compress.h"
int main(int argc,char *argv[]){
	int block,threads,size;
	comp = argv[1];
	FILE * read = fopen(comp,"rb");
	if(!read)	{
		printf("Unable to open file\n");
		return 1;	
	}
	fseek(read, 0L, SEEK_END);
	size = ftell(read);
	threads = atoi(argv[2]);
	block = (size/threads)+1;
	fclose(read);
	compi(block,threads);
	return 0;
}
