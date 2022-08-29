#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<strings.h>
#include<string.h>

int main(){
	char buffer[1000];
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM , 0);
	
	printf("[+] Server created ");
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	
	bind(server_socket , (struct sockaddr*)&server_address, sizeof(server_address));
	printf("\n[+] Socket and port 9002 are bound ");
	listen(server_socket, 5);
	printf("\n[+] Listening for clients in port 9002");
	int client_socket; 
	client_socket = accept(server_socket , NULL, NULL);
	
	while(strcmp(buffer,"exit")!=0){
		printf("\nServer : ");
		scanf("%s",buffer);
		send(client_socket , buffer , sizeof(buffer), 0 );
		bzero(buffer, sizeof(buffer));
	
		recv(client_socket, buffer, sizeof(buffer),0);
		printf("\nClient : %s",buffer);
	}
	close(server_socket);
	
	return 0;
}