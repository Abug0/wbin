/* 
 * wwho.c
 * 
 * @TODO:时间计算bug已解决，但未探明原因
 */


#include <stdio.h>

#include <fcntl.h>
#include <utmp.h>
#include <unistd.h>
#include <time.h>

#include "werr.h"

int do_who();
int show_info(struct utmp*);
int do_help();


int main(int argc, char *argv[])
{
	HELP_CALL uhelp = do_help;
	if (argc != 1)
	{
		whelp(uhelp);	
		exit(1);
	}
	
	do_who();
	
	return 0;
}


int do_who()
{
	int fd = open(UTMP_FILE, O_RDONLY);
	
	if (fd == -1)
		werror("OPEN FAILED", "");
	
	struct utmp record;
	int reclen = sizeof(struct utmp);
	
	while (read(fd, &record, reclen) == reclen)
		show_info(&record);
	
	if (close(fd) == -1)
		werror("CLOSE ERROR", "");
	
	return 0;
}

int show_info(struct utmp* record)
{
	if (record->ut_type != USER_PROCESS)
		return 0;
	//printf("%d\t", record->ut_type);
	printf("%-8.8s", record->ut_user);
	printf("%-8.8s", record->ut_line);
	long t = record->ut_time;
	printf("%-10.20s", ctime(&t));
	printf("(%s)\n", record->ut_host);
	
	//int32_t t1 = record->ut_time;
	/* 时间计算bug,问题解决,但未找到原因
	time_t *tt = &record->ut_time;
	int32_t *t1 = &record->ut_time;
	int32_t *t2 = &record->ut_time + 4;
	printf("tt--%d, t1--%d,  t2--%d.\n", *tt, *t1, *t2);
	
	
	show(&record->ut_time);
	printf("%d----", *(&record->ut_time));
	printf("%-10.20s", ctime(&(record->ut_time)));
	
	printf("login time:%d\t", record->ut_tv.tv_sec);
	//time(&record->ut_tv);
	printf("login time:%s\t", ctime((&(record->ut_tv.tv_sec))));
	*/
	
	return 0;
}


/* 
 * wwho的帮助信息
 */
int do_help()
{
	printf("Usage:wwho\n");
	
	return 0;
}

/*
 * 调试时间计算bug
int show_time(long timeval)
{
	long rawtime = timeval;
    struct tm * timeinfo;
 
    //time (&rawtime);
	//rawtime = 1566090938;
	//printf("time:%d\n", rawtime);
	printf("time:%s\n", ctime(&rawtime));
    //timeinfo = localtime ( &rawtime );
    //printf ( "The current date/time is: %s", asctime (timeinfo) );
 
    return 0;
}

int show(const time_t *timer)
{
	printf("timer:%d.=====", *timer);
	printf("@@%-10.20s@@@", ctime(&timer));
	return 0;
}
*/