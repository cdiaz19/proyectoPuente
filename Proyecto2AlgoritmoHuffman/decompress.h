/*
 *      Proyecto 2 de Sistemas Operativos
 *      decompress.h
 *      
 *      David Ugalde
 *      Cristian Díaz
 * 
 */

#include "tree.h"
#include <string.h>

static Tree * tree;
static char value;
static int count,size,current,end;
static FILE * read;
static FILE * create;
static Node * aux;
static struct stat st;
static char * file;
char * substract(char *s) {
    int len = strlen(s);
    char buf[len-1];
    int i;
	for(i = 0; i < len-4; i++){
		buf[i] = s[i];
	}
	buf[i] = 0;
    return strdup(buf);
}

void search(){
	if(aux->left == NULL && aux->right == NULL){
		current = ftell(read);
		fwrite (&aux->data.value, sizeof(char), 1, create);
		fflush(create);
		if(!(aux->data.value == 10 && current == size)){
			aux = tree->first;
			end = 1;
		}
		else
			count = -1;
	}
	if(end == 0){
		if(count < 0){
			if(fscanf(read, "%c", &value) == 1){
				count = 7;
				search();
			}
		}
		else{
			if(value>>count&1){
				aux = aux->right;
				count--;
			}
			else{
				aux = aux->left;
				count--;
			}
			search();
		}
	}
}

void decompress(){
	while(current != size){
		end = 0;
		search();
	}
}

void dec(){
	HuffmanCode code;
	tree = (Tree*)malloc(sizeof(Tree));
	tree->first = (Node*)malloc(sizeof(Node));
	read = fopen(file,"rb");
	if (!read){
		printf("Unable to open file!\n");
	}
	else{
		stat(file, &st);
		size = st.st_size;
		file = substract(file);
		create = fopen(file,"wb");
		if (!read){
			printf("Unable to open file!\n");
		}
		else{
			while (1){
				fread(&code,sizeof(HuffmanCode),1,read);
				if(code.bits == 0)
					break;
				makeTree(tree,code);
			}
			count = -1;
			aux = tree->first;
			decompress();
			fclose(create);
		}
	}
	fclose(read);
}
