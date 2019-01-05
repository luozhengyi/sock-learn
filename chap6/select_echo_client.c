#include <stdio.h>
#include <sys/socket.h>	//socket() bind() sockaddr INADDR_ANY
#include <netinet/in.h>	//sockaddr_in
#include <strings.h>	//bzero()
#include <errno.h>	//global variable errno
#include <arpa/inet.h>	//inet_pton inet_ntop

#ifndef SA
	#define struct sockaddr
#endif

#define SRV_PORT 7887
#define SRV_ADDR "127.0.0.1"

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
		if( (fd = socket(AF_INET,SOCK_STREAM,0) < 0)
		{
			printf("create socket fd falied!\n");
			break;
		}

		

	}while(0);
	return iRet;
}
