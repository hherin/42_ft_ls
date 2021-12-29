#include "../inc/ft_ls.h"

fileInfo *create_new_file(char *name, char *file_path)
{
	fileInfo *new = malloc(sizeof(fileInfo));

	ft_bzero(new, sizeof(fileInfo));
	new->name = ft_strdup(name);
	new->fullpath = ft_str_sep_join(file_path, name, "/");
	if (lstat(new->fullpath, &new->sinfo) < 0 && new->name) {
		new->fullpath = NULL;
		return new;
	}
	new->size = 0;
	new->is_dir = (S_IFDIR == (new->sinfo.st_mode & S_IFMT));
	new->next = NULL;
	new->prev = NULL;

	return new;
}

void free_fileinfo(fileInfo *head)
{
	fileInfo *tmp = head->next;

	while (tmp && tmp != head) {
		fileInfo *tmp2 = tmp->next;
		free(tmp->name);
		free(tmp->fullpath);
		free(tmp);
		tmp = tmp2;
	}
	free(head);
}

static void link_file(fileInfo *prev, fileInfo *next, fileInfo *new)
{
	prev->next = new;
	next->prev = new;
	new->prev = prev;
	new->next = next;
}

fileInfo *add_new_file(fileInfo *head, fileInfo *new, bool timesorted, int (*as)(fileInfo*, fileInfo*), int (*ds)(fileInfo*, fileInfo*))
{
	if (!new)
		return NULL;
	head->size++;
	if (!head->next && !head->prev)
		link_file(head, head, new);

	else {
		fileInfo *tmp = head->next;
		while (tmp != head && ((!timesorted && (*as)(new, tmp)) || (timesorted && (*ds)(new, tmp))))
			tmp = tmp->next;
		link_file(tmp->prev, tmp, new);
	}

	return new;
}

int import_curr_repo(char *dir, fileInfo *head, bool timesort, bool showall)
{
	DIR *op = opendir(dir);
	
	if (!op){
		ft_putstr_fd("ls: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": Operation not permitted\n", 2);
		return 0;
	}

	struct dirent *rd;
	while ((rd = readdir(op))){
		if (showall || (!showall && rd->d_name[0] != '.'))
			add_new_file(head, create_new_file(rd->d_name, dir), timesort, &alpha_sorted, &date_sorted);
	}
	closedir(op);
	return 1;
}

void del_fileInfo(fileInfo *f)
{
	fileInfo *next = f->next;
	fileInfo *prev = f->prev;
	next->prev = prev;
	prev->next = next;
	free(f->name);
	free(f->fullpath);
	free(f);
}