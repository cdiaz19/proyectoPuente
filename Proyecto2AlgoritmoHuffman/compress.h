/*
 *      Proyecto 2 de Sistemas Operativos
 *      compress.h
 *      
 *      David Ugalde
 *      Cristian Díaz
 * 
 */

#include "quicksort.h"
#include <string.h>
#include <time.h>
static char * comp;
static int **vector;
static char * charValues;
static int size;

typedef struct threadData {
	int start;
	int end;
	int i;
}threadData;

char * append(char *s) {
    int len = strlen(s);
    char buf[len+5];
    strcpy(buf, s);
    buf[len] = '.';
    buf[len+1] = 'e';
    buf[len+2] = 'd';
    buf[len+3] = 'y';
    buf[len+4] = 0;
    return strdup(buf);
}

void compress(int size){
	FILE * read,*create;
	read = fopen(comp,"rb");	
	comp = append(comp);
	create = fopen (comp, "wb");
	char * value = (char*) malloc(sizeof(char)),* save = (char*) malloc(sizeof(char)),a,b;
	int count,i;
	HuffmanCode code;
	value = 44;
	for(i=0;i < size;i++){
		fwrite (&codes[0][i], sizeof(HuffmanCode), 1, create);
	}
	code.bits = 0;
	fwrite (&code, sizeof(HuffmanCode), 1, create);
	count = 0;
	while ( fscanf(read, "%c", &value) == 1){
		a = (char)value;
		//buscar en el vector de codigos el codigo al que pertenece
		for(i = 0; i < size; i++){
			b = (char)codes[0][i].value;
			if(a == b){
				code = codes[0][i];
				break;
			}
		}
		//comprimir el byte en el codigo
		for(i = code.bits-1; i >= 0; i--){
			if(((code.code>>i)&1)==0){
				count++;
			}else{
				save++;
				count++;
			}
			if(count == 8){
				fwrite (&save, sizeof(char), 1, create);
				save = 0;
				count=0;	
			}
			else
				save = ((int)save) <<1;
		}
	}
	if(count != 0){
		save = ((int)save) <<(7-count);
		fwrite (&save, sizeof(char), 1, create);
	}
	fclose(create);
}

void freq(threadData * data)
{	int i,pos;
	char value;
	FILE * read = fopen(comp,"rb");
	fseek(read,data->start,SEEK_SET);
	for(i=data->start;i<data->end;i++){
		if(fscanf(read, "%c", &value)==1){
			pos = (int)value;
			if(pos < 0)
				pos = 127+abs(pos);
			if(vector[data->i][pos] == 0){
				charValues[pos] = value;
			}
			vector[data->i][pos]++;
	 	}
		else
			break;
	}
	free(data);
	fclose(read);
	pthread_exit();
}
void compi(int block,int numberT){
	clock_t t1,t2,t3,t4;
	int i,j;
	pthread_t threads[numberT]; 
	Data * vec;
	threadData * data;
	Tree * tree;
	size = 0;
	pthread_mutex_init(&mutex, NULL);
	charValues = (char *)malloc(256*sizeof(char));
	memset(charValues, 0, 256);
	vector = (int **)malloc(numberT*sizeof(int*));
	for(i = 0; i < numberT; i++){
		vector[i] = (int *)malloc(256*sizeof(int));
		memset(vector[i], 0, 256);
	}
	t1 = clock();
	for(i=0;i<numberT;i++) {
		data = (threadData*)malloc(sizeof(threadData));
		data->start = i*block;
		data->end = i+1;
		data->end = data->end * block;
		data->i = i;
		pthread_create(&threads[i],NULL,freq,data);			
	}
	for(i=0;i<numberT;i++) {
		pthread_join(threads[i],NULL);			
	}
	for(i = 1; i < numberT; i++){
		for(j = 0; j < 256; j++){
			vector[0][j] = vector[0][j] + vector[i][j];
		}
	}
	for(i = 0; i < 256; i++){
		if(vector[0][i] != 0)
				size++;
	}
	t1 = clock()-t1;
	vec = (Data*) malloc(size*sizeof(Data));
	j = 0;
	for(i = 0; i < 256; i++){
		if(vector[0][i] != 0){
			vec[j].value = charValues[i];
			vec[j].frequency = vector[0][i];
			j++;
		}
	}
	quickSort(vec,0,size-1);
	printf("Hojas del arbol: %d\n",size);
	printf("Tabla de frecuencias\n",size);
	for(i = 0; i < size; i++){
		printf("%d)Caracter: %c, frecuencia: %d\n",i+1,vec[i].value,vec[i].frequency);
	}
	t2 = clock();
	tree = createTree(vec,size);
	t2 = clock()-t2;
	t3 = clock();
	HuffmanCodes(tree,size);
	t3 = clock()-t3;
	t4 = clock();
	compress(size);
	t4 = clock()-t4;
	free(vec);
	free(charValues);
	free(comp);
	printf("codigos: %d\n",codesCount[0]);
	for(i = 0; i < 4; i++){
		free(codes[i]);
	}
	free(codes);
	for(i = 0; i < numberT; i++){
		free(vector[i]);
	}
	free(vector);
	free(codesCount);
	printf("Tiempo que tomo la fase 1: %f segundos\n",((double)t1)/CLOCKS_PER_SEC);
	printf("Tiempo que tomo la fase 2: %f segundos\n",((double)t2)/CLOCKS_PER_SEC);
	printf("Tiempo que tomo la fase 3: %f segundos\n",((double)t3)/CLOCKS_PER_SEC);
	printf("Tiempo que tomo la fase 4: %f segundos\n",((double)t4)/CLOCKS_PER_SEC);
}

