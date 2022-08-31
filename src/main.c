#include "../inc/ft_ls.h"
#include <stdio.h>

fileInfo *main_list = NULL, *sub_list = NULL;

int main(int ac, char **av)
{
  fileInfo *head;
  bool options[5];

  for (int i =0; i < 5; i++)
    options[i] = false;

  head = create_root_list();
  main_list = head;
  Sortfcn sortfcn = &namecmp;

  if (ac > 1) {
    av = get_options(++av, options, &sortfcn);
    while (*av) {
      fileInfo *new = create_element(*av, "");
      parse_argument(head, new, sortfcn);
      av++;
    }
    (head->next == head) ? fileInfo_add_front(head, create_element(".", "")) : 0;
  }
  else {
    fileInfo_add_front(head, create_element(".", ""));
  }

  ls_routine(head, options, sortfcn);
  free_fileInfo_list(head);
  
  return 0;
}