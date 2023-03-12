/*
 * forkJoin1.2.1.c
 *
 *  Created on: 12 mar 2023
 *      Author: brontolosauro
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>l

int main(){
    pid_t pid1, pid2;
    int val, x, y, z, fd[2];

    // creo la pipe
    pipe(fd);

    pid1 = fork();
    pid2 = fork();
    if(pid1>0 && pid2>0){ // processo padre
        printf("sono il processo padre pid: %d\n"
               "devo calcolare z=x+y \n", getppid());

        printf("chiudo la scrittura\n", getppid());
        close(fd[1]); // chiudo la scrittura; il lato inutilizzato della pipe va' chiuso
        printf("leggo la pipe\n", getppid());
        read(fd[0], &x, sizeof(x));
        printf("ricevo dal proceso figlio x=%d\n", x);

        //questa non serve; visto che successive chiamate read si dovrebbero bloccare fino a che non vengono inseriti
        //nuovi dati
        //printf("chiudo la lettura\n", getppid());
        //close(fd[0]); // chiudo la lettura;


        //anche questa non serve; già fatta all'inizio
        //printf("chiudo la scrittura\n", getppid());
        //close(fd[1]); // chiudo la scrittura

        printf("leggo la pipe\n", getppid());
        read(fd[0], &y, sizeof(y));
        printf("ricevo dal proceso figlio y=%d\n", y);
        printf("chiudo la lettura\n", getppid());
        close(fd[0]); // chiudo la lettura;
    } else if(pid1==0 && pid2>0) { // figlio
        printf("\tsono il processo figlio pid: %d\n", getpid());
        printf("\til processo padre ha pid:%d\n", getppid());
        printf("\tchiudo la lettura\n", getpid());
        close(fd[0]); // chiudo la lettura; perchè uso la pipe solo in scrittura
        val = 3+5;
        printf("\tscrivo la pipe\n", getpid());
        printf("\tinvio al padre val=%d\n", val);
        write(fd[1], &val,sizeof (val));

        //mi sa che anche queste operazioni creano solo problemi al prossimo processo
        printf("\tchiudo la scrittura\n", getpid());
        close(fd[1]); //chiudo la scrittura

        printf("\ttermino l'esecuzione\n", getpid());
        exit(0); //devo terminarlo altrimente prosegue con l'esecuzione di una parte di codice che non gli compete
    } else if(pid1>0 && pid2==0){ // figlio
        printf("\t\tsono il processo figlio pid: %d\n", getpid());
        printf("\t\til processo padre ha pid:%d\n", getppid());
        printf("\t\tchiudo la lettura\n", getpid());
        close(fd[0]); // chiudo la lettura
        val = 4-6;
        printf("\t\tscrivo la pipe\n", getpid());
        printf("\t\tinvio al padre val=%d\n", val);
        write(fd[1], &val, sizeof (val));

        //come sopra; meglio evitare per evitare problemi; non sai quale processo viene eseguito per primo
        printf("\t\tchiudo la scrittura\n", getpid());
        close(fd[1]); //chiudo la scrittura

        printf("\t\ttermino l'esecuzione\n", getpid());
        exit(0); //devo terminarlo altrimente prosegue con l'esecuzione di una parte di codice che non gli compete
    }else if(pid1==0 && pid2==0){ // figlio
        printf("\t\t\tsono il processo figlio pid: %d\n", getpid());
        printf("\t\t\til processo padre ha pid:%d\n", getppid());
        printf("\t\t\t non ho nulla da fare\n");
        printf("\t\t\ttermino l'esecuzione\n", getpid());
        exit(0); //devo terminarlo altrimente prosegue con l'esecuzione di una parte di codice che non gli compete
    }
    z = x*y;
    printf("-> risultato finale z=%d\n", z);

    return 0;

}

