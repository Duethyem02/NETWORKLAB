#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>//SOCK_STREAM
#include<netinet/in.h>//sock_addr
#include<netdb.h>//tcp function calls
#include<stdlib.h>//exit
#include<string.h>
int main()
{
	char b[100];//buffer-b
	int n;	
	int sockfd,cid,length;
	struct sockaddr_in saddress,client;
	sockfd=socket(AF_INET,SOCK_STREAM,0);//domain-ipv4(AF_INET),type-tcp,protocol-ip(0)
	if(sockfd==-1)
	{
		printf("socket not created\n");
		exit(0);
	}
	else
		printf("Socket successfully created\n");
	bzero(&saddress,sizeof(saddress));
	saddress.sin_family=AF_INET;
	saddress.sin_addr.s_addr=INADDR_ANY;
	saddress.sin_port=8080;
	if((bind(sockfd,(struct sockaddr *)&saddress,sizeof(saddress)))!=0)
	{
		printf("socket binding failed\n");
		exit(0);
	}
	else
		printf("Socket binding done successfully\n");
	if((listen(sockfd,5))!=0)
	{
		printf("Listen failed\n");
		exit(0);
	}
	else
		printf("server listening\n");
	length=sizeof(client);
	cid=accept(sockfd,(struct sockaddr *)&client,&length);
	if(cid<0)
	{
		printf("Server accept failed\n");
		exit(0);
	}
	else
		printf("server accept client\n");
	n=recv(cid,b,100,0);
	if(n==-1)
		printf("Error in receiving");
	printf("Message from client:%s",b);
	close(sockfd);
	return 0;
}
/*
Socket successfully created
Socket binding done successfully
server listening
server accept client
Message from client:welcome
*/
