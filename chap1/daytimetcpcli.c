#include <sys/socket.h>	/* socket() connect().... apis */
#include <stdio.h>
#include <netinet/in.h>	/* sockaddr_in */
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>

#define MAXLINE 1024
typedef char bool;
#define true 1

int main(int argc, char *argv[])
{
	int iRet = -1;
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	do{
		if(argc != 2)
		{
			printf("usage: a.out <IPaddress\n");
			break;
		}

		if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		{
			printf("socket() error\n");
			break;
		}

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(13);	/* daytime server */
		if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0)
		{
			printf("inet_pton() error for %s\n",argv[1]);
			break;
		}

		if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
		{
			printf("connect() error\n");
			break;
		}

		bool bflag = true;
		while((n = read(sockfd,recvline,MAXLINE))>0)
		{
			recvline[n] = 0; /* null terminate */
			if(fputs(recvline,stdout) == EOF)
			{
				printf("fputs() error\n");
				break;
			}
		}
		if(!bflag)
			break;
		if(n<0)
		{
			printf("read() error\n");
			break;
		}
		
		iRet = 0;
	}while(0);
	close(sockfd);
	return iRet;
}
