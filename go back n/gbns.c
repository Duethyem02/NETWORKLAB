#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

void itoa(int number,char numberString[])
{
	numberString[0]=(char)(number+48);
	numberString[1]='\0';
}

int main()
{
	int sockfd,nsf,size,ws=1,wc=1,we=4,ows,flag;
	char buffer[100];
	socklen_t len;
	struct sockaddr_in server,client;
	server.sin_family=AF_INET;
	server.sin_port=3033;
	server.sin_addr.s_addr=INADDR_ANY;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	printf("\nStarting up...");
	int k;
	k=bind(sockfd,(struct sockaddr*)&server,sizeof(server));
	if(k==-1)
		printf("Error in binding");
	len=sizeof(client);
	listen(sockfd,1);
	nsf=accept(sockfd,(struct sockaddr*)&client,&len);
	recv(nsf,buffer,100,0);
	fcntl(nsf,F_SETFL,O_NONBLOCK);
	printf("\nReceived a request from clinet.Sending packets one by one..");
	do
	{
		if(wc!=we)
		{
			itoa(wc,buffer);
			send(nsf,buffer,100,0);
			printf("\n Packet sent :%d\n",wc);
			wc++;
		}
		recv(nsf,buffer,100,0);
		if(buffer[0]=='R')
		{
			printf("\n**Received a RETRANSMIT packet.\nResending packet no:%c",buffer[1]);
			itoa((atoi(&buffer[1])),buffer);
			send(nsf,buffer,100,0);
			wc=atoi(&buffer[0]);
			wc++;
		}
		else if(buffer[0]=='A')
		{
			ows=ws;
			ws=atoi(&buffer[1])+1;
			we+=(ws-ows);
			printf("\n**Received ACK %c.Moving window boundary",buffer[1]);
		}
	}while(wc!=10);
	close(sockfd);
	close(nsf);
	printf("\n Sending Complete.Sockets closed.Exiting...\n");
	return(0);
}
