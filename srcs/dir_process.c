#include "ft_ls.h"

static int more_than_one_in_list(struct directory *dir)
{
	return (dir && dir->next && dir->next->next && dir->next != dir && dir->next->next != dir) ? 1 : 0;
}

static struct directory *print_current_dir_list(dir_info info, const char *full_path)
{
	struct directory *sub_dir = new_directory(NULL, NULL);

	while ((info.read_d = readdir(info.open_d)))
	{
		if ((!ft_strncmp(".", info.read_d->d_name, 1) || !ft_strncmp("..", info.read_d->d_name, 2)) && opt.hidded == false)
			continue;

		if (S_ISDIR(info.dbuf.st_mode) && !S_ISLNK(info.lbuf.st_mode))
			add_new_directory(sub_dir, new_directory(info.read_d->d_name, full_path));
	}

	print_dir_content(sub_dir);

	return sub_dir;
}

void directory_processor(struct directory *head, int rec_state)
{
	struct directory *curdir = NEXT_DIR(opt.reverse, head->prev, head->next);
	struct directory *newdir = NULL;

	while (curdir && curdir != head)
	{
		dir_info info;
		stat(curdir->full_path, &info.dbuf);
		lstat(curdir->full_path, &info.lbuf);
		info.open_d = opendir(curdir->full_path);

		if (!readlink(curdir->full_path, NULL, 0)) {
			if (!rec_state && opt.long_format) 
				print_long_format(curdir);
		}
		// if inside recursive and (not a directory or curdir == '.' or '..')
		else if (rec_state && (!info.open_d || !ft_strncmp(".", curdir->name, 2) || !ft_strncmp("..", curdir->name, 3)))
			;
		else if (!info.open_d && !rec_state)
			print_not_found_dir(curdir->name);
		else
		{
			if ((!rec_state && more_than_one_in_list(head)) || rec_state)
				ft_printf("%s: \n", curdir->full_path);

			if (opt.long_format)
				ft_printf("total %d\n", curdir->buf.st_blksize / 512);

			// loop that store content of the directory in newdir and print
			newdir = print_current_dir_list(info, curdir->full_path);

			if (opt.recursive) 
				directory_processor(newdir, RECURSIVE);
		}

		(info.open_d) ? closedir(info.open_d) : 0;
		free_dir_list(newdir);
		newdir = new_directory(NULL, NULL);
		curdir = NEXT_DIR(opt.reverse, curdir->prev, curdir->next);
	}
	free_dir_list(newdir);
}