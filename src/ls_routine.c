#include "../inc/ft_ls.h"

void parse_argument(fileInfo *head, fileInfo *new, int (*sortfcn)(fileInfo*, fileInfo*))
{
  if (!new)
    return;

  if (head->next == head){
    return fileInfo_add_front(head, new);
  }

  fileInfo *tmp = head->next;
  while (tmp != head && !tmp->is_dir) {
    if (!new->is_dir && (*sortfcn)(new, tmp) < 0)
      break;
    tmp = tmp->next;
  }
  while (tmp != head && new->is_dir && (*sortfcn)(new, tmp) > 0)
    tmp = tmp->next;

  fileInfo_add_front(tmp, new);
}

void add_dir_content(fileInfo *currentdir, fileInfo *dirContent, bool options[5], bool in_rec_mode, int (*sortfcn)(fileInfo *, fileInfo*))
{
  DIR *opend;
  if ((opend = opendir(currentdir->fullpath)) == NULL) {
    printf("%s\n", currentdir->fullpath);
  }
  else {
    struct dirent *rdir;
    while((rdir = readdir(opend))) {
      fileInfo *new = create_element(rdir->d_name, currentdir->fullpath);

      if ((!ft_strncmp(".", rdir->d_name, 1) && options[SHOW_HIDDEN]) || ft_strncmp(".", rdir->d_name, 1)) {
        add_file_into_dir(dirContent, new, sortfcn);
      }
    }

    if ((!in_rec_mode && currentdir->next != currentdir->prev) || in_rec_mode)
        printf("%s:\n", currentdir->fullpath);
    print_list(dirContent);

  }
}

void ls_routine(fileInfo *currentDir, bool options[5], int (*sortfcn)(fileInfo *, fileInfo *), bool in_rec_mode)
{
  if (currentDir->next == currentDir)
    return;
  fileInfo *tmp = currentDir->next;
  
  while (tmp != currentDir) {
    fileInfo *dirContent = create_root_list();
    add_dir_content(tmp, dirContent, options, in_rec_mode, sortfcn);

    if (options[RECURSIVE]){
      ls_routine(dirContent, options, sortfcn, true);
    }

    free_fileInfo_list(dirContent);
    tmp = tmp->next;
  }
}