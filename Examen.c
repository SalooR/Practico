#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <math.h>
#include <sys/wait.h>
#include <signal.h>

int aux=0;

typedef struct{
    int hash;
    int old_hash;
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
}block;

block array[99999999999];

int resolver_potencia(int a){
    int exp=a;
    for(int i=0; i<exp; i++){
        exp *= a;
    }
    return exp;
}

void crear_bloque(){
    int status;
    pid_t pid_h = fork();
    if(pid_h==-1){
        printf("Error: proceso no creado");
        exit(EXIT_FAILURE);
    }
    if(pid_h==0){
        printf("Proceso hijo creado-%d\n", getpid());
        pthread_create(&array[aux].t1,NULL,&resolver_potencia,NULL);
        pthread_create(&array[aux].t2,NULL,&resolver_potencia,NULL);
        pthread_create(&array[aux].t3,NULL,&resolver_potencia,NULL);
        pthread_join(&array[aux].t1,NULL);
        pthread_join(&array[aux].t2,NULL);
        pthread_join(&array[aux].t3,NULL);
    }else{
        printf("Proceso padre  %d\n", getpid());
        wait(NULL);
    }
    if(WIFEXITED(status)){ 
        printf("Bloque creado, status = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)){
        printf("signal %d\n", WTERMSIG(status));
    }
}

int main(){
    int old_hash = rand()%30+1;
    while(1){
        crear_bloque(aux);
        aux++;
    }
}