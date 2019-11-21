#include <signal.h>
#include <stdio.h>
#include <string.h>

/*
 * @remark: signal handle function
 * @para: signo:
 *
 */

void handler(int signo)
{
	switch(signo)
	{
	case SIGKILL:
		printf("SIGKILL\n");
		break;
	case SIGSTOP:
		printf("SIGSTOP\n");
		break;
	case SIGINT:
		printf("SIGINT\n");
		break;
	default:
		break;
	}
}

typedef void (*funptr)(int);

int main(int argc, char* argv[])
{
	funptr pfun = NULL;
	if(argc == 1){
		printf("usage: sig.out SIG_NUM\n");
		return -1;
	}
	else{
		if(0 == strcmp(argv[1],"SIGSTOP")){
			pfun = signal(SIGSTOP, handler);
			raise(SIGSTOP);
		}else if( 0 == strcmp(argv[1], "SIGINT")){
			pfun = signal(SIGINT, handler);
			raise(SIGINT);
		}else{
			printf("Not support SIG NUM\n");
		}
		return 0;
	}
}
