#include "../../inc/ft_ls.h"

fileInfo *deleteElement(fileInfo *elem)
{
  fileInfo *ret = elem->next;
  elem->next->prev = elem->prev;
  elem->prev->next = ret; 
  free(elem->filename);
  free(elem->fullpath);
  free(elem);
  return ret;
}

void free_fileInfo_list(fileInfo *head)
{
  fileInfo *tmp = head->next;
  while (tmp != head) {
    tmp = deleteElement(tmp);
  }
  free(head);
}

fileInfo *create_root_list(void)
{
  fileInfo *new;

  if (!(new = malloc(sizeof(fileInfo)))) {
    my_fd_printf(2, "ERROR MALLOC LIST\n");
    exit(1);
  }

  new->prev = new; 
  new->next = new;
  return new;
}

fileInfo *create_element(char *filename, char *parent)
{
  fileInfo *new;

  if (!(new = malloc(sizeof(fileInfo)))) {
    // free the list
    my_fd_printf(2, "ERROR MALLOC LIST\n");
    exit(1);
  }
  new->filename = ft_strdup(filename);

  if (parent[0]){
    new->fullpath = ft_str_sep_join(parent, new->filename, "/");
  } else {
    new->fullpath =ft_strdup(filename);
  }

  if (lstat(new->fullpath, &new->statp) < 0) {
    my_fd_printf(2, "FILE DONT EXIST %s\n", new->fullpath);
    deleteElement(new);
    return NULL;
  }
  new->is_dir = (S_ISDIR(new->statp.st_mode)) ? true : false;
  new->next = NULL;
  new->prev = NULL;
  return new;
}

void fileInfo_add_front(fileInfo *elem, fileInfo *new)
{
  if (!new)
    return;
  fileInfo *tmp = elem->prev;
  elem->prev = new;
  new->prev = tmp;
  tmp->next = new;
  new->next = elem;
}

int size_list(fileInfo *head)
{
  fileInfo *tmp = head->next;
  int i = 0;
  while (tmp != head) {
    i++;
    tmp = tmp->next;
  }
  return i;
}



// int main(void)
// {
//   fileInfo *head = create_root_list();
//   fileInfo *src = create_element("../src", "");
//   fileInfo *aa = create_element("../aa", "");
//   fileInfo *inc = create_element("../inc", "");
//   fileInfo *sort = create_element("sort.c", "");
//   add_file_into_dir(head, src, datecmp);
//   add_file_into_dir(head, inc, datecmp);
//   add_file_into_dir(head, aa, datecmp);
//   add_file_into_dir(head, sort, datecmp);


//   print_list(head);

//   deleteElement(aa);

//   print_list(head);

//   deleteElement(src);

//   print_list(head);

//   deleteElement(inc);

//   print_list(head);

//   deleteElement(sort);

//   print_list(head);

//   struct stat buf;

//   lstat("main.c", &buf);

//   my_fd_printf(1, "test1 %d\n", (S_IFDIR == (buf.st_mode & S_IFMT)));
//   my_fd_printf(1, "test2 %d\n", buf.st_mode & S_IFDIR);
//   my_fd_printf(1, "test3 %d\n", S_ISDIR(buf.st_mode));
// }