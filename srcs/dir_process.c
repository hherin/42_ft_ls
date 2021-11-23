#include "ft_ls.h"

static int more_than_one_in_list(struct directory *dir)
{
	return (dir && dir->next && dir->next->next && dir->next != dir && dir->next->next != dir) ? 1 : 0;
}

static struct directory *print_current_dir_list(DIR *open_d, const char *full_path)
{
	struct directory *sub_dir = new_directory(NULL, NULL);
	struct dirent *read_d;
	struct stat dbuf;
	stat(full_path, &dbuf);

	while ((read_d = readdir(open_d)))
	{
		if ((!ft_strncmp(".", read_d->d_name, 1) || !ft_strncmp("..", read_d->d_name, 2)) && opt.hidded == false)
			continue;

		if (S_ISDIR(dbuf.st_mode))
			add_new_directory(sub_dir, new_directory(read_d->d_name, full_path));
	}
	if (opt.long_format)
		ft_printf("total %d\n", dir_total_size(sub_dir));
	print_dir_content(sub_dir);

	return sub_dir;
}

void directory_processor(struct directory *head, int rec_state)
{
	struct directory *curdir = NEXT_DIR(opt.reverse, head->prev, head->next);
	struct directory *newdir = NULL;

	while (curdir && curdir != head)
	{
		DIR *open_d = opendir(curdir->full_path);

		if (!rec_state && *curdir->lpath) {
			if (opt.long_format){
				print_long_format(curdir);
				ft_putchar_fd('\n', 1);
			}
			else {
				if (more_than_one_in_list(head))
					ft_printf("%s: \n", curdir->full_path);
				free_dir_list(print_current_dir_list(open_d, curdir->full_path));
			}
		}
		// if inside recursive and (not a directory or curdir == '.' or '..')
		else if (rec_state && (*curdir->lpath || !open_d || !ft_strncmp(".", curdir->name, 2) || !ft_strncmp("..", curdir->name, 3)))
			;
		else if (!open_d && !rec_state)
			print_not_found_dir(curdir->name);
		else
		{
			if ((!rec_state && more_than_one_in_list(head)) || rec_state)
				ft_printf("%s: \n", curdir->full_path);

			// loop that store content of the curdir in newdir and print it
			newdir = print_current_dir_list(open_d, curdir->full_path);

			if (opt.recursive) 
				directory_processor(newdir, RECURSIVE);
		}

		if (open_d) 
			closedir(open_d);

		free_dir_list(newdir);
		newdir = new_directory(NULL, NULL);
		curdir = NEXT_DIR(opt.reverse, curdir->prev, curdir->next);
	}
	free_dir_list(newdir);
}