#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<arpa/inet.h>

struct frame
{
	int packet[40];
};

struct ack
{
	int acknowledgement[40];
};

int main()
{
 int cs;
 struct sockaddr_in serveraddr;
 socklen_t len;
 struct hostent *server;
 struct frame f1;
 int ws,tp,tf,i=0,j=0,fr=0,k,l,buffer;
 struct ack acknowledgement;
 char req[50];
 cs=socket(AF_INET,SOCK_DGRAM,0);
 bzero((char*)&serveraddr,sizeof(serveraddr));
 serveraddr.sin_family=AF_INET;
 serveraddr.sin_port=htons(5018);
 server=gethostbyname("127.0.0.1");
 bcopy((char*)server->h_addr,(char*)&serveraddr.sin_addr.s_addr,sizeof(server->h_addr));
 printf("\nSending request to server\n");
 sendto(cs,"HI I AM CLIENT",sizeof("HI I AM CLIENT"),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
 printf("Waiting for reply\n");
 recvfrom(cs,req,sizeof(req),0,(struct sockaddr*)&serveraddr,&len);
 printf("\n The server has to send :\t%s\n",req); 
 printf("\nEnter the window size\n");
 scanf("%d",&ws);
 printf("\n sending window size\n");
 sendto(cs,(char*)&ws,sizeof(ws),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr)); 
 printf("\n waiting for the server response\n");
 recvfrom(cs,(char*)&tp,sizeof(tp),0,(struct sockaddr*)&serveraddr,&len);
 printf("\nThe total packets are:\t%d\n",tp);
 sendto(cs,"RECEIVED",sizeof("RECEIVED"),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
 recvfrom(cs,(char*)&tf,sizeof(tf),0,(struct sockaddr*)&serveraddr,&len);
 printf("\nTotal no. frames or windows are:\t%d\n",tf);
 sendto(cs,"RECEIVED",sizeof("RECEIVED"),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
 printf("\nStarting the process of receiving\n");
 while(i<tp)
 {
 	printf("\nInitailizing the receiving buffer\n");
 	printf("\nThe expected frame is %d with packets:",fr);
 	buffer=i;
 	j=0;
 	while(j<ws && i<tp)
 	{
 		printf("%d",i);
 		j++;
 		i++;
 	}
 	printf("\nWaiting for the frame\n");
 	recvfrom(cs,(char*)&f1,sizeof(f1),0,(struct sockaddr*)&serveraddr,&len);
 	printf("\n Receivrd frame:%d\n\n enter -1 to send negative acknowledgement for the following packets\n",fr);
 	j=0;k=0;l=buffer;
 	while(j<ws && l<tp)
 	{
 		printf("\n Packet:%d\n",f1.packet[j]);
 		scanf("%d",&acknowledgement.acknowledgement[j]);
 		if(acknowledgement.acknowledgement[j]==-1)
 		{
 			if(k==0)
 			{
 				i=f1.packet[j];
 				k=1;
 			}
 		}
 		j++;
 		l++;
 	}
 	fr++;
 	sendto(cs,(char*)&acknowledgement,sizeof(acknowledgement),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
 }
 printf("\n All frames receivrd successfully\nClosing connection with the server\n");
 close(cs);
}
