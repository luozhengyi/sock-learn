#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>	//inet_pton inet_ntop
#include "../mysock.h"
#include <errno.h>

#define SRV_PORT 7887
#define SRV_ADDR "127.0.0.1"

#define MAXLINE 1024

#ifndef SA
	#define SA struct sockaddr
#endif

void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];
	while(fgets(sendline, MAXLINE, fp))
	{
		write(sockfd, sendline, strlen(sendline));
		if(readline(sockfd,recvline,MAXLINE) == 0)
		{
			printf("str_cli: server terminated prematruely\n");
			exit(-1);
		}
		fputs(recvline, stdout);
	}
}

int main(int argc, char* argv[])
{
	int iRet = -1;
	int sockfd;
	
	struct sockaddr_in addrSrv;	

	bzero(&addrSrv, sizeof(addrSrv));
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(SRV_PORT);
	inet_pton(AF_INET, SRV_ADDR, &addrSrv.sin_addr);

	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket fd create failed!\n");
		return iRet;
	}

	if(connect(sockfd, (SA*)&addrSrv, sizeof(addrSrv)) < 0)
	{
		printf("connect failed!\n%d\n",errno);
		return iRet;
  	}		

	str_cli(stdin, sockfd);
	close(sockfd);
	return iRet;
}
