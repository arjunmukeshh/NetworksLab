#include<stdlib.h>
#include<stdio.h>
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
		recv(clientsocket, buffer, sizeof(buffer), 0);
	
		printf("\nServer : %s",buffer);
	
		bzero(buffer, sizeof(buffer));
		printf("\nClient : ");
		scanf("%s",buffer);
	
		send(clientsocket, buffer, sizeof(buffer), 0);
	}
	close(clientsocket);
	
	
	return 0;
}