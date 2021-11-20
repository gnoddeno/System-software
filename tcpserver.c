#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE sizeof(struct sockaddr_in)

int main(){
	int sockfd_listen;
	int sockfd_connect;
	int client_len;

	char buff[80];
	//char c;
	//struct sockaddr_in server= {AF_INET, 5000, INADDR_ANY};
	struct sockaddr_in server, client;	// 16 byte

	bzero(&server, sizeof(server));	// 0 clear
	server.sin_family = AF_INET;	// IPv4
	server.sin_port = 5000;
	//server.sin_addr = INADDR_ANY;
	server.sin_addr.s_addr = inet_addr("192.168.64.129"); //personal ip  

	printf("Server IP : %s, ServerPort : %u\n", inet_ntoa(server.sin_addr),server.sin_port);


	printf("socket()\n");
	sockfd_listen = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd_listen == -1) printf("socket error\n");

	printf("bind()\n");

	//1. IPv4 address
	if(bind(sockfd_listen, (struct sockaddr *)&server, SIZE) == -1) printf("bind error\n");

	printf("listen()\n");
	if(listen(sockfd_listen, 5) == -1) printf("listen error\n");

	printf("wating for client\n");

	//2. IPv4 address
	bzero(&client, sizeof(client));
	client_len = sizeof(client);
	
	sockfd_connect = accept(sockfd_listen, (struct sockaddr *)&client, &client_len);
	if(sockfd_connect == -1) printf("accept error\n");

	printf("accepted\n");
	printf("SERVER: Client IP : %s, Client Port : %u\n",
			inet_ntoa(client.sin_addr), ntohs(client.sin_port));

	while(1){
		bzero(buff, sizeof(buff));
		recv(sockfd_connect, buff, sizeof(buff), 0);
		printf("Server received %s\n", buff);

        	printf("server message: ");
	        fgets(buff, sizeof(buff), stdin);
	        send(sockfd_connect, buff, strlen(buff)-1, 0);
	}

	printf("close()\n");
	close(sockfd_connect);
	close(sockfd_listen);
}

