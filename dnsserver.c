#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<strings.h>
#include<
//dns table

char arr[100][100] = { "www.google.com", "142.89.78.66",
						   "www.yahoo.com", "10.2.45.67",
						   "www.annauniv.edu", "197.34.53.122", 
						   "lms.ssn.edu.in", "182.75.25.237"};
//returns index of element in arr;
int search(char str[100]){
	int ind = 0 ;
	for(int i = 0 ; i< 4 ; i++){
		if(strcmp(str,arr[i])==0){
			return i+1;
		}
	}
	return -1;
}

int main(){ 
	
		
	printf("-----------------PROGRAM TO IMPLEMENT DNS(exit to EXIT, prefix websitename with m to modify)---------------\n");
	char buffer[1000];
	bzero(buffer, sizeof(buffer));
	
	//display dns table
	//display();
	
	//create file descriptor
	int sockfd;
	
	
	//socket call
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd<0)
		perror("[-] Socket not created");
	
	printf("[+] Socket created");
	
	//struct address
	
	
	struct sockaddr_in serveraddr;
	serveraddr.sin_addr.s_addr  = INADDR_ANY;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9002);
	

	//bind
	if(bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr))>0)
		printf("[-] Bind failure\n");
	else
		printf("\n[+] Bind success \n");
		
	
	//listen
	listen(sockfd,5);
	
	//accept
	int clientsocket = accept(sockfd,NULL,NULL);
	
	//data exchange
	
	char old[100],new[100];
	int changed = -1;
	while(strcmp(buffer,"exit")!=0 ){
		recv(clientsocket, buffer, sizeof(buffer),0);
		printf("\nClient Request : %s",buffer);
		
		if(strcmp(buffer,"exit")==0)
			break;
		
		if(strcmp(buffer, arr[changed])==0){
			send(clientsocket , new , sizeof(buffer), 0 );
			
		}
		int index = search(buffer);
		bzero(buffer, sizeof(buffer));
		strcpy(buffer,arr[index]);
		printf("\nServer : %s",buffer);
		
		
		printf("\n Do you want to modify : (y/n)");
		char ch ;
		ch = getch();
		if(ch == 'y'){
			changed = index;
			strcpy(old,buffer);
			printf("\nNew IP : ");
			char new[100];
			scanf("%s",new);
			strcpy(arr[index],new);
			//validate()
			
		}
		//Send the char[index] as index = search(buffer);
		send(clientsocket , buffer , sizeof(buffer), 0 );
	}
	close(sockfd);
	
	
	return 0;
	
}
