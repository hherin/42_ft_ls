#include "../inc/ft_ls.h"

int alpha_sorted(fileInfo *new, fileInfo *tmp)
{
	if (ft_strncmp(tmp->name, new->name, ft_strlen(tmp->name) + 1) < 0)
		return 1;
	return 0;
}

int date_sorted(fileInfo *new, fileInfo *tmp)
{
	struct timespec t1 = tmp->sinfo.st_mtimespec;
	struct timespec t2 = new->sinfo.st_mtimespec;
	if (t1.tv_sec > t2.tv_sec || (t1.tv_sec == t2.tv_sec && t1.tv_nsec > t2.tv_nsec))
		return 1;
	return 0;
}

int parse_a_sorted(fileInfo *new, fileInfo *tmp)
{
	bool is_new_dir = new->is_dir;
	bool is_tmp_dir = tmp->is_dir;

	if (new->name[0] == '.') {
		if (tmp->name[0] == '.' && ft_strncmp(tmp->name, new->name, ft_strlen(tmp->name) + 1) < 0)
			return 1;
	}
	else { 
		if (tmp->name[0] == '.')
			return 1;
		if (!is_new_dir && !is_tmp_dir && ft_strncmp(tmp->name, new->name, ft_strlen(tmp->name) + 1) < 0)
			return 1;
		if (is_new_dir && !is_tmp_dir)
			return 1;
		if (is_new_dir && is_tmp_dir && ft_strncmp(tmp->name, new->name, ft_strlen(tmp->name) + 1) < 0)
			return 1;
	}
	return 0;
}

int parse_d_sorted(fileInfo *new, fileInfo *tmp)
{
	bool is_new_dir = new->is_dir;
	bool is_tmp_dir = tmp->is_dir;

	if (new->name[0] == '.') {
		if (tmp->name[0] == '.' && date_sorted(tmp, new) > 0)
			return 1;
	}
	else { 
		if (tmp->name[0] == '.')
			return 1;
		if (!is_new_dir && !is_tmp_dir && date_sorted(tmp, new) > 0)
			return 1;
		if (is_new_dir && !is_tmp_dir)
			return 1;
		if (is_new_dir && is_tmp_dir && date_sorted(tmp, new) > 0)
			return 1;
	}
	return 0;
}
