/*
 * exe002.c
 *
 *  Created on: 12 mar 2023
 *      Author: brontolosauro
 */

/*
 * rif: Nuovo Tecnologie e progettazzione di sistemi
 * 		informatici e di telecomunicazione, vol. 2
 * 		pag 92
 * 		exe 1
 *
 *
 * calculate (3+2)*(5-7)+(8-3)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {

	int a, b, c, result;
	int fd[2];
	pid_t p1, p2;

	pipe(fd);

	p1=fork();
	p2=fork();

	if (p1>0 && p2>0){
		c=(8-3);
	} else if (p1==0 && p2>0){
		a=(3+2);
		close(fd[0]);
		write(fd[1], &a, sizeof(a));
		exit(0);
	} else if (p1>0 && p2==0){
		b=(5-7);
		close(fd[0]);
		write(fd[1], &b, sizeof(b));
		exit(0);
	} else if (p1==0 && p2==0){
		exit(0);
	}

	close(fd[1]);
	read(fd[0], &a, sizeof(a));
	read(fd[0], &b, sizeof(b));

	result=a*b-c;

	printf("(3+2)*(5-7)+(8-3)= \n");
	printf("%d*%d+%d=%d \n", a, b, c, result);

	return(0);

}
