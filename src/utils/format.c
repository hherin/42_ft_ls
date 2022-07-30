#include "../../inc/ft_ls.h"

static int digit_size(int d)
{
	int i = 0;
	while (d && ++i) 
		d /= 10;
	return i;
}

void set_max_field(const fileInfo *head, int max[4])
{
	ft_bzero(max, sizeof(int) * 4);
  for (fileInfo *tmp = head->next; tmp != head; tmp = tmp->next) {

		int nlink = digit_size(tmp->statp.st_nlink);
		(nlink > max[0]) ? max[0] = nlink : 0;

		int user = ft_strlen(getpwuid(tmp->statp.st_uid)->pw_name);
		(user > max[1]) ? max[1] = user : 0;

		int grp = ft_strlen(getgrgid(tmp->statp.st_gid)->gr_name);
		(grp > max[2]) ? max[2] = grp : 0;

		int size = digit_size(tmp->statp.st_size);
		(size > max[3]) ? max[3] = size : 0;
	}
}

void set_max_files(const fileInfo *head, int max[4]) 
{
	fileInfo *tmp = head->next;

	ft_bzero(max, sizeof(int) * 4);
	while (tmp && tmp != head && !tmp->is_dir) {
		int nlink = digit_size(tmp->statp.st_nlink);
		int user = ft_strlen(getpwuid(tmp->statp.st_uid)->pw_name);
		int grp = ft_strlen(getgrgid(tmp->statp.st_gid)->gr_name);
		int size = digit_size(tmp->statp.st_size);
		(nlink > max[0]) ? max[0] = nlink : 0;
		(user > max[1]) ? max[1] = user : 0;
		(grp > max[2]) ? max[2] = grp : 0;
		(size > max[3]) ? max[3] = size : 0;
		tmp = tmp->next;
	}
}