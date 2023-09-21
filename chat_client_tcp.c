#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    int sockfd, n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while (1)
    {
        bzero(sendline, 100);
        fgets(sendline, 100, stdin);
        send(sockfd, sendline, strlen(sendline), 0);
        if (strncmp("exit", sendline, 4) == 0)
        {
            printf("Exiting...");
            break;
        }
        bzero(recvline, 100);
        recv(sockfd, recvline, 100, 0);
        printf("%s", recvline);
        if (strncmp("exit", recvline, 4) == 0)
        {
            printf("Exiting...");
            break;
        }
    }
}