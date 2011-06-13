#include "stdio.h"
int main(int argc, char* argv[])
{
	int fd;
	char* buf="aaaab";
	char* readbuf[6];
	if(argc != 2) 
	{
		printf("manule: mkfile /[name]\n");
		return 0;
	}
	fd = open(argv[1], O_CREAT | O_RDWR);
	printf("%s",argv[1]);
	if(fd == -1)
	{
		printf("file exsited!");
		return 0;
	}
	if(write(fd, buf, 5) == -1) printf("write error\n");
	if(read(fd, buf, 5) == -1) printf("read error\n");
	readbuf[5] = "\0";
	printf("%s",readbuf);
	close(fd);
	return 0;
}

