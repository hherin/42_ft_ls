#include "../inc/ft_ls.h"

void set_max_field(const fileInfo *head, size_t max[4]);
int dir_total_size(fileInfo *head);
void del_fileInfo(fileInfo *f);

void display_name(fileInfo *f, bool rec, int size, int recindex)
{
	if (rec || (!rec && recindex > 0))
		ft_printf("\n");
	if (!rec && size > 1)
		ft_printf("%s:\n", f->name);
	else if (rec)
		ft_printf("%s:\n", f->fullpath);
}

void print_long_format(const fileInfo *file, size_t max[4])
{
	char time[13];
	char lpath[128];

	time[12] ='\0';
	ft_bzero(lpath, 128);
	ft_strlcpy(time, ctime(&file->sinfo.st_mtime) + 4, 12);

	if (S_IFLNK == (file->sinfo.st_mode & S_IFMT))
		readlink(file->fullpath, lpath, 128);
	char *linkpath;
	linkpath = (*lpath) ? ft_str_sep_join("-> ", lpath, "") : ft_strdup("");
	ft_printf("%*.u %*s %*s %*d %s %s %s\n", \
	max[0], (unsigned int)file->sinfo.st_nlink, \
	max[1], getpwuid(file->sinfo.st_uid)->pw_name, \
	max[2], getgrgid(file->sinfo.st_gid)->gr_name, \
	max[3], (long)file->sinfo.st_size, \
	time, file->name, linkpath);
	free(linkpath);
}

void display_file(fileInfo *f, bool longf, size_t max[4])
{
    if (longf)
		print_long_format(f, max);
    else
        ft_printf("%s\n", f->name);
}

/*
**	print each element of a directory and delete all files in fileInfo head
**	for the next call of rec_file_process in case option R
**
*/
void display_list_content(fileInfo *head, bool rev, bool longf)
{
	fileInfo *tmp = rev ? head->prev : head->next;
	size_t max[4];

	if (longf) {
		set_max_field(head, max);
		ft_printf("total %d\n", dir_total_size(head));
	}
	while (tmp && tmp != head) {
		fileInfo *del = tmp;
		display_file(tmp, longf, max);
        tmp = rev ? tmp->prev : tmp->next;
		if (!del->is_dir)
			del_fileInfo(del);
    }
}

