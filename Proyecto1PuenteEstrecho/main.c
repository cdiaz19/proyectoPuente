/*
 *      Proyecto 1 de Sistemas Operativos
 *      main.c
 *      
 *      David Ugalde
 *      Cristian Díaz
 * 
 */

#include "principal.h"

/* Declaracion de Metodos */
void loadFile();

/* Desarrollo de Metodos */
void loadFile() {
	char * line = NULL;
	char *ptr;
	size_t len = 0;
	int read;
	int i = 0;
	var = malloc(16*sizeof(int));
	FILE * fp = fopen("output.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	while ((read = getline(&line, &len, fp)) != -1) {
		var[i] = strtol(line, &ptr, 10);
		i++;
	}
	fclose(fp);
	if (line)
		free(line);
}


int main(int argc, const char* argv[]){
	loadFile();
	time_t t;
	srand((unsigned) time(&t));

	pthread_t we, ew, pan, semaphore,officer;
	bridge = createBridge(var[1]);
	wes = createRoadSide();
	ews = createRoadSide();
	pthread_mutex_init(&wait, NULL);
	int * side_we = 1;
	int * side_ew = 0;
	pthread_create(&pan, NULL, (void *)panel, NULL);
	
  if(var[0] == 2){
		pthread_create(&semaphore, NULL, (void *) semaphoreManager, NULL);
	}
	
  if(var[0] == 3){
		contWE = 0;
		contEW = 0;
		pthread_create(&officer, NULL, (void *) officerManager, NULL);
	}

	pthread_create(&we, NULL, (void *) startCreateCars, side_we);
	pthread_create(&ew, NULL, (void *) startCreateCars, side_ew);

	pthread_join(pan, NULL);
	pthread_join(we, NULL);
	pthread_join(ew, NULL);

  return 0;
}
