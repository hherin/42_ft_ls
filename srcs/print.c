#include "../ft_ls.h"

// change fd
void colored_name(const char *name)
{
	ft_putstr_fd("\033[1;36m", 1);
	ft_putstr_fd((char*)name, 1);
	ft_putstr_fd("\033[0m\n", 1);
}

static void print_long_format(struct directory *dir)
{
	struct passwd *user;
	struct group *gp;
	char *time;

	if (!(user = getpwuid(dir->buf.st_uid)))
		err_exit_msg("error from user \n");
	if (!(gp = getgrgid(dir->buf.st_gid)))
		err_exit_msg("error from gp \n");
	time = ctime(&dir->buf.st_mtime);

	ft_printf("%2.u %s %s %6.d", (unsigned int)dir->buf.st_nlink, user->pw_name, gp->gr_name, (long)dir->buf.st_size);
	ft_printf(" %.3s %.2s ", time + 4, time + 8);
	time += 8;
	while (!ft_isdigit(*time))
		time++;
	while(ft_isdigit(*time))
		time++;
	ft_printf("%.5s ", time + 1);
	S_ISDIR(dir->buf.st_mode) ? colored_name(dir->name) :  ft_printf("%s\n", dir->name);
}

void print_dir_content(struct directory *head)
{
	struct directory *tmp = opt.reverse ? head->prev : head->next;

	while (tmp && tmp != head)
	{
		if (opt.long_format)
			print_long_format(tmp);
		else
			S_ISDIR(tmp->buf.st_mode) ? colored_name(tmp->name) : ft_printf("%s\n", tmp->name);
		tmp = opt.reverse ? tmp->prev : tmp->next;
	}
	ft_putchar_fd('\n', 1); 
}


void print_not_found_dir(char *name)
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(name, 2);
	perror(": ");
}

