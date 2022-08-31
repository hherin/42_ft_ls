#include "../../inc/ft_ls.h"

// COMPARISON
// a - b < 0
// a - b > 0 
// a - b = 0

char *strdup_tolower(char *name)
{
  size_t size = ft_strlen(name);
  char *lower_name = malloc(sizeof(char) * (size + 1));
  for (size_t i = 0; name[i]; i++) {
    lower_name[i] = ft_tolower(name[i]);
  }
  lower_name[size] = '\0';
  return lower_name;
}

int namecmp(fileInfo *a, fileInfo *b)
{
  char *name_a = strdup_tolower(a->filename);
  char *name_b = strdup_tolower(b->filename);
  return ft_strncmp(name_a, name_b, ft_strlen(name_a));
  free(name_a);
  free(name_b);
}

int revnamecmp(fileInfo *a, fileInfo *b)
{
  char *name_a = strdup_tolower(a->filename);
  char *name_b = strdup_tolower(b->filename);
  return ft_strncmp(name_b, name_a, ft_strlen(b->filename));
  free(name_a);
  free(name_b);
}


int datecmp(fileInfo *a, fileInfo *b)
{
  long diff = a->statp.st_mtime - b->statp.st_mtime;
  if (diff > 0)
    return -1;
  else if (!diff)
    return 0;
  else
    return 1;
  // long sec_diff = a->statp.st_mtimespec.tv_sec - b->statp.st_mtimespec.tv_sec;
  // long nsec_diff = a->statp.st_mtimespec.tv_nsec - b->statp.st_mtimespec.tv_nsec;
  // if (sec_diff > 0|| (!sec_diff && nsec_diff > 0))
  //   return -1;
  // else if (!sec_diff && !nsec_diff)
  //   return 0;
  // else
  //   return 1;
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
