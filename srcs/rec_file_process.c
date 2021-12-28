#include "../inc/ft_ls.h"

static int fileInfo_size(fileInfo *head)
{
	fileInfo *tmp = head->next;
	int size = 0;

	while (tmp && tmp != head)	{
		size++;
		tmp = tmp->next;
	}
	return size;
}

static void display_name(fileInfo *f, bool rec, int size, int recindex)
{
	if (rec || (!rec && recindex > 0))
		ft_printf("\n");
	if (!rec && size > 1)
		ft_printf("%s:\n", f->name);
	else if (rec)
		ft_printf("%s:\n", f->fullpath);
}

void rec_file_process(fileInfo *head, bool option[256], bool rec)
{
	fileInfo *tmp = (option[(int)'r']) ? head->prev : head->next;
	fileInfo *curr_repo = create_new_file(NULL, NULL);
	static int index = 0;

	while (tmp && tmp != head) {
		if (tmp->is_dir && \
		(!rec || (rec && ft_strncmp(tmp->name, ".", 2) && ft_strncmp(tmp->name, "..", 3)))) {
			display_name(tmp, rec, fileInfo_size(head), index);
			int eacces = import_curr_repo(tmp->fullpath, curr_repo, option[(int)'t'], option[(int)'a']);
			if (eacces) {
				display_list_content(curr_repo, option[(int)'r'], option[(int)'l']);
				if (option[(int)'R'] && curr_repo->size)
					rec_file_process(curr_repo, option, REC);	
			}
			free_fileinfo(curr_repo);
			curr_repo = create_new_file(NULL, NULL);
		}
		else 
			if (!rec)
				display_file(tmp, option[(int)'l']);
		index++;
		tmp = (option[(int)'r']) ? tmp->prev: tmp->next;
	}
	free_fileinfo(curr_repo);
}
