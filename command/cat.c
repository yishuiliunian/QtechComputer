#include "stdio.h"

int main(int argc, char * argv[])
{
	int fd;
	int i = 0;
	char* buf;
	if(argc != 2)
	{
		printf("SORRY ERROR! YOU CAN NOT USE CAT LIKE THAT!\n");
		return 0;
	}
	fd = open(argv[1], O_RDWR);
	if(fd == -1)
	{
		printf("open error!\n");
		return 0;
	}
	else
		while(i <= 100)
		{
		if(read(fd, buf, 1)== 'b') return 0;
	    else printf("%s",buf);
		i++;
		}
	printf("\n");
	close(fd);
	return 0;
}



