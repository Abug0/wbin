/* 
 * werr.c
 * 错误处理
 */

#include "werr.h"

/* 
 * 打印出错信息
 */
int werror(char *err_str, char *ext_str)
{
	printf("Error:%s.\n", err_str);
	perror(ext_str);
	
	exit(1);
}


/* 
 * 打印帮助信息
 */
int whelp(int(*uhelp)())
{
	//printf("Usage:wcp src dst\n");
	uhelp();
	
	return 0;
}