#include "ft_ls.h"

static void free_content(struct directory *dir)
{
	(dir->open_dir) ? closedir(dir->open_dir) : 0;
	free(dir->full_path);
	free(dir->name);
	free(dir);
}

void free_dir_list(struct directory *head)
{
	struct directory *tmp = head->next;
	while (tmp && tmp != head)
	{
		struct directory *next = tmp->next;
		free_content(tmp);
		tmp = NULL;
		tmp = next;
	}

	free(head);
}