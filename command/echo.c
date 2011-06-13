#include "stdio.h"

int main(int argc, char * argv[])
{

	int i;
	//	printf("pid is %d \n",getpid());
//	sourceinit(1,0,5,getpid());
//	sourcesignal(1,getpid());
//	sourcewait(1,getpid());
	for (i = 1; i < argc; i++)
		printf("%s%s", i == 1 ? "" : " ", argv[i]);
	printf("\n");

	return 0;
}
