#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>

int fact(int n)
{
	if (n==0)
		return(1);
	else 
		return n*fact(n-1);
}

int main()
{
	int ssockfd,csockfd;	
	struct sockaddr_in server,client;
	socklen_t client_len=sizeof(client);
	char buffer[1024];
	ssockfd = socket(AF_INET,SOCK_STREAM,0);
	if(ssockfd==-1)
		printf("Error in socket()");
	memset(&server,0,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(12345);
	if(bind(ssockfd,(struct sockaddr*)&server,sizeof(server))<0)
		printf("Error in bind()");
	listen(ssockfd,5);
	printf("Server is listening..\n");
	while(1)
	{
		csockfd=accept(ssockfd,(struct sockaddr*)&client,&client_len);
		if(csockfd==-1)
			printf("Error in accept()");
		memset(buffer,0,1024);
		read(csockfd,buffer,1023);
		int n=atoi(buffer);
		int result=fact(n);
		memset(buffer,0,1024);
		sprintf(buffer,"%d",result);
		write(csockfd,buffer,strlen(buffer));
		close(csockfd);	
	}
	return 0;
}
