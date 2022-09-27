#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>

int main(){
	int clientsocket;

	clientsocket = socket(AF_INET , SOCK_STREAM , 0);
	printf("[+] Client socket created");

	struct sockaddr_in clientaddress;

	clientaddress.sin_family = AF_INET;
	clientaddress.sin_port = htons(9002);
	clientaddress.sin_addr.s_addr = INADDR_ANY;

	int status = connect(clientsocket ,(struct sockaddr *)&clientaddress, sizeof(clientaddress));
	if(status)
		printf("[+] Client socket connected");

	char buffer[1000];
	while(strcmp(buffer,"exit")!=0){
		printf("\nWebsite name : ");
		scanf("%s",buffer);
		send(clientsocket, buffer, sizeof(buffer), 0);
		if(strcmp(buffer,"exit")==0)
			break;
		
		bzero(buffer, sizeof(buffer));
		recv(clientsocket, buffer, sizeof(buffer), 0);

		printf("\n IP Address : %s",buffer);

		
		
	}
	close(clientsocket);


	return 0;
}
