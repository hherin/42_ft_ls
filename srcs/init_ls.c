#include "ft_ls.h"

// Doesnt check if not good option
static void add_option(const char *av)
{
	if (ft_strchr(av, 'R'))
		opt.recursive = true;
	if (ft_strchr(av, 'a'))
		opt.hidded = true;
	if (ft_strchr(av, 'l'))
		opt.long_format = true;
	if (ft_strchr(av, 'r'))
		opt.reverse = true;
	if (ft_strchr(av, 't'))
		opt.modif_order = true;
}

void init_ls(char **av)
{
	dir_list = new_directory(NULL, NULL);
	size_t i = 0, j = 0;

	ft_bzero(&opt, sizeof(struct option));
	while (av[j] && default_path && av[j][0] == '-')
		add_option(&av[j++][1]);
	i = j;
	while (av[i])
		add_new_directory(dir_list, new_directory(av[i++], NULL));

	if (!dir_list->next)
		add_new_directory(dir_list, new_directory(".", NULL));
}