/*
 * parametroIngresso.c
 *
 *  Created on: 13 mar 2023
 *      Author: brontolosauro
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int ritorno; //variabile globale per ritorno da thread
void* code(void* arg);

int main(){
	pthread_t tid;
	int ingresso=1;
	pthread_create(&tid, NULL, code, (void*) &ingresso);

	return 0;
}

void* code(void* arg){
	int datoIngresso;
	datoIngresso = *(int*)arg; //caste e deferenziazione
	datoIngresso++;
	printf("valore processato da thread: %d\n", datoIngresso);

	return 0;
}
