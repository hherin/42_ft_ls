#include <dirent.h>
#include <stdio.h>
#include "ft_ls.h"

struct option opt; //*opt;
struct file_info *files;

void err_exit_msg(const char *msg)
{
	ft_putstr_fd((char*)msg, 2);
	exit(1);
}

void print_struct(void)
{
	struct file_info *tmp = files->prev;

	printf("PATHS : ");
	while (tmp && tmp != files)
	{
		printf("%s ", tmp->name);
		tmp = tmp->prev;
	}
	printf("\nOPTION\n");

	printf("format %d\nrecursive %d\nhid %d\nrev %d\nmodif %d\n", \
		opt.long_format, opt.recursive, opt.hidded, opt.reverse, opt.modif_order);
}

int main(int ac, char **av)
{
	(void)ac;
	commande_parsing(++av);

	print_struct();
	return 0;
}