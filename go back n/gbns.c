#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int sockfd,nsf,size,ft=1,cp,wait=3;
	char data[100],digit[2];
	struct sockaddr_in client;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	client.sin_family=AF_INET;
	client.sin_port=3033;
	client.sin_addr.s_addr=INADDR_ANY;
	printf("\nStarting up...");
	size=sizeof(client);
	printf("\nEstablishing connection to server..");
	connect(sockfd,(struct sockaddr*)&client,size);
	sprintf(data,"REQUEST");
	send(sockfd,data,strlen(data),0);
	do
	{
		recv(sockfd,data,100,0);
		cp=atoi(data);
		printf("\nGot Packet:%d",cp);
		if(cp==3 && ft)
		{
			printf("\n***Simulation =:Packet data corrupted or incomplete");
			printf("\n***sending RETRANSMIT for packet 1");
			memset(&data,0,sizeof(data));
			sprintf(data,"R1");
			send(sockfd,data,strlen(data),0);
			ft=0;
		}
		else 
		{
			wait--;
			if(!wait)
			{
				printf("\n***Packet accepted->sending ACK");
				wait=3;
				sprintf(data,"A");
				digit[0]=(char)(cp+48);
				digit[1]='\0';
				strcat(data,digit);
				send(sockfd,data,strlen(data),0);
			}
		}
	}while(cp!=9);
	printf("\n All packets received.Exiting...\n");
	close(sockfd);
	return(0);
}
