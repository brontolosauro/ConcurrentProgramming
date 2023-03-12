/*
 * forkJoin2.1.0.c
 *
 *  Created on: 12 mar 2023
 *      Author: brontolosauro
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Calculate [(3+4)*(7-5)]+(10:2) with parallel computing
 * parent proces calculate (10:2)
 *
 */

int main(){

	int a, b, c, fd[2], result;
	pid_t p1, p2;

	pipe(fd);

	p1 = fork();
	p2 = fork();

	if (p1>0 && p2>0){
		// parent process
		c = 10/2;
		close(fd[1]); //close pipe's write side
		read(fd[0], &a, sizeof(a));
		printf("%d riceve dal figlio a=%d \n", getpid(), a);
		read(fd[0], &b, sizeof(b));
		printf("%d riceve dal figlio b=%d \n", getpid(), b);
	} else if (p1>0 && p2==0  ){
		// 1st child
		a = 3+4;
		close(fd[0]); //close pipe's read side
		printf("%d invia al padre %d a=3+4=%d \n", getpid(), getppid(), a);
		write(fd[1], &a, sizeof(a));
		exit(0);
	} else if (p1==0 && p2>>0  ){
		// 2nd child
		b = 7-5;
		close(fd[0]);
		printf("%d invia al padre %d b=7-5=%d \n", getpid(), getppid(), b);
		write(fd[1], &b, sizeof(b));
		exit(0);
	}else if (p1==0 && p2==0  ){
		// grandchild (from 2nd child)
		exit(0);
	}

	result = a*b+c;
	printf("[(3+4)*(7-5)]+(10:2)=%d \n", result);

	return 0;


}
