#include "../ft_ls.h"

void err_exit_msg(const char *msg)
{
	ft_putstr_fd((char*)msg, 2);
	exit(1);
}

char *ft_str_slash_join(char const *s1, char const *s2);

struct directory *new_directory(const char *name, const char *pre_name)
{
	struct directory *new;

	if (!(new = malloc(sizeof(struct directory))))
		err_exit_msg("Malloc of directory failed\n");

	ft_bzero(&new->buf, sizeof(struct stat));

	new->full_path = ft_str_slash_join(pre_name, name);
	new->name = ft_strdup(name);
	new->is_valid = stat(new->full_path, &new->buf);
	new->open_dir = S_ISDIR(new->buf.st_mode) ? opendir(new->full_path) : NULL;
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
	if (new->is_valid >= 0 && datecmp(tmp->buf.st_mtim, new->buf.st_mtim) > 0)
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
		
	else {
		struct directory *tmp = head->next;

		while (tmp != head && ((!opt.modif_order && alpha_sorting(new, tmp)) || (opt.modif_order && date_sorting(new, tmp))))
			tmp = tmp->next;
		link_dir_list(tmp->prev, tmp, new);
	}

	return new;
}

void print_struct(struct directory *head)
{
	struct directory *tmp = head->next;

	printf("PATHS : %s ", head->name);
	while (tmp && tmp != head) {
		printf("%s ", tmp->name);
		tmp = tmp->next;
	}
	printf("\n");
	// printf("\nOPTION\n");

	// printf("format %d\nrecursive %d\nhid %d\nrev %d\nmodif %d\n", //opt.long_format, opt.recursive, opt.hidded, opt.reverse, opt.modif_order);
}