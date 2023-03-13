/*
 * exe001.c
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
 * calculate 5*[(2+4)*(7+3)]-10
 */

#include <stdio.h>
#include <stdlib.h>
//#include <types.h>
#include <unistd.h>
#include <wait.h>

int main(){

	int a, b, result, fd[2];
	pid_t p1;

	pipe(fd);

	p1 = fork();

	if (p1>0){
		a=2+4;
	} else if (p1==0){
		b=7+3;
		close(fd[0]);
		write(fd[1], &b, sizeof(b));
		exit(0);
	}
	close(fd[1]);
	read(fd[0], &b, sizeof(b));
	result=5*(a*b)-10;
	printf("5*[(2+4)*(7+3)]-10=%d", result);

	//system("PAUSE");
	return(0);
}
