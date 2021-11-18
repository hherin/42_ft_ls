#include <dirent.h>
#include <stdio.h>
#include "ft_ls.h"

struct option opt;
struct directory *dir_list;
bool default_path = true;

void print_struct(struct directory *head);

int main(int ac, char **av)
{
	(void)ac;

	init_ls(++av);

	directory_processor(dir_list, ROOT);

	return 0;
}