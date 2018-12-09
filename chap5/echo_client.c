#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>	//inet_pton inet_ntop

#define SRV_PORT 7887
#define SRV_ADDR "127.0.0.1"

#ifndef SA
	#define SA struct sockaddr
#endif

void str_cli(FILE *fp, int sockfd)
{
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

	if(connect(sockfd, (SA*)&addrSrv, sizeof(addrSrv)) < 0)
	{
		printf("connect failed!\n");
		return iRet;
  	}		

	str_cli(stdin, sockfd);

	return iRet;
}
