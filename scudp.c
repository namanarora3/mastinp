#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>

int main(){
	char str[100], str2[100];
	int listen_fd, clen;
	struct sockaddr_in servaddr, cli;
	
	listen_fd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(22000);
	
	bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	
	while(1){
		while(1){
			clen = sizeof(cli);
			bzero(&str, 100);
			recvfrom(listen_fd, str, 100, 0, (struct sockaddr *) &cli, &clen);
			printf("They- %s", str);
			if(strncmp("exit",str,4)==0){
				printf("Exiting...");
				break;
			}
			bzero(&str2, 100);
			printf("You- ");
			fgets(str2,100,stdin);
			sendto(listen_fd, str2, strlen(str2), 0, (struct sockaddr *) &cli, clen);
			if(strncmp("exit",str2,4)==0){
				printf("Exiting...");
				break;
			}
		}
	}
	close(listen_fd);

}

