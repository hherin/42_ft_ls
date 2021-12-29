#include "../inc/ft_ls.h"

static void parse_err_msg(fileInfo *new)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(new->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	free(new->name);
	free(new->fullpath);
}

static void err_option_exit(char c)
{
	char str[2];
	str[0] = c;
	str[1] = '\0';
	char *msg = ft_str_sep_join("ls: illegal option -- ", "\nusage: ls [Ralrt] [file ...]\n", str);
	ft_putstr_fd(msg, 2);
	free(msg);
	exit(1);
}

static void add_option(char ***av, bool option[256])
{
	while (**av && (**av)[0] == '-') {
		size_t i = 0;
		while ((**av)[++i]) {
			char c = (**av)[i];
			if (c != 'R' && c != 'r' && c != 'l' && c != 'a' && c != 't')
				err_option_exit(c);
			option[(int)c] = true;
		}
		(*av)++;
	}
}

static void display_unfound(fileInfo *error)
{
	fileInfo *tmp = error->next;

	while (tmp && tmp != error) {
		fileInfo *tmp2 = tmp->next;
		parse_err_msg(tmp);
		free(tmp);
		tmp = tmp2;
	}
	free(error);
}

fileInfo *parse_cmd(int ac, char **av, bool option[256])
{
	fileInfo *head = create_new_file(NULL, NULL);
	fileInfo *error = create_new_file(NULL, NULL);

	av++;
	if (ac > 1 && (*av)[0] == '-')
		add_option(&av, option);
	
	bool timesort = option['t'];
	if (!*av)
		add_new_file(head, create_new_file(".", NULL), timesort, &parse_a_sorted, &parse_d_sorted);

	while (*av) {
		fileInfo *new = create_new_file(*av++, NULL);
		if (!new->fullpath)
			add_new_file(error, new, false, &parse_a_sorted, &parse_d_sorted);
		else
			add_new_file(head, new, timesort, &parse_a_sorted, &parse_d_sorted);
	}
	
	(error->next) ? display_unfound(error) : 0;
	
	return head;
}