#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define MAXLINE 1024

int main(int argc, char **argv)
{
	int iRet = -1;
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;

	do
	{
		if((listenfd = socket(AF_INET, SOCK_STREAM, 0))<0)
		{
			printf("socket() error\n");
			break;
		}
		
		bzero(&servaddr,sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(13);
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

		if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
		{
			printf("bind() error: %s\n",strerror(errno));
			break;
		}
		
		if(listen(listenfd,5)<0)
		{
			printf("listen() error\n");
			break;
		}

		for(;;)
		{
			connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);

			ticks = time(NULL);
			snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
			write(connfd,buff,strlen(buff));

			close(connfd);
		}

		iRet = 0;
	}while(0);


	close(listenfd);
	return iRet;
}
