/*
 * exe003.c
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
 * calculate (3+x)-(5-y)*(7*z+3)
 *
 * x readen from stdin inside parent process
 * y,z readen from stdin inside main()
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(){

	int x,y,z;
	int a,b,c,result;
	int fd[2];
	pid_t p1,p2;

	pipe(fd);

	printf("this program calculate: \n");
	printf("(3+x)-(5-y)*(7*z+3) \n");
	printf("where x,y,z are given by the user. \n");

	printf("pls enter y: ");
	scanf("%d", &y);
	printf("pls enter z: ");
	scanf("%d", &z);

	p1=fork();
	p2=fork();

	if (p1>0 && p2>0){
		printf("pls enter x: ");
		scanf("%d", &x);

		a=3+x;
	} else if (p1==0 && p2>0){
		b=5-y;

		close(fd[0]);
		write(fd[1], &b, sizeof(b));
		exit(0);
	} else if (p1>0 && p2==0){
		c=7*z+3;

		close(fd[0]);
		write(fd[1], &c, sizeof(c));
		exit(0);
	}else if (p1==0 && p2==0){
		exit(0);
	}

	close(fd[1]);
	read(fd[0], &b, sizeof(b));
	read(fd[0], &c, sizeof(c));

	result=a-b*c;
	printf("(3+x)-(5-y)*(7*z+3)= \n");
	printf("%d-%d*%d=%d", a, b, c, result);

	return(0);

}
