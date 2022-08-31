#include "../inc/ft_ls.h"

char **get_options(char **av, bool options[5], Sortfcn *func)
{
  while ((*av) && (*av)[0] == '-' && ft_strlen(*av) > 1) {
    int i = 0;
    while ((*av)[++i]) {
      switch ((*av)[i]) {
        case 'a':
          options[SHOW_HIDDEN] = true;
          continue;
        case 'l':
          options[LONG_FORMAT] = true;
          continue;
        case 'r':
          options[REVERSE] = true;
          continue;
        case 't':
          options[BY_MODIF_TIME] = true;
          continue;
        case 'R':
          options[RECURSIVE] = true;
          continue;
        default:
          my_fd_printf(1, "ERROR OPTION\n");
          exit(1);
      }
    }
    av++;
  }
  
  if (options[REVERSE]) {
    if (options[BY_MODIF_TIME]) {
      *func = &revdatecmp;
    }
    else {
      *func = &revnamecmp;
    }
  }
  else {
    if (options[BY_MODIF_TIME]) {
      *func = &datecmp;
    }
    else {
      *func = &namecmp;
    }
  }
  return av;
}
