#include<stdio.h>

#include<string.h>

#include<strings.h>

#include<netinet/in.h>

#include<arpa/inet.h>

#include<sys/types.h>

#include<sys/sockets.h>

#include<stdlib.h>

#include<unistd.h>

#include<fcntl.h>



void main(){

	char buffer[100];

	int sockfd;

	

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	printf("[+] SOcket created");

	

	struct sockaddr_in saddr;

	saddr.sin_family = AF_INET;

	saddr.sin_port = htons(9002);

	saddr.sin_addr.s_addr = INADDR_ANY;

	

	while(strcmp(buffer, "exit")!=0){

		bzero(buffer,sizeof(buffer));

		printf("Client: ");

		scanf("%s",buffer);

		sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&saddr, sizeof(saddr));

		bzero(buffer,sizeof(buffer));

		recvfrom(sockfd, buffer,sizeof(buffer), 0, (struct sockaddr *)&saddr, sizeof(saddr));

		printf("Server : %s", buffer);

	}

	close(sockfd);

}
