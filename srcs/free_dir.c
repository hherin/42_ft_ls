#include "ft_ls.h"

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