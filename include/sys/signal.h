
typedef struct singnaldata{
	int		type;
	int		resource;
	int		limit;
    struct proc*		waitlist;
}semaphore;
