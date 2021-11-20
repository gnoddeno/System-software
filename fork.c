#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(void){
	pid_t p1,p2,p3,p4,p5,p6,p7;

	p1 = fork();
	if(p1 > 0){
		p2 = fork();
		if(p2 > 0){
			printf("parent process pid = %d\n",getpid());
                        printf("parent process ppid = %d\n",getppid());
                        printf("parent process child#1 = %d\n",p1);
                        printf("parent process child#2 = %d\n",p2);
			sleep(30);
		}else if (p2 == 0){
			printf("child#2 process pid = %d\n",getpid());
			printf("child#2 process ppid = %d\n",getppid());
			p6 = fork();
			if(p6 > 0){
				p7 = fork();
				if(p7 > 0){
					printf("parent process pid = %d\n",getpid());
                        		printf("parent process ppid = %d\n",getppid());
                        		printf("parent process child#6 = %d\n",p6);
                       			printf("parent process child#7 = %d\n",p7);
                        		sleep(30);
				}else if(p7 == 0){
		                        printf("child#7 process pid = %d\n",getpid());
		                        printf("child#7 process ppid = %d\n",getppid());
				}else{
					printf("fork error\n");
				}
			}else if(p6 == 0){
	                        printf("child#6 process pid = %d\n",getpid());
	                        printf("child#6 process ppid = %d\n",getppid());
			}else{
				printf("fork error\n");
			}
		}else{
			printf("fork error\n");
		}
		sleep(30);
	}else if(p1 == 0){
		printf("child#1 process pid = %d\n",getpid());
		printf("child#1 process ppid = %d\n",getppid());
		p3 = fork();
		if(p3>0){
			p4 = fork();
			if(p4 > 0){
				p5 = fork();
				if(p5 > 0){
                                        printf("parent process pid = %d\n",getpid());
                                        printf("parent process ppid = %d\n",getppid());
                                        printf("parent process child#3 = %d\n",p3);
                                        printf("parent process child#4 = %d\n",p4);
					printf("parent process child#5 = %d\n",p5);
                                        sleep(30);
				}else if(p5 ==0){
                                printf("child#5 process pid = %d\n",getpid());
                                printf("child#5 process ppid = %d\n",getppid());
				}else{
					printf("fork error\n");
				}
			}else if(p4 == 0){
                                printf("child#4 process pid = %d\n",getpid());
                                printf("child#4 process ppid = %d\n",getppid());
			}else{
				printf("fork error\n");
			}
		}else if(p3 == 0){
			printf("child#3 process pid = %d\n",getpid());
			printf("child#3 process ppid = %d\n",getppid());
		}else{
			printf("fork error\n");
		}
	}else{
		printf("fork error\n");
	}
	return 0;
}
 
