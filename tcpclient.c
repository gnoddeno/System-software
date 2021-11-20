#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE sizeof(struct sockaddr_in)

int main(void){
	int sockfd;
	//char send_c, recv_c;
	char message[80];

	
	//struct sockaddr_in server = {AF_INET, 5000};
	struct sockaddr_in server;	// 16 byte

	bzero(&server, sizeof(server));	// 0 clear
	server.sin_family = AF_INET;	// IPv4
	server.sin_port = 5000;
	//server.sin_addr = INADDR_ANY;
	server.sin_addr.s_addr = inet_addr("192.168.64.129"); //personal ip 
	
	printf("Server IP : %s, ServerPort : %u\n", inet_ntoa(server.sin_addr),server.sin_port);

	//server.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("socket()\n");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)printf("socket erroe\n");

	printf("connect()\n");
	connect(sockfd, (struct sockaddr *)&server, SIZE);

	while(1){
		printf("client message: ");
		fgets(message, sizeof(message), stdin);
		send(sockfd, message, strlen(message)-1, 0);
	
		bzero(message, sizeof(message));
		recv(sockfd, message, sizeof(message), 0);
		printf("client received : %s\n", message);
	}
	printf("close()\n");
	close(sockfd);
}

