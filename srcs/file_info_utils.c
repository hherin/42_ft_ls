#include "../ft_ls.h"

struct file_info *new_file(const char *name)
{
	struct file_info *new;

	if (!(new = malloc(sizeof(struct file_info))))
		err_exit_msg("Malloc of file_info failed\n");
	ft_bzero(new, sizeof(struct file_info));
	new->name = ft_strdup(name);
	new->next = NULL;
	new->prev = NULL;

	return new;
}

void add_new_file(struct file_info *new)
{
	if (!files->next && !files->prev) {
		files->next = new;
		files->prev = new;
		return ;
	}

	struct file_info *last_elem = files->prev;
	last_elem->next = new;
	files->prev = new;

	new->next = files;
	new->prev = last_elem;
}

bool file_list_empty(void)
{
	return files->next ? false : true;
}

