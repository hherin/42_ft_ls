#include "../inc/ft_ls.h"

void display_repo_name(fileInfo *f, bool rec, int size, int recindex)
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
	ft_printf("%*.u %-*s %-*s %*d %s %s %s\n", \
	max[0], (unsigned int)file->sinfo.st_nlink, \
	max[1], getpwuid(file->sinfo.st_uid)->pw_name, \
	max[2], getgrgid(file->sinfo.st_gid)->gr_name, \
	max[3], (long)file->sinfo.st_size, \
	time, file->name, linkpath);
	free(linkpath);
}

void display_file(fileInfo *f, bool longf, size_t max[4], fileInfo *head)
{
	static int idx_cols = 0;

	if (longf)
		print_long_format(f, max);
	else {
		if (max[1] < idx_cols * max[0]) {
			ft_printf("\n");
			idx_cols = 0;
		}
		ft_printf("%-*s",max[0], f->name);
		idx_cols++;
	}
	if (f->next == head)
		ft_printf("\n");
}

int get_term_cols(void)
{
	struct winsize ws;
	int fd;

	/* open controlling terminal*/
	if ((fd = open("/dev/tty", O_RDWR)) < 0) {
		write(2, "fail to open /dev/tty", ft_strlen("fail to open /dev/tty"));
		exit(1);
	}

	if (ioctl(fd, TIOCGWINSZ, &ws) < 0) {
		write(2, "fail to ioctl", ft_strlen("fail to ioctl"));
		exit(1);
	}
	close(fd);
	return (ws.ws_col);
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
	else {
		ft_bzero(max, sizeof(size_t) * 4);
		max[0] = get_max_strlen(head) + 1;
		max[1] = (size_t)get_term_cols();
	}
	while (tmp && tmp != head) {
		fileInfo *del = tmp;
		display_file(tmp, longf, max, head);
		tmp = rev ? tmp->prev : tmp->next;
		if (!del->is_dir)
			del_fileInfo(del);
	}
}

