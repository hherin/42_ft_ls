#include "../ft_ls.h"

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
	ft_bzero(&opt, sizeof(struct option));
	dir_list = new_directory("./", NULL);			// case no path is given

	size_t i = 0;
	while (av[i]) {
		while (default_path && av[i][0] == '-')
			add_option(&av[i++][1]);

		add_new_directory(dir_list, new_directory(av[i], NULL));
		i++;
	}	
}