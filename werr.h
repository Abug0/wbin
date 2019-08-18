/* 
 * werr.h
 * 错误处理相关
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef int (*HELP_CALL)();  /* 函数指针类型，指向具体的help函数 */

int werror(char*, char*);
int whelp(int(*uhelp)());