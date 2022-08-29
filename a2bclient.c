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
	
	
	char fname[1000];
	char buffer[1000];
	
	bzero(buffer, sizeof(buffer));
	bzero(fname,sizeof(fname));
	printf("\nEnter the name(path) of file to read : ");
	scanf("%s",fname);
	//scanf("%s",buffer);
	send(clientsocket, fname, sizeof(fname), 0);
		
	bzero(buffer, sizeof(buffer));
	recv(clientsocket, buffer, sizeof(buffer), 0);
	printf("File Contents : \n%s",buffer);
		

	
	close(clientsocket);
	printf("\n[+] Disconnected");
	
	return 0;
}