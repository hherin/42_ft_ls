#include "ft_ls.h"

int datecmp(struct timespec t1, struct timespec t2)
{
	if (t1.tv_sec < t2.tv_sec || (t1.tv_sec == t2.tv_sec && t1.tv_nsec < t2.tv_nsec))
		return -1;
	else if (t1.tv_sec > t2.tv_sec || (t1.tv_sec == t2.tv_sec && t1.tv_nsec > t2.tv_nsec))
		return 1;
	return 0;
}