#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<strings.h>
#include<string.h>

#define MAXLEN 1000
int main(){
	char buffer[MAXLEN+1];
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
	
	
	bzero(buffer, sizeof(buffer));
	char fname[1000];
	bzero(fname, sizeof(fname));
	printf("\nReading file : ");
	recv(client_socket, fname, sizeof(fname),0);
	printf("%s",fname);
	//READING THE FILE
	FILE *fp = fopen(fname,"r");
	if(fp!=NULL){
		size_t newLen = fread(buffer, sizeof(char), MAXLEN, fp);
    		if (ferror(fp)!=0) 
        		fputs("Error reading file", stderr);
       		else 
    	   		buffer[newLen++] = '\0'; //terminating with null string
       		fclose(fp);
	}
	
	printf("\nIn buffer : %s",buffer);
	send(client_socket , buffer , sizeof(buffer), 0 );
		
	
	close(server_socket);
	printf("\n[+] Client disconnected");
	
	return 0;
}