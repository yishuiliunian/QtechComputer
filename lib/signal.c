
#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "signal.h"
#include "global.h"
#include "proto.h"
PUBLIC int sourcewait(int type,int pid)
{
	MESSAGE msg;
    msg.type = SEMWAIT;
	msg.TYPE = type;
	msg.PID = pid;
	printf("%d\n",pid);
	send_recv(SEND, TASK_SIGNAL, &msg);
}

PUBLIC int sourcesignal(int type, int pid)
{
	MESSAGE msg;
    msg.type = SEMSIGNAL;
	msg.TYPE = type;
	msg.PID = pid;
	printf("signal sending %d\n",pid);
	send_recv(SEND, TASK_SIGNAL, &msg);
}
PUBLIC int sourceinit(int type, int limit, int source,  int pid)
{
	MESSAGE msg;
    msg.type = SEMINIT;
	msg.TYPE = type;
	msg.LIMIT = limit;
	msg.RESOURCE = source;
	msg.PID = pid;
	printf("sending messge\n");
	send_recv(SEND, TASK_SIGNAL, &msg);
}
