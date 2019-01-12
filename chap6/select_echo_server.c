#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>	// bzero()
#include <netinet/in.h>	// sockaddr_in
#include <errno.h>
#include <sys/select.h>

#ifndef SA
#define SA struct sockaddr
#endif

#define SRV_PORT 7887
#define SRV_ADDR "127.0.0.1"
#define MAX_CONN 1024
#define MAX_LINE 1024

void str_echo(int listenfd)
{
	fd_set rset;
	int maxfdp1 = 0;
	int connfd[FD_SETSIZE];
	int fd = 0;
	int iready = 0;
	int i = 0;
	int clientfd= -1;
	struct sockaddr_in addrCli;
	socklen_t clilen;
	int rdsize = 0;	// the size that read() return
	char rdbuf[MAX_LINE];	


	for(fd = 0; fd < FD_SETSIZE; ++fd)	// initial the connfd
		connfd[fd] = -1;	
	connfd[listenfd] = 1;
	FD_ZERO(&rset);



	for(;;)
	{
		for(fd = 0; fd<FD_SETSIZE; ++fd)
		{
			if(connfd[fd]>0)
			{
				maxfdp1 = fd+1;
				FD_SET(fd, &rset);
			}
		
		}
		
			
		iready = select(maxfdp1, &rset, NULL, NULL, NULL);

		for(fd=0; fd<maxfdp1; ++fd)
		{
			if(connfd[fd]>0 && FD_ISSET(fd,&rset))
			{
				
				if(fd == listenfd)	// listen socket
				{
					clilen = sizeof(addrCli);
					clientfd = accept(listenfd, (SA*)&addrCli, &clilen);	
					if(clientfd >= FD_SETSIZE)
					{
						printf("the fd is bigger than FD_SETSIZE\n");
						return;
					}
					else if(clientfd > 0)
					{
						connfd[clientfd] = 1;
						// printf("new connection\n");
					}
					else
					{
						printf("accept failed\n");
						return;
					}

					if(--iready <= 0)	// no more ready fd
						break;
				}
				else		// connected socket
				{
					if( (rdsize = read(fd, rdbuf, MAX_LINE)) > 0)
					{
						write(fd, rdbuf, rdsize);
						// write(fileno(stdout), rdbuf, rdsize);
					}					
					else
					{
						close(fd);
						connfd[fd] = -1;
						FD_CLR(fd, &rset);
					}

					if(--iready <= 0)	// no more ready fd
						break;
				}
			}

		}
	}



}


int main(int argc, char* argv[])
{
	int iRet = -1;
	int listenfd, connfd;
	struct sockaddr_in addrSrv;

	bzero(&addrSrv, sizeof(addrSrv));
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(SRV_PORT);
	addrSrv.sin_addr.s_addr = htonl(INADDR_ANY);
	
	do
	{
		if( (listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		{
			printf("create listen socket failed\n");
			break;			
		}
		
		if(bind(listenfd, (SA*)&addrSrv, sizeof(addrSrv)) < 0)
		{
			printf("bind listen socket failed\n");
			break;
		}
		
		if(listen(listenfd, MAX_CONN) < 0 )
		{
			printf("listen failed\n");
			break;
		}

		str_echo(listenfd);

		iRet = 0;
	}while(0);

	return iRet;
}
