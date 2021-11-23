#include "ft_ls.h"

int datecmp(struct timespec t1, struct timespec t2)
{
	if (t1.tv_sec < t2.tv_sec || (t1.tv_sec == t2.tv_sec && t1.tv_nsec < t2.tv_nsec))
		return -1;
	else if (t1.tv_sec > t2.tv_sec || (t1.tv_sec == t2.tv_sec && t1.tv_nsec > t2.tv_nsec))
		return 1;
	return 0;
}

int dir_total_size(struct directory *head)
{
	struct directory *tmp = head->next;
	int total = 0;

	while (tmp && tmp != head)
	{
		if (!*tmp->lpath)
			total += tmp->buf.st_blocks;
		tmp = tmp->next;
	}
	return total;
}

void free_dir_list(struct directory *head)
{
	struct directory *tmp = (head) ? head->next : NULL;
	while (tmp && tmp != head)
	{
		struct directory *next = tmp->next;
		free(tmp->full_path);
		free(tmp->name);
		free(tmp);
		tmp = NULL;
		tmp = next;
	}

	free(head);
}

void err_exit_msg(const char *msg)
{
	free_dir_list(dir_list);
	ft_putstr_fd((char *)msg, 2);
	exit(1);
}