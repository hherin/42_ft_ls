#include "../inc/ft_ls.h"

void print_long_format(const fileInfo *file)
{
	struct passwd *user;
	struct group *gp;
	char *time;

	if (!(user = getpwuid(file->sinfo.st_uid)))
		; //err_exit_msg("error from user \n");
	if (!(gp = getgrgid(file->sinfo.st_gid)))
		;//err_exit_msg("error from gp \n");
	time = ctime(&file->sinfo.st_mtime);

	ft_printf("%2.u %s %s %6.d", (unsigned int)file->sinfo.st_nlink, user->pw_name, gp->gr_name, (long)file->sinfo.st_size);
	ft_printf(" %.3s %.2s ", time + 4, time + 8);
	time += 8;
	while (!ft_isdigit(*time))
		time++;
	while (ft_isdigit(*time))
		time++;
	ft_printf("%.5s ", time + 1);
	file->is_dir ? ft_printf("\033[1;36m%s\033[0m", file->name) : ft_printf("%s", file->name);
	if (S_IFLNK == (file->sinfo.st_mode & S_IFMT)) {
        char lpath[256];
        ft_bzero(lpath, 256);
		ft_printf(" -> %s", lpath);
    }
	ft_printf("\n");
}

void display_file(fileInfo *f, bool longf)
{
    if (longf)
			print_long_format(f);
    else
		ft_printf("%s\n", f->name);
        // S_IFDIR == (f->sinfo.st_mode & S_IFMT) ? ft_printf("\033[1;36m%s\033[0m\n", f->name) : ft_printf("%s\n", f->name);
}

void display_list_content(fileInfo *head, bool rev, bool longf)
{
	fileInfo *tmp = rev ? head->prev : head->next;

	while (tmp && tmp != head){
		fileInfo *del = tmp;
		display_file(tmp, longf);
        tmp = rev ? tmp->prev : tmp->next;
		if (!del->is_dir)
			del_fileInfo(del);
    }
}

