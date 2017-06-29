/*
 *      Proyecto 1 de Sistemas Operativos
 *      principal.h
 *      
 *      David Ugalde
 *      Cristian Díaz
 * 
 */

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
      car = createCar(y,side,var[8],var[9]);
      ews.createdCars++;
      y++;
      pthread_create(&thread, NULL, (void *)drive, car);
    }
  }
}

void gotoxy (int x,int y){ //reubicacion del puntero en pantalla
printf("\033[%d;%df", y,x);
	};

void imprime()
{
system("clear");
printf("Proyecto puente estrecho \n");
printf("David Ugalde Solis, Cristian Diaz \n \n");
printf("Modo de interaccion: %i",var[0]);

gotoxy(74,9);
printf("Carros en puente: %d\n",bridge.carQueue->size);
gotoxy(80,3);
printf("Tamaño del puente: %d\n",bridge.size);

gotoxy(57,5);
printf("\t\t Vehiculos este-oeste: %i ",ews.createdCars);
gotoxy(0,5);
printf("\t\t Vehiculos oeste-este: %i ",wes.createdCars);
gotoxy(53,9);
printf("Simulacion Puente");
gotoxy((55)-bridge.size/2,10);
printf("{");
for(int i=0;i<var[1];i++){
printf("-");
}
printf("}");

gotoxy(1,12);
printf("Lista de Vehiculos Oeste-Este");
gotoxy(1,13);
printf("Posicion Carro Vel.Actual Vel.Original Distancia");
for(int i=0;i<var[14];i++)
{
gotoxy(1,14+i);
printf("   -_-     %d       %d         %d          %f   ", i,0,0,0);
}


gotoxy(60,12);
printf("Lista de Vehiculos Este-Oeste");
gotoxy(60,13);
printf("Posicion Carro Vel.Actual Vel.Original Distancia");
for(int i=0;i<var[15];i++)
{
gotoxy(60,14+i);
printf("   -_-     %d       %d         %d          %f   ", i,0,0,0);
}

}
void panel(){
	int i;
	Car * car;
	time_t start, end;
	double elapsed;
	time(&start);
        char Puente[var[1]];
        for(int i=0;i<bridge.size;i++){Puente[i]='0';}
        imprime();
	while(1){
		time(&end);
		elapsed = difftime(end, start);
                gotoxy(90,1);
                printf("Tiempo: %f\n",elapsed);
                gotoxy(74,9);
                printf("Carros en puente: %d\n",bridge.carQueue->size);
                gotoxy((55)-bridge.size/2,10);
                printf("{");
                for(int i=0;i<var[1];i++){
                printf("-");
                 }
                printf("}");
	for(i = 0; i < bridge.carQueue->size;i++){
			car = get(bridge.carQueue,i);
			if(car->side){
gotoxy((56)-(bridge.size/2)+(int)car->distance,10);
printf("O");
fflush(stdout);
gotoxy(1,14+car->num);
printf("    %d      %d       %d         %d          %f   ",car->pos,car->num,car->varSpeed,car->speed,car->distance);
fflush(stdout);
			}else{

gotoxy((56)+(bridge.size/2)-(int)car->distance,10);
printf("E");
fflush(stdout);
gotoxy(60,14+car->num);
printf("    %d      %d       %d         %d          %f   ",car->pos,car->num,car->varSpeed,car->speed,car->distance);
fflush(stdout);
		}

}

		usleep(16666);
	}
}
