#include "../inc/ft_ls.h"

fileInfo *deleteElement(fileInfo *elem);

void print_long_format(const fileInfo *file, int max[4])
{
	char time[13];
	char lpath[128];

	time[12] ='\0';
	ft_bzero(lpath, 128);
	ft_strlcpy(time, ctime(&file->statp.st_mtime) + 4, 12);

	if (S_IFLNK == (file->statp.st_mode & S_IFMT))
		readlink(file->fullpath, lpath, 128);
	char *linkpath;
	linkpath = (*lpath) ? ft_str_sep_join("-> ", lpath, "") : ft_strdup("");

	my_fd_printf(1, "%*u %-*s %-*s %*ld %s %s %s\n", \
	  max[0], (unsigned int)file->statp.st_nlink, \
	  max[1], getpwuid(file->statp.st_uid)->pw_name, \
	  max[2], getgrgid(file->statp.st_gid)->gr_name, \
	  max[3], (long)file->statp.st_size, \
	  time, 
    file->filename, 
    linkpath);
	
  free(linkpath);
}


void print_list(fileInfo *head, bool options[5])
{
  fileInfo *tmp = head->next;
  int max[4];

  if (options[LONG_FORMAT])
    set_max_field(head, max);

  while (tmp != head) {
    
    if (options[LONG_FORMAT]) {
      print_long_format(tmp, max);
    } else {
      my_fd_printf(1, "%s\n", tmp->filename);
    }

    if (!tmp->is_dir || !ft_strncmp(".", tmp->filename, 2) || !ft_strncmp("..", tmp->filename, 3)) {
      tmp = deleteElement(tmp);
    } else {
      tmp = tmp->next;
    }
  }

  my_fd_printf(1, "\n");
}