#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE sizeof(struct sockaddr_in)

int main(){
	int sockfd_listen;
	int sockfd_connect;

	char c;
	struct sockaddr_in server = {AF_INET, 5000, INADDR_ANY};

	printf("socket()\n");
	sockfd_listen = socket(AF_INET, SOCK_STREAM, 0);
	//socket()함수는 소켓을  만드는 함수로 AF_INET 은 IPv4를, SOCK_STREAM은 TCP통신을 0은 프로토콜의 값을 결정하는 것

	printf("bind()\n");
	bind(sockfd_listen, (struct sockaddr *)&server, SIZE);
	//bind() 함수는 소켓에 IP주소와 포트번호를 지정해 준다. 만들어놓은 소켓 sockfd_listen과, 소켓의 정보를 담은 구조체인 (struct sockaddr *)&server를, SIZE는 이 sockaddr 구조체의 크기이다.

	printf("listen()\n");
	listen(sockfd_listen, 5);
	//listen() 함수는 클라이언트로부터의 연결 요청을 처리, sockfd_listen은 소켓을, 5는 연결 요청을 대기시킬 공간 설정

	printf("wating for client\n");
	sockfd_connect = accept(sockfd_listen, NULL, NULL);
	//accept() 함수는 해당 소켓에 연결 요청이 왔을 때 연결을 받아들이는 함수이다. sockfd_listen은 연결을 기다리는 소켓, 두번째 인자는 Client 주소,포트 정보를 저장할 구조체, 세번째 인자는 sockaddr 구조체의 길이가 저장된 변수의 주소값이다.
	printf("accepted\n");

	recv(sockfd_connect, &c, 1, 0);
	printf("recv %c from client\n", c);
	//recv() 함수는 소켓으로부터 데이터를 수신한다.sockfd_connect는 연결된 소켓이며, &c는 수신받은 데이터가 저장될 버퍼의 주솟값, 세 번째 인자는 버퍼의 최대 길이를 나타내고, 네 번째 인자는 옵션플래그 이다.

	c = 'g';
	printf("send %c to client\n", c);
	send(sockfd_connect, &c, 1, 0);
	//send() 함수는 연결된 서버나 클라이언트로 데이터를 전송한다. sockfd_connect는 데이터를 보낼 소켓, &c는 송신할 데이터, 세 번째 인자는 버퍼의 쵀대 길이, 네 번째 인자는 옵션플래그이다.


	printf("close()\n");
	close(sockfd_connect);
	close(sockfd_listen);
}

