#include "../ft_ls.h"

// Doesnt check if not good option
void add_option(const char *av)
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

void commande_parsing(char **av)
{
	ft_bzero(&opt, sizeof(struct option));
	files = new_file("./");			// case no path is given

	size_t i = 0;
	while (av[i]) {
		if (file_list_empty() && av[i][0] == '-')
			add_option(&av[i][1]);
		else if (av[i][0] != '-') 
			add_new_file(new_file(av[i]));
		else
			err_exit_msg("wrong output\n");
		i++;
	}
	
}