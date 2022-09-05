#include<stdio.h>

#include<string.h>

#include<sys/stat.h>

#include<sys/types.h>

#include<sys/socket.h>

#include<netinet/in.h>

#include<arpa/inet.h>



int main()

{

    struct sockaddr_in client,server;

    int s,n;

    fd_set readfds;

    

    char b1[100],b2[100];

    s=socket(AF_INET,SOCK_DGRAM,0);

    

    server.sin_family=AF_INET;

    server.sin_port=2000;

    server.sin_addr.s_addr=INADDR_ANY;

    

    if(bind(s,(struct sockaddr *)&server,sizeof(server))<0)

    {

    	perror("\nBind failed");

    	exit(EXIT_FAILURE);

    }

    

    

    printf("\nServer bound.\n");

    printf("Server listening on port #2000");

    n=sizeof(client);

    while(1)

    {

        recvfrom(s,b1,sizeof(b1),0,(struct sockaddr *) &client,&n);

        if(!(strcmp(b1,"end")))

            break;

        printf("\nClient:%s",b1);

        printf("\nServer:");

        gets(b2);

        sendto(s,b2,sizeof(b2),0,(struct sockaddr *) &client,n);

    }

    return 0;

 

}
