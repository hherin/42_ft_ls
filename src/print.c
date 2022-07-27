#include "../inc/ft_ls.h"

fileInfo *deleteElement(fileInfo *elem);


void print_list(fileInfo *head)
{
  fileInfo *tmp = head->next;
  while (tmp != head) {
    printf("%s\n", tmp->filename);
    if (!tmp->is_dir || !ft_strncmp(".", tmp->filename, 2) || !ft_strncmp("..", tmp->filename, 3)) {
      tmp = deleteElement(tmp);
    }
    else {
      tmp = tmp->next;
    }
  }
    printf("\n");
}