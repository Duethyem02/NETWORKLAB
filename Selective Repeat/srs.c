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
 int ss;
 struct sockaddr_in saddr,caddr;
 socklen_t len;
 struct frame f1;
 int ws,tp,tf,i=0,j=0,fs=0,k,l,buffer;
 struct ack acknowledgement;
 char req[50];
 ss=socket(AF_INET,SOCK_DGRAM,0);
 bzero((char*)&saddr,sizeof(saddr));
 saddr.sin_family=AF_INET;
 saddr.sin_port=htons(5018);
 saddr.sin_addr.s_addr=INADDR_ANY;
 bind(ss,(struct sockaddr*)&saddr,sizeof(saddr));
 bzero((char*)&caddr,sizeof(caddr));
 len=sizeof(caddr);
 printf("\nWaiting for client connection");
 recvfrom(ss,req,sizeof(req),0,(struct sockaddr*)&caddr,&len);
 printf("\nThe client connection obtained\t%s\n",req);
 printf("\nsending request for window size\n");
 sendto(ss,"REQUEST FOR WINDOWSIZE",sizeof("REQUEST FOR WINDOWSIZE"),0,(struct sockaddr*)&caddr,sizeof(caddr));
 printf("Waiting for the window size\n");
 recvfrom(ss,(char*)&ws,sizeof(ws),0,(struct sockaddr*)&caddr,&len);
 printf("\nThe window size obatined as:\t%d\n",ws);
 printf("\nObtaining packets from the network layer\n");
 printf("\nTotal packets obtained:%d\n",(tp=ws*5));
 printf("\nTotal frames or windows to be transmitted:%d\n",(tf=5));
 printf("\nSending total number of packets\n");
 sendto(ss,(char*)&tp,sizeof(tp),0,(struct sockaddr*)&caddr,sizeof(caddr));
 recvfrom(ss,req,sizeof(req),0,(struct sockaddr*)&caddr,&len);
 printf("\nSending total number of frames\n");
 sendto(ss,(char*)&tf,sizeof(tf),0,(struct sockaddr*)&caddr,sizeof(caddr));
 recvfrom(ss,req,sizeof(req),0,(struct sockaddr*)&caddr,&len);
 printf("\nPress enter to start the process\n");
 fgets(req,2,stdin);
 while(i<tp)
 {
 	bzero((char*)&f1,sizeof(f1));
 	printf("\nInitailizing the transmit buffer\n");
 	printf("\nThe frame to be send is %d with packets:",fs);
 	buffer=i;
 	j=0;
 	while(j<ws && i<tp)
 	{
 		printf("%d",i);
 		f1.packet[j]=i;
 		j++;
 		i++;
 	}
 	printf("Sending frame %d\n",fs);
 	sendto(ss,(char*)&f1,sizeof(f1),0,(struct sockaddr*)&caddr,sizeof(caddr));
 	printf("Waiting for acknowledgement");
 	recvfrom(ss,(char*)&acknowledgement,sizeof(acknowledgement),0,(struct sockaddr*)&caddr,&len);
 	j=0;k=0;l=buffer;
 	while(j<ws && l<tp)
 	{
 		if(acknowledgement.acknowledgement[j]==-1)
 		{
 			printf("\n Negative acknowledgement received for packet:%d\n",f1.packet[j]);
 			printf("\n Retransmitting from packet:%d\n",f1.packet[j]);
 			i=f1.packet[j];
 			k=l;
 			break;
 		}
 		j++;
 		l++;
 	}
 	if(k=0)
 	{
 		printf("\n Positive acknowledgement received for all packets,within the frame:%d\n",fs);
 	}
 	fs++;
 	printf("\n Press enter to proceed\n");
 	fgets(req,2,stdin);
 }
 printf("\n All frames sends successfully\nClosing connection with the client\n");
 close(ss);
}
