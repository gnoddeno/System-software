#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(void){
	pid_t p1,p2,p3,p4,p5,p6,p7;

	//parent process
	p1 = fork();

	if(p1 > 0){	//parent process

		p2 = fork();
		if(p2 == 0){	//child 2 process
			printf("child #2 process pid : %d \n" ,getpid());
                        printf("child #2 process ppid : %d \n" ,getppid());
			p6 = fork();
			p7 = fork();

		}
		else if(p2 <0) { 
			printf("fork error \n");
		}
		else {	//parent process
			printf("parent process pid : %d\n",getpid());
	                printf("parent process ppid : %d\n",getppid());
        	        printf("parent process child#1 id : %d\n",p1);
                        printf("parent process child#2 id : %d\n",p2);


			sleep(30);
		}
		sleep(30);
	}
	else if(p1 < 0){
		printf("fork error\n");
	}
	else{	//child 1 process
		printf("child #1 process pid : %d \n" ,getpid());
		printf("child #1 process ppid : %d \n" ,getppid());
		p3 = fork();
		p4 = fork();
		p5 = fork();
	}
	printf("---------------------------");
	
}
