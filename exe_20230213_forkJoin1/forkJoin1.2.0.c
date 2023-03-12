/*
 * forkJoin1.2.0.c
 *
 *  Created on: 12 mar 2023
 *      Author: brontolosauro
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>l

int main(){
    pid_t pidFiglio;
    int x, y, z, fd[2];
    int val=0;

    // creo la pipe
    pipe(fd);

    pidFiglio = fork();
    if(pidFiglio != 0){ // processo padre
        printf("sono il processo padre pid: %d\n", getppid());
        y = 4-6;
        printf("calcolo y=4-6=%d\n", y);
        printf("sono il processo padre pid: %d; chiudo la scrittura\n", getppid());
        close(fd[1]); // chiudo la scrittura
        printf("sono il processo padre pid: %d; leggo la pipe\n", getppid());
        read(fd[0], &x, sizeof(x));
        printf("ricevo dal proceso figlio x=%d\n", x);
        printf("sono il processo padre pid: %d; chiudo la lettura\n", getppid());
        close(fd[0]); // chiudo la lettura;
    } else { // figlio
        printf("\tsono il processo figlio pid: %d\n", getpid());
        printf("\tsono il processo figlio pid: %d; chiudo la lettura\n", getpid());
        close(fd[0]); // chiudo la lettura
        x = 3+5;
        printf("\tsono il processo figlio pid: %d; scrivo la pipe\n", getpid());
        write(fd[1], &x, x);
        printf("\tinvio al padre x=3+5%d\n", x);
        printf("\tsono il processo figlio pid: %d; clhiudo la scrittura\n", getpid());
        close(fd[1]); //chiudo la scrittura
        printf("\tsono il processo figlio pid: %d; termino l'esecuzione\n", getpid());
        exit(0); //devo terminarlo altrimente prosegue con l'esecuzione di una parte di codice che non gli compete
    }
    z = x*y;
    printf("-> risultato finale z=%d\n", z);

    return 0;

}

