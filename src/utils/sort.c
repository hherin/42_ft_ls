#include "../../inc/ft_ls.h"

// COMPARISON
// a - b < 0
// a - b > 0 
// a - b = 0


int namecmp(fileInfo *a, fileInfo *b)
{
  return ft_strncmp(a->filename, b->filename, ft_strlen(a->filename));
}

int revnamecmp(fileInfo *a, fileInfo *b)
{
  return ft_strncmp(b->filename, a->filename, ft_strlen(b->filename));
}


int datecmp(fileInfo *a, fileInfo *b)
{
  long sec_diff = a->statp.st_mtimespec.tv_sec - b->statp.st_mtimespec.tv_sec;
  long nsec_diff = a->statp.st_mtimespec.tv_nsec - b->statp.st_mtimespec.tv_nsec;
  if (sec_diff > 0|| (!sec_diff && nsec_diff > 0))
    return -1;
  else if (!sec_diff && !nsec_diff)
    return 0;
  else
    return 1;
}

int revdatecmp(fileInfo *a, fileInfo *b)
{
  return datecmp(b, a);
}

void add_file_into_dir(fileInfo *head, fileInfo *new, int (*sortfcn)(fileInfo*, fileInfo*))
{
  if (!new)
    return;
  if (head->next == head){
    return fileInfo_add_front(head, new);
  }
  fileInfo *tmp = head->next;
  while (tmp != head && (*sortfcn)(new, tmp) > 0){
    tmp = tmp->next;
  }

  fileInfo_add_front(tmp, new);
}
