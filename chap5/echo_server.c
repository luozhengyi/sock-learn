#include <stdio.h>
#include <strings.h> 	// bzero()
#include <string.h>
#include <sys/socket.h>	// socket() bind() listen() accept() sockaddr INADDR_ANY
#include <netinet/in.h>	// sockaddr_in
#include <errno.h>	// global variable errno
#include <stdlib.h>	// exit()
#include <signal.h> 	// signal()
#include <sys/wait.h>	// wait()

#define MAXLINE 1024

#ifndef SA
	#define SA struct sockaddr
#endif

#define SRV_PORT 7887
#define MAX_CONN 1024

void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];
again:
	while( (n = read(sockfd, buf, MAXLINE)) >0)
	{
		printf("RECV: %s",buf);
		write(sockfd, buf, n);	
		memset(buf, 0, MAXLINE);
	}

	if(n < 0 && errno == EINTR)
		goto again;
	else if(n < 0)
	{
		printf("str_echo: read error\n");
		exit(-1);
	}
}

void handler(int sigNum){
	pid_t pid;
	int stat;

	pid = wait(&stat);
	printf("child %d terminated\n", pid);
	return;
}


int main(int argc, char* argv[])
{
	int iRet = -1;

	int listenfd, connfd;
	struct sockaddr_in addrSrv, addrCli;
	socklen_t lenCli;
	pid_t childpid;

	if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("create socekt fd failed!\n");
		return iRet;
	}
		
	bzero(&addrSrv,sizeof(struct sockaddr_in));
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(SRV_PORT);
	addrSrv.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(listenfd, (SA*)&addrSrv, sizeof(addrSrv)) < 0)
	{	
		printf("bind socket fd failed!\n");
		return iRet;
	}

	if(listen(listenfd,MAX_CONN) < 0)
	{
		printf("listen socket fd failed!\n");
		return iRet;
	}

	
	// add signal handler
	signal(SIGCHLD,handler);

	for(;;)
	{
		lenCli = sizeof(addrCli);
		if( (connfd = accept(listenfd, (SA*) &addrCli, &lenCli)) < 0)
		{
			if(errno == EINTR)
				continue;
			else{
				printf("accept failed!\n");
				return iRet;	
			}
				
		}

		if( (childpid = fork()) == 0)	// child process
		{
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		else if(childpid > 0)	// parent process
		{
			close(connfd);
		}
	}

	return iRet;
}
