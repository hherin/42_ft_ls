#include "../inc/ft_ls.h"

int main(int ac, char **av)
{
	fileInfo *head = NULL;
	bool option[256];

	ft_bzero(option, 256);
	head = parse_cmd(ac, av, option);

	rec_file_process(head, option, !REC);

	free_fileinfo(head);
	// printf("R %d | r %d | l %d | a %d | t %d\n", option['R'], option['r'], option['l'], option['a'], option['t']);

	// printf("index %d\n", idx);
	return 0;
}
