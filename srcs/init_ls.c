#include "ft_ls.h"

static bool is_option_valid(const char *option, const char *buf)
{
	size_t i = 0;
	while (option[i]) {
		size_t j = 0;
		while (buf[j] && buf[j] != option[i])
			j++;
		if (j == ft_strlen(buf))
			return false;
		i++;
	}
	return true;
}

static void add_option(const char *av)
{
	if (!is_option_valid(av + 1, "Ralrt"))
		err_exit_msg("ls: illegal option\nusage: ./ft_ls [-Ralrt] [file ...]\n");
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
		add_option(av[j++]);
	i = j;
	while (av[j])
		add_new_directory(dir_list, new_directory(av[j++], NULL));

	if (!dir_list->next)
		add_new_directory(dir_list, new_directory(".", NULL));
}