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

void add_dir_content(fileInfo *currentdir, fileInfo *dirContent, bool options[5], int (*sortfcn)(fileInfo *, fileInfo*))
{
  DIR *opend;
  if ((opend = opendir(currentdir->fullpath)) == NULL) {
    my_fd_printf(1, "%s\n", currentdir->fullpath);
  }
  else {
    struct dirent *rdir;
    while((rdir = readdir(opend))) {

      if ((!ft_strncmp(".", rdir->d_name, 1) && options[SHOW_HIDDEN]) || ft_strncmp(".", rdir->d_name, 1)) {
        fileInfo *new = create_element(rdir->d_name, currentdir->fullpath);
        add_file_into_dir(dirContent, new, sortfcn);
      }
    }

    if ((!options[RECURSIVE] && currentdir->next != currentdir->prev) || options[RECURSIVE])
        my_fd_printf(1, "%s:\n", currentdir->fullpath);
    print_list(dirContent, options);

    closedir(opend);
  }
}

void ls_routine(fileInfo *currentDir, bool options[5], int (*sortfcn)(fileInfo *, fileInfo *))
{
  if (currentDir->next == currentDir)
    return;
  fileInfo *tmp = currentDir->next;
  
  while (tmp != currentDir) {
    fileInfo *dirContent = create_root_list();
    sub_list = dirContent;
    add_dir_content(tmp, dirContent, options, sortfcn);

    if (options[RECURSIVE]){
      ls_routine(dirContent, options, sortfcn);
    }

    free_fileInfo_list(dirContent);
    tmp = tmp->next;
  }
}