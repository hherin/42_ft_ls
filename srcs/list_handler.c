#include "ft_ls.h"

struct directory *new_directory(const char *name, const char *pre_name)
{
	struct directory *new;

	if (!(new = malloc(sizeof(struct directory))))
		err_exit_msg("Malloc of directory failed\n");

	ft_bzero(&new->buf, sizeof(struct stat));
	ft_bzero(new->lpath, 512);
	new->full_path = ft_str_sep_join(pre_name, name, "/");
	new->name = ft_strdup(name);
	if (new->full_path)
		readlink(new->full_path, new->lpath, 512);
	new->is_valid = (*new->lpath) ? lstat(new->full_path, &new->buf) : stat(new->full_path, &new->buf);
	new->next = NULL;
	new->prev = NULL;

	return new;
}

static void link_dir_list(struct directory *prev, struct directory *next, struct directory *new)
{
	prev->next = new;
	next->prev = new;
	new->prev = prev;
	new->next = next;
}

static int alpha_sorting(struct directory *new, struct directory *tmp)
{
	if (new->is_valid >= 0 && tmp->is_valid < 0)
		return 1;
	if (new->is_valid >= 0 && ft_strncmp(tmp->name, new->name, ft_strlen(tmp->name) + 1) < 0)
		return 1;
	if (new->is_valid < 0 && tmp->is_valid < 0 && ft_strncmp(tmp->name, new->name, ft_strlen(tmp->name) + 1) < 0)
		return 1;
	return 0;
}

static int date_sorting(struct directory *new, struct directory *tmp)
{
	if (new->is_valid >= 0 && tmp->is_valid < 0)
		return 1;
	if (new->is_valid >= 0 && datecmp(tmp->buf.st_mtimespec, new->buf.st_mtimespec) > 0)
		return 1;
	if (new->is_valid < 0 && tmp->is_valid < 0 && ft_strncmp(tmp->name, new->name, ft_strlen(tmp->name) + 1) < 0)
		return 1;
	return 0;
}

struct directory *add_new_directory(struct directory *head, struct directory *new)
{
	default_path = false;

	if (!new)
		return NULL;

	if (!head->next && !head->prev)
		link_dir_list(head, head, new);

	else
	{
		struct directory *tmp = head->next;

		while (tmp != head && ((!opt.modif_order && alpha_sorting(new, tmp)) || (opt.modif_order && date_sorting(new, tmp))))
			tmp = tmp->next;
		link_dir_list(tmp->prev, tmp, new);
	}

	return new;
}