/* 
 * wcp.c 1.0
 * 使用read和write实现cp命令
 * 
 * usage:wcp src dst
 *
 * @TODO:设置缓冲区提升性能
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 15

int werror(char*, char*);
int do_cp(char*, char*);


int main(int argc, char* argv[])
{
	if (argc != 3)
		werror("help", "");

	do_cp(argv[1], argv[2]);
	
	return 0;
}


/* 
 * cp的具体实现
 *
 * @param char* src_file 源文件名
 * @param char* dst_file 目标文件名
 *
 * @return int
 */
int do_cp(char *src_file, char *dst_file)
{
	int fd_src, fd_dst;
	if ((fd_src = open(src_file, O_RDONLY)) == -1)
		werror("OPEN FAILED", src_file);
	
	if ( (fd_dst = creat(dst_file, 0644)) == -1)
		werror("CREATE FAILED", dst_file);
	
	int n_chars = 0;
	char *buf = (char*)calloc(BUFSIZE, sizeof(char));
	
	while( (n_chars = read(fd_src, buf, BUFSIZE)) > 0 )
	{
		
		if (write(fd_dst, buf, n_chars) != n_chars)
			werror("WRITE ERROR", "");
	}

	if ( (close(fd_src) == -1) || (close(fd_dst) == -1))
		werror("CLOSE ERROR", "");
	
	return 0;
}


/* 
 * 打印出错信息
 */
int werror(char *err_str, char *ext_str)
{
	if (strcmp(err_str, "help") == 0)
		whelp();
	
	printf("Error:%s.\n", err_str);
	perror(ext_str);
	
	exit(1);
}


/* 
 * 打印帮助信息
 */
int whelp()
{
	printf("Usage:wcp src dst\n");
	
	return 0;
}