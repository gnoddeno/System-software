#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SIZE sizeof(struct sockaddr_in)

int main(){
	int sockfd_listen;
	int sockfd_connect;
	int client_len;

	char buff[80];
	//struct sockaddr_in server = {AF_INET, 5000, INADDR_ANY};
	struct sockaddr_in server, client;	// 16 byte

	bzero(&server, sizeof(server));	// 16 byte 0 clear
	server.sin_family = AF_INET;	// IPv4
	server.sin_port = 6000;
	server.sin_addr.s_addr = inet_addr("192.168.64.129");

	printf("Server IP : %s, Server port : %u\n",
			inet_ntoa(server.sin_addr), server.sin_port);
	//close(0);	//stdin



	printf("socket()\n");
	sockfd_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//sockfd_listen = 3
	if(sockfd_listen == -1) printf("socket error\n");

	printf("sockfd_listen = %d\n", sockfd_listen);	// 3, 0

	printf("bind()\n");

	// 1. IPv4 address
	if(bind(sockfd_listen, (struct sockaddr *)&server, SIZE) == -1) printf("bind error\n");

	printf("listen()\n");
	if(listen(sockfd_listen, 5) == -1) printf("listen error");

	printf("waiting for client\n");

	while(1){

		// 2. IPv4 address
		bzero(&client, sizeof(client));	// 16 byte 0 clear
		client_len = sizeof(client);


		sockfd_connect = accept(sockfd_listen,
			       	(struct sockaddr *)&client, &client_len);
		//sockfd_connect = 4
		if(sockfd_connect == -1) printf("accept error\n");
		printf("sockfd_connet = %d\n", sockfd_connect);

		printf("accepted\n");
		printf("SERVER: Client IP : %s, Client Port : %u\n",
				inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		if(fork() == 0) { // child process
			while(1){
				bzero(buff, sizeof(buff));
				recv(sockfd_connect, buff, sizeof(buff), 0);
				printf("Server received : %s\n", buff);

				printf("Server message: ");
				//fgets(buff, sizeof(buff), stdin);
				strcat(buff, "::SERVER");	// buff = "hello" -> "hello::SERVER"
				send(sockfd_connect, buff, strlen(buff), 0);
			}
		}	//end child
	}// end while

	printf("close()\n");
	close(sockfd_connect);
	close(sockfd_listen);
}

