#include<stdio.h>

#include<string.h>

#include<strings.h>

#include<stdlib.h>

#include<netinet/in.h>

#include<sys/types.h>

#include<sys/socket.h>

#include<unistd.h>

#include<netdb.h>



void main(){

	int sockfd, csize, arr[30], pre =0, flag, p, i;

	char buff[100];

	

	fd_set readfds;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	for(int i =0; i<30; i++){

		arr[i] = 0;

	}

	

	struct sockaddr_in saddr,caddr;

	saddr.sin_family = AF_INET;

	saddr.sin_port = htons(9002);

	saddr.sin_addr.s_addr = INADDR_ANY;

	

	int status = bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr), 0);

	printf("[+] Bind succesfful");

	

	listen(sockfd,5);

	printf("[+] Listening ");

	bzero(&saddr, sizeof(saddr));

	

	FD_ZERO(&readfds);

	while(1){

		FD_SET(sockfd, &readfds);

		csize = sizeof(caddr);

		select(sockfd +1 , &readfds, NULL, NULL,NULL);

		recvfrom(sockfd,buffer,1024, 0 , (struct sockaddr *)&caddr, &csize);

		p = ntohs(caddr.sin_port);

		flag = 0;

		printf("%d",p);

		for(i =0 ; i<30;i++){

			if(arr[i] ==p){

				p = i+1;

				flag = 1;

				break;

			}

		}

		if(flag ==0){

			arr[pre] = p;

			pre++;

			p = pre;

		}

		

		printf("\n Client %d : %s\n",p,buffer);

		csize = sizeof(saddr);

		sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&caddr, csize);

	}

	close(sockfd);

	return 0;

}
