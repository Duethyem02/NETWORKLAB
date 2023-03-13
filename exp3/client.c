#include<stdio.h>
#include<sys/socket.h>//SOCK_STREAM
#include<netinet/in.h>//tcp function calls
#include<stdlib.h>//exit
#include<string.h>

int main()
{
	char b[100];
	int k;
	int sockfd;
	struct sockaddr_in client;
	sockfd=socket(AF_INET,SOCK_STREAM,0);//domain-ipv4(AF_INET),type-tcp,protocol-ip(0)
	if(sockfd==-1)
	{
		printf("socket not created\n");
		exit(0);
	}
	else
		printf("Socket successfully created\n");
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=INADDR_ANY;
	client.sin_port=8080;
	if((connect(sockfd,(struct sockaddr *)&client,sizeof(client)))==-1)
	{
		printf("Connection with the server failed\n");
		exit(0);
	}
	else
		printf("Connected to the server\n");
	printf("\nEnter data to be send:");
	fgets(b,100,stdin);
	k=send(sockfd,b,100,0);
	if(k==-1)
		printf("Error in sending");
	close(sockfd);
	return 0;
}
/*
Socket successfully created
Connected to the server

Enter data to be send:welcome
*/
