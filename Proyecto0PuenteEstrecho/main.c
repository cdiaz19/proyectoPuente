#include"basics.h"
void cargar(){
	FILE * fp;
	char * line = NULL;
	char *ptr;
	size_t len = 0;
	int read;
	int i = 0;
	var = malloc(14*sizeof(int));
	fp = fopen("output.txt", "r");
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
	cargar();
	time_t t;
	srand((unsigned) time(&t));
	pthread_t we, ew, mon, semaphore,officer;
	bridge = createBridge(var[1]);
	wes = createRoadSide();
	ews = createRoadSide();
	pthread_mutex_init(&wait, NULL);
	int * side_we = 1;
	int * side_ew = 0;
	pthread_create(&mon, NULL, (void *)monitor, NULL);
	if(var[0] == 2){
		pthread_create(&semaphore, NULL, (void *)semaphoreManager, NULL);
		//pthread_join(semaphore, NULL);
	}
	if(var[0] == 3){
		contWE = 0;
		contEW = 0;
		pthread_create(&officer, NULL, (void *)officerManager, NULL);
		//pthread_join(officer, NULL);
	}
	pthread_create(&we, NULL, (void *)start, side_we);
	pthread_create(&ew, NULL, (void *)start, side_ew);
	pthread_join(mon, NULL);
	pthread_join(we, NULL);
	pthread_join(ew, NULL);
}











