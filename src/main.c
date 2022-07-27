#include "../inc/ft_ls.h"
#include <stdio.h>


int main(int ac, char **av)
{
  fileInfo *head;
  bool options[5];
  int (*sortfcn)(fileInfo *, fileInfo*) = NULL;
  for (int i =0; i < 5; i++)
    options[i] = false;
  head = create_root_list();
  sortfcn = &namecmp;
  (void)ac;(void) av;
  if (ac > 1) {
    av = get_options(++av, options, sortfcn);
    while (*av) {
      parse_argument(head, create_element(*av, ""), sortfcn);
      av++;
    }
    (head->next == head) ? fileInfo_add_front(head, create_element("./", "")) : 0;
  }
  else {
    fileInfo_add_front(head, create_element("./", ""));
  }

  ls_routine(head, options, sortfcn, false);
  free_fileInfo_list(head);
  
  return 0;
}