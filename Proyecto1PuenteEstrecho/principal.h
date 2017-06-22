#include "bridge.h"
#include "roadSide.h"
static Bridge bridge;
static RoadSide wes,ews;
static pthread_mutex_t wait;
static int * var;
static int semaphoreWE,semaphoreEW;
static int contWE,contEW;

/* Metodos para cruzar el puente */

int fifo(Car * car){
	pthread_mutex_lock(&wait);
	pthread_mutex_lock(&bridge.carQueue->wait);
	if(bridge.carQueue->size == 0){
		if(car->side){
			bridge.we = 1;
			bridge.ew = 0;
			
			return 0;
		}
		else{
			bridge.ew = 1;
			bridge.we = 0;
			return 0;
		}
	}
	else{
		if(car->side){
			if(bridge.ew || (bridge.carQueue->size >= bridge.size) || get(bridge.carQueue,bridge.carQueue->size-1)->distance < 1.5){
				pthread_mutex_unlock(&bridge.carQueue->wait);
				pthread_mutex_unlock(&wait);
				return 1;
			}
			else return 0;
		}
		else{
			if(bridge.we || (bridge.carQueue->size >= bridge.size) || get(bridge.carQueue,bridge.carQueue->size-1)->distance < 1.5){
				pthread_mutex_unlock(&bridge.carQueue->wait);
				pthread_mutex_unlock(&wait);
				return 1;
			}
			else return 0;
		}
	}
}

void officerManager(){
	while(1){
		contWE = 0;
		bridge.we = 1;
		bridge.ew = 0;
		do {
		} while(contWE < var[12] && wes.createdCars > 0);
		contEW = 0;
		bridge.we = 0;
		bridge.ew = 1;
		do {
		} while(contEW < var[13] && ews.createdCars > 0);
	}
}

int officer(Car * car){
	pthread_mutex_lock(&wait);
	pthread_mutex_lock(&bridge.carQueue->wait);
	Car * aux;
	if(car->side){
		if(bridge.carQueue->size == 0 && bridge.we){
			usleep(500000);
			return 0;
		}
		if(bridge.ew || (bridge.carQueue->size >= bridge.size)){
			pthread_mutex_unlock(&bridge.carQueue->wait);
			pthread_mutex_unlock(&wait);
			return 1;
		}
		else{
			aux = get(bridge.carQueue,bridge.carQueue->size-1);
			if(aux->distance < 1.5 || aux->side != car->side){
				pthread_mutex_unlock(&bridge.carQueue->wait);
				pthread_mutex_unlock(&wait);
				return 1;
			}
			else return 0;
		}
	}
	else{
		if(bridge.carQueue->size == 0 && bridge.ew){
			usleep(500000);
			return 0;
		}
		if(bridge.we || (bridge.carQueue->size >= bridge.size)){
			pthread_mutex_unlock(&bridge.carQueue->wait);
			pthread_mutex_unlock(&wait);
			return 1;
		}
		else{
			aux = get(bridge.carQueue,bridge.carQueue->size-1);
			if(aux->distance < 1.5 || aux->side != car->side){
				pthread_mutex_unlock(&bridge.carQueue->wait);
				pthread_mutex_unlock(&wait);
				return 1;
			}
			else return 0;
		}
	}
}


void semaphoreManager(){
	time_t start, end;
	double elapsed;
	while(1){
		time(&start);
		bridge.we = 1;
		bridge.ew = 0;
		do {
			time(&end);
			elapsed = difftime(end, start);
		} while(elapsed <= var[10]);
		time(&start);
		
		bridge.we = 0;
		bridge.ew = 1;
		do {
			time(&end);
			elapsed = difftime(end, start);
		} while(elapsed <= var[11]);
	}
}

int semaphore(Car * car){
	pthread_mutex_lock(&wait);
	pthread_mutex_lock(&bridge.carQueue->wait);
	Car * aux;
	if(car->side){
		if(bridge.carQueue->size == 0 && bridge.we){
			usleep(500000);
			return 0;
		}
		if(bridge.ew || (bridge.carQueue->size >= bridge.size)){
			pthread_mutex_unlock(&bridge.carQueue->wait);
			pthread_mutex_unlock(&wait);
			return 1;
		}
		else{
			aux = get(bridge.carQueue,bridge.carQueue->size-1);
			if(aux->distance < 1.5 || aux->side != car->side){
				pthread_mutex_unlock(&bridge.carQueue->wait);
				pthread_mutex_unlock(&wait);
				return 1;
			}
			else return 0;
		}
	}
	else{
		if(bridge.carQueue->size == 0 && bridge.ew){
			usleep(500000);
			return 0;
		}
		if(bridge.we || (bridge.carQueue->size >= bridge.size)){
			pthread_mutex_unlock(&bridge.carQueue->wait);
			pthread_mutex_unlock(&wait);
			return 1;
		}
		else{
			aux = get(bridge.carQueue,bridge.carQueue->size-1);
			if(aux->distance < 1.5 || aux->side != car->side){
				pthread_mutex_unlock(&bridge.carQueue->wait);
				pthread_mutex_unlock(&wait);
				return 1;
			}
			else return 0;
		}
	}
}

