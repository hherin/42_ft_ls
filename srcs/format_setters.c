#include "../inc/ft_ls.h"

static size_t digit_size(size_t d)
{
	size_t i = 0;
	while (d && ++i) 
		d /= 10;
	return i;
}

void set_max_field(const fileInfo *head, size_t max[4])
{
	fileInfo *tmp = head->next;

	ft_bzero(max, sizeof(size_t) * 4);
	while (tmp && tmp != head) {
		size_t nlink = digit_size(tmp->sinfo.st_nlink);
		size_t user = ft_strlen(getpwuid(tmp->sinfo.st_uid)->pw_name);
		size_t grp = ft_strlen(getgrgid(tmp->sinfo.st_gid)->gr_name);
		size_t size = digit_size(tmp->sinfo.st_size);
		(nlink > max[0]) ? max[0] = nlink : 0;
		(user > max[1]) ? max[1] = user : 0;
		(grp > max[2]) ? max[2] = grp : 0;
		(size > max[3]) ? max[3] = size : 0;
		tmp = tmp->next;
	}
}

void set_max_files(const fileInfo *head, size_t max[4]) 
{
	fileInfo *tmp = head->next;

	ft_bzero(max, sizeof(size_t) * 4);
	while (tmp && tmp != head && !tmp->is_dir) {
		size_t nlink = digit_size(tmp->sinfo.st_nlink);
		size_t user = ft_strlen(getpwuid(tmp->sinfo.st_uid)->pw_name);
		size_t grp = ft_strlen(getgrgid(tmp->sinfo.st_gid)->gr_name);
		size_t size = digit_size(tmp->sinfo.st_size);
		(nlink > max[0]) ? max[0] = nlink : 0;
		(user > max[1]) ? max[1] = user : 0;
		(grp > max[2]) ? max[2] = grp : 0;
		(size > max[3]) ? max[3] = size : 0;
		tmp = tmp->next;
	}
}