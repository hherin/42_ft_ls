#include "ft_ls.h"

int more_than_one_in_list(struct directory *dir)
{
	return (dir && dir->next && dir->next->next && dir->next != dir && dir->next->next != dir) ? 1 : 0;
}

void directory_processor(struct directory *head, int rec_state)
{
	struct directory *current_dir = opt.reverse ? head->prev : head->next;
	struct directory *sub_dir = new_directory(NULL, NULL);

	while (current_dir && current_dir != head)
	{
		// if inside recursive and (not a directory or current_dir == '.' or '..')
		if (rec_state && (!current_dir->open_dir || (!ft_strncmp(".", current_dir->name, 2) || !ft_strncmp("..", current_dir->name, 3))))
			;
		else if (!current_dir->open_dir && !rec_state)
			print_not_found_dir(current_dir->name);
		else
		{
			if ((!rec_state && more_than_one_in_list(head)) || rec_state)
				ft_printf("%s: \n", current_dir->full_path);
			if (opt.long_format)
				ft_printf("total %d\n", current_dir->buf.st_blksize / 512);

			// loop that store content of the directory in sub_dir
			while ((current_dir->read_dir = readdir(current_dir->open_dir)))
			{
				if ((!ft_strncmp(".", current_dir->read_dir->d_name, 1) || !ft_strncmp("..", current_dir->read_dir->d_name, 2)) && opt.hidded == false)
					continue;
				add_new_directory(sub_dir, new_directory(current_dir->read_dir->d_name, current_dir->full_path));
			}

			print_dir_content(sub_dir);
			(opt.recursive) ? directory_processor(sub_dir, RECURSIVE) : 0;
		}
		free_dir_list(sub_dir);
		sub_dir = new_directory(NULL, NULL);
		current_dir = opt.reverse ? current_dir->prev : current_dir->next;
	}
	free_dir_list(sub_dir);
}