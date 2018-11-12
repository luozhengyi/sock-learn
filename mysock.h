#ifndef __MYSOCK_H__
#define __MYSOCK_H__
#include <stddef.h>	/* size_t */
#include <sys/types.h>	/* ssize_t */
/*
 *@ret: return  written or read bytes, return -1 if encounters errors 
 */
ssize_t readn(int filedes, void* buff, size_t nbytes);
ssize_t written(int filedes, const void* buff, size_t nbytes);
ssize_t readline(int filedes, void* buff, size_t maxlen);









#endif	//__MYSOCK_H__
