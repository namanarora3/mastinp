#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
char buff[100];
int sock_fd,clen;
struct sockaddr_in servaddr,cli;
sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
if(sock_fd==-1){
printf("Socket Creation Failed...\n");
exit(0);
}
else{
printf("Socket Created Successfully...\n");
}

bzero(&servaddr, sizeof(servaddr));

servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(22000);

if(bind(sock_fd, (struct sockaddr *) &servaddr, sizeof(servaddr))!=0){
printf("Socket Bind Failed..\n");
exit(0);
}
else{
printf("Socket is binded successfully..\n");
}
clen=sizeof(cli);

while(1){
bzero(buff, 100);
recvfrom(sock_fd,buff,sizeof(buff),0,(struct sockaddr *)&cli,&clen);
printf("Client Side Port: %i...\n",cli.sin_port);
printf("Echoing back: %s",buff);
sendto(sock_fd,buff,strlen(buff),0,(struct sockaddr *)&cli,clen);
if(strncmp("exit",buff,4)==0){
printf("Client Exited...\n");
break;
}
}
close(sock_fd);
}