int selecMethod(Car * car){
	if(var[0] == 1)
		return fifo(car);
	if(var[0] == 2)
		return semaphore(car);
	if(var[0] == 3)
		return officer(car);
}

void drive(Car * car){
	Car * ahead;
	while(selecMethod(car));
	enqueue(bridge.carQueue,car);
	if(car->side){
		wes.next++;
		wes.createdCars--;
		contWE++;
	}
	else{
		ews.next++;
		ews.createdCars--;
		contEW++;
	}
	if(car->pos > 0)
		ahead = get(bridge.carQueue, car->pos-1);
	pthread_mutex_unlock(&bridge.carQueue->wait);
	pthread_mutex_unlock(&wait);
	while(car->distance < bridge.size){
		pthread_mutex_lock(&bridge.carQueue->wait);
		if(car->pos > 0){
			if(((int)(ahead->distance)-1.5) <= ((int)(car->distance))){
				if(car->varSpeed > ahead->varSpeed)
					car->varSpeed = ahead->varSpeed;
			}
			else{
				car->varSpeed = car->speed;
			}	
		}
		else{
			car->varSpeed = car->speed;
		}
		pthread_mutex_unlock(&bridge.carQueue->wait);
		car->distance += ((float)car->varSpeed/100);
		usleep(100000);
	}
  
	dequeue(bridge.carQueue);
	free(car);
	pthread_exit(0);
}

void startCreateCars(int side){
	pthread_t thread;
	Car * car;
	int i = 0;
  int y = 0;
	double time;
	if(side){
    while(i<var[14]) {
		  car = createCar(i,side, var[6], var[7]);
		  wes.createdCars++;
      i++;
      pthread_create(&thread, NULL, (void *)drive, car);
    }
	}
	else{
    while(y<var[15]) {
      car = createCar(i,side,var[8],var[9]);
      ews.createdCars++;
      y++;
      pthread_create(&thread, NULL, (void *)drive, car);
    }
  }
}

void panel(){
	int i;
	Car * car;
	time_t start, end;
	double elapsed;
	time(&start);
	while(1){
		time(&end);
		elapsed = difftime(end, start);
    printf("== DATOS PRINCIPALES == \n");
		printf("Carros en direccion Este-Oeste: %d\n",ews.createdCars);
		printf("Carros Direccion Oeste-Este: %d\n",wes.createdCars);
    if(var[0] == 1) {
      printf("Forma de Paso: FIFO \n\n");
    }
    if(var[0] == 2) {
      printf("Forma de Paso: Semaforos \n");
      printf("Duracion del Semaforo de Oeste-Este: %i\n\n", var[10]);
      printf("Duracion del Semaforo de Este-Oeste: %i\n\n", var[11]);
    } 
    if(var[0] == 3) {
      printf("Forma de Paso: Oficial \n\n");
    }

    printf("== DATOS ACTUALES == \n");
		printf("Carros en puente: %d\n",bridge.carQueue->size);
		printf("Tamaño del puente: %d\n",bridge.size);
		printf("Lado activo:Oeste-Este %d\n",bridge.we);
		printf("Lado activo:Este-Oeste %d\n",bridge.ew);
		printf("Tiempo: %f\n\n", elapsed);

		printf("Posicion Carro  Direccion   Velocidad Actual Velocidad Original Distancia \n");
		for(i = 0; i < bridge.carQueue->size;i++){
			car = get(bridge.carQueue,i);
			if(car->side)
			printf("   %d       %d    oeste-este       %d                %d            %f \n",car->pos,car->num,car->varSpeed,car->speed,car->distance);
			else
			printf("   %d      %d     este-oeste       %d                %d            %f \n",car->pos,car->num,car->varSpeed,car->speed,car->distance);
		}	

		usleep(16666);
		printf("\033[H\033[J");
	}
}