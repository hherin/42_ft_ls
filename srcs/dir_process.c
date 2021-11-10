#include "../ft_ls.h"

int more_than_one_in_list(struct directory *dir)
{
	return (dir && dir->next && dir->next->next && dir->next != dir && dir->next->next != dir) ? 1 : 0;
}

void not_found_dir(char *name)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(name, 2);
	perror(": ");
}

void print_dir_name(char *name)
{
	ft_putstr_fd(name, 1); 
	ft_putstr_fd(":    ", 1);
	ft_putstr_fd("\n", 1);
}

char *ft_str_slash_join(char const *s1, char const *s2)
{
	char *new;

	if (!s1)
		return ((char *)ft_strdup(s2));
	if (!s2)
		return ((char *)ft_strdup(s1));
	int len1 = ft_strlen(s1), len2 = ft_strlen(s2);
	if (!(new = ft_calloc(sizeof(char), len1 + len2 + 2)))
		return (NULL);
	ft_memcpy(new, s1, len1);
	ft_memcpy(new + len1, "/", 1);
	ft_memcpy(new + len1 + 1, s2, len2);
	return new;
}

void print_struct(struct directory *head);

void directory_processor(struct directory *head, int rec_state)
{
	struct directory *current_dir = opt.reverse ? head->prev : head->next;
	struct directory *sub_dir = new_directory(NULL, NULL);
	int dir_in_current = 0;
	// printf("------------------------------------\n");
	while (current_dir != head)
	{
		// printf("current_dir = %s\n", current_dir->name);
		if (!current_dir->open_dir && rec_state)
			;
		else if (!current_dir->open_dir && !rec_state)
			not_found_dir(current_dir->name);
		else
		{
			// printf("\n.................................... %p\n", sub_dir);
			((!rec_state && more_than_one_in_list(head)) || rec_state) ? print_dir_name(current_dir->full_path) : 0;

			while ((current_dir->read_dir = readdir(current_dir->open_dir)))
			{
				// printf("read %s\n", current_dir->read_dir->d_name);
				if ((!ft_strncmp(".", current_dir->read_dir->d_name, 2) || !ft_strncmp("..", current_dir->read_dir->d_name, 3)) && opt.hidded == false)
					continue;
				add_new_directory(sub_dir, new_directory(current_dir->read_dir->d_name, current_dir->full_path));
					dir_in_current = 1;
				// print_struct(sub_dir);
				// printf("\n");
			}

			print_dir_content(sub_dir);
			(opt.recursive) ? directory_processor(sub_dir, RECURSIVE) : 0;
		}
		free_dir_list(sub_dir);
		sub_dir = new_directory(NULL, NULL);
		current_dir = opt.reverse ? current_dir->prev : current_dir->next;
	}
}