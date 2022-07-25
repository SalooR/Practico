#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct{
	char nom_af;
	int cant_cash;
} Afiliado;

typedef struct{
	char nom_caja;
	char nom_empleado;
} Caja;

static void *solicitar_caja(void *args);
static void *caja_disponible(void *args);

int contador = 0;
sem_t semaforo;

int main(){
	pthread_t hilo1, hilo2;
	
	sem_init(&semaforo, 0, 1);
	
	pthread_create(&hilo1, NULL, *solicitar_caja, NULL);
	pthread_create(&hilo2, NULL, *caja_disponible, NULL);
	
	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);
	
	printf("Turno caja: %d \n", contador);
	
	return 0;	
}

static void *solicitar_caja(void *args){
	sem_wait(&semaforo);
	contador +=1;
	sem_post(&semaforo);
}

static void *caja_disponible(void *args){
	sem_wait(&semaforo);
	contador -=1;
	sem_post(&semaforo);
}
