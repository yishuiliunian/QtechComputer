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
PRIVATE void block(struct proc* currunt)
{
	int i;
	struct proc* pbp;
	pbp = proc_table;
	currunt->p_flags = PROBLOCKED;
	/*
	for(i=0; i<NR_PROCS+NR_TASKS; i++)
	{
		if(pbp->p_flags == PROBLOCKED) panic("%d",i);
		pbp++;
	}
	*/
	schedule();
}

PRIVATE void unblock(struct proc* currunt)
{
	currunt->p_flags = 0;
	schedule();
}
/*
 * 初始化信号量
 */
int initsemaphore(int type, int limit, int resource)
{
	int i;
	semaphore* p = semaphore_table;
	for(i=0; i<NRSEMAPHORE; i++,p++)
		if(p->type == type) return 1;
	p = semaphore_table;
	for(i=0; i<NRSEMAPHORE; i++,p++)
		if(p->type == NONETYPE) 
			break;


	p->limit = limit;
	p->resource  = resource;
	p->type = type;
	p->waitlist = NONENEXT;
	
//	panic("resource = %d, limit = %d",p->resource,p->limit);
	assert(semaphore_table[0].type == 1);
	return 0;
}
/*
 * signal_wait操作
 */
int signal_wait(int type, struct proc* currunt) 
{
	int i;
	struct proc* pbp;
	semaphore* p = semaphore_table;
	assert(type == 1);
	for(i=0; i<NRSEMAPHORE; i++)
	{
		if(p->type == type) break; 
		p++;
	}
	assert(p->type == type);
	p->resource--;
	if(p->resource <= p->limit)
	{
		currunt->next = NONENEXT;
		if(p->waitlist != NONELIST)
		{
			for(pbp = p->waitlist; pbp->next != NONENEXT; pbp=pbp->next); // 找到等待队列的最后一个进程
			pbp->next = currunt;
		}
		else p->waitlist = currunt;
		assert(p->waitlist == currunt);
		assert(currunt->next == NONENEXT);
		block(currunt);
	}

}

int signal(int type)
{
	int i;
	struct proc* pbp;
	semaphore* p = semaphore_table;
	for(i=0; i<NRSEMAPHORE; i++)
	{
		if(p->type == type) break;
		p++;
	}
	p->resource++;
	assert(type == 1);
	if(p->waitlist != NONELIST)
	{
		pbp = p->waitlist;
		unblock(pbp);
		p->waitlist = pbp->next;
	}
	return;
}




PUBLIC void task_signal()
{
	MESSAGE msg;
	while(1){
	send_recv(RECEIVE, ANY , &msg);
	switch(msg.type)
	{
		case SEMWAIT:
			signal_wait(msg.TYPE, &(proc_table[msg.PID]));
			break;
		case SEMSIGNAL:
			signal(msg.TYPE);
			break;
		case SEMINIT:
			initsemaphore(msg.TYPE, msg.LIMIT, msg.RESOURCE);
			break;
		default:
			panic("semaphore fault\n");
			break;
	}
	}
}
