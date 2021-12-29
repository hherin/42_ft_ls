#include "../inc/ft_ls.h"

int main(int ac, char **av)
{
	fileInfo *head = NULL;
	bool option[256];

	ft_bzero(option, 256);
	head = parse_cmd(ac, av, option);
	rec_file_process(head, option, !REC);
	free_fileinfo(head);
	
	return 0;
}
