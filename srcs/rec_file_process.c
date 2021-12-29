#include "../inc/ft_ls.h"

void rec_file_process(fileInfo *head, bool option[256], bool rec)
{
	fileInfo *tmp = (REVERSE) ? head->prev : head->next;
	fileInfo *curr_repo = create_new_file(NULL, NULL);
	static int index = 0;

	while (tmp && tmp != head) {
		if (tmp->is_dir && \
		(!rec || (rec && ft_strncmp(tmp->name, ".", 2) && ft_strncmp(tmp->name, "..", 3)))) {
			display_repo_name(tmp, rec, fileInfo_size(head), index);
			int eacces = import_curr_repo(tmp->fullpath, curr_repo, TIME, SHOWALL);
			if (eacces) {
				display_list_content(curr_repo, REVERSE, LFORM);
				if (RECURS && curr_repo->size)
					rec_file_process(curr_repo, option, REC);
			}
			free_fileinfo(curr_repo);
			curr_repo = create_new_file(NULL, NULL);
		}
		else 
			if (!rec){
				size_t max[4];
				set_max_files(head, max);
				display_file(tmp, LFORM, max);
			}
		index++;
		tmp = (REVERSE) ? tmp->prev: tmp->next;
	}
	free_fileinfo(curr_repo);
}
