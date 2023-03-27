#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int csockfd;	
	struct sockaddr_in server;
	char buffer[1024];
	csockfd = socket(AF_INET,SOCK_STREAM,0);
	if(csockfd==-1)
		printf("Error in socket()");
	memset(&server,0,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(12345);
	if(connect(csockfd,(struct sockaddr*)&server,sizeof(server))<0)
		printf("Error in bind()");
	int n;
	printf("Enter number to calculate factorial:");
	scanf("%d",&n);
	memset(buffer,0,1024);
	sprintf(buffer,"%d",n);
	write(csockfd,buffer,strlen(buffer));
	memset(buffer,0,1024);
	read(csockfd,buffer,1023);
	int result=atoi(buffer);
	printf("Factorial of %d is %d\n",n,result);	
	close(csockfd);	
	
	return 0;
}





