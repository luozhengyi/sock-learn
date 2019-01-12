#include <stdio.h>
#include <sys/socket.h>	// socket() bind() sockaddr INADDR_ANY
#include <netinet/in.h>	// sockaddr_in
#include <strings.h>	// bzero()
#include <errno.h>	// global variable errno
#include <arpa/inet.h>	// inet_pton inet_ntop
#include <sys/select.h>	// select() FD_SET
#include <sys/time.h>
#include <stdlib.h>	// exit()
#include <unistd.h>	// close(0
#include "../mysock.h"

#define MAXLINE 1024

#ifndef SA
	#define SA struct sockaddr
#endif

#define max(a,b) (a>b?a:b)

#define SRV_PORT 7887
#define SRV_ADDR "127.0.0.1"

void str_cli(FILE *fp, int sockfd)
{
	int maxfdp1, stdineof;
	fd_set rset;
	char buf[MAXLINE];
	int n;

	stdineof = 0;
	FD_ZERO(&rset);

	for(;;)
	{
		if( stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		select(maxfdp1, &rset, NULL, NULL, NULL);

		if(FD_ISSET(sockfd, &rset))	// socket is readable
		{
			if( (n = read(sockfd, buf, MAXLINE)) == 0)
			{
				if(stdineof == 1)
					return;
				else
				{
					printf("str_cli: server terminated preamturely\n");
					exit(-1);
				}
			}
			write(fileno(stdout), buf, n);
		}
		
		if(FD_ISSET(fileno(fp), &rset))	// input is readable
		{
			if( (n = read(fileno(fp), buf, MAXLINE)) == 0)
			{
				stdineof = 1;
				shutdown(sockfd, SHUT_WR);	// send FIN
				FD_CLR(fileno(fp), &rset);
				continue;
			}
			write(sockfd, buf, n);
		}
	}
}

int main(int argc, char* argv[])
{
	int iRet = -1;
	int fd;
       	struct sockaddr_in addrSrv;

	bzero(&addrSrv,sizeof(addrSrv));
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(SRV_PORT);
	inet_pton(AF_INET, SRV_ADDR, &addrSrv.sin_addr);
	do
	{
		if( (fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		{
			printf("create socket fd falied!\n");
			break;
		}

		if( connect(fd, (SA*)&addrSrv, sizeof(addrSrv)) < 0)
		{
			printf("connect failed: ");
			if(errno == ETIMEDOUT)	
				printf("time out\n");
			else if(errno == ECONNREFUSED)
				printf("refused\n");
			else
				printf("host unreach\n");
			break;	
		}

		str_cli(stdin, fd);

	}while(0);

	close(fd);
	return iRet;
}
