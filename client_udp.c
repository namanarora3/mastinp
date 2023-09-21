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
int sock_fd,len,n;
struct sockaddr_in servaddr;
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
len=sizeof(servaddr);

printf("Enter String: ");
n=0;
while((buff[n++]=getchar())!='\n')
;
sendto(sock_fd,buff,strlen(buff),0,(struct sockaddr *)&servaddr,len);
bzero(buff, sizeof(buff));
recvfrom(sock_fd,buff,sizeof(buff),0,(struct sockaddr *)&servaddr,&len);
printf("Echoing back: %s",buff);
close(sock_fd);
}