#include "../inc/ft_ls.h"

char **get_options(char **av, bool options[5], int (*sortfcn)(fileInfo *, fileInfo*))
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
          printf("ERROR OPTION\n");
          exit(1);
      }
    }
    av++;
  }
  
  if (options[REVERSE]) {
    if (options[BY_MODIF_TIME]) {
      sortfcn = &revdatecmp;
    }
    else {
      sortfcn = &revnamecmp;
    }
  }
  else {
    if (options[BY_MODIF_TIME]) {
      sortfcn = &datecmp;
    }
    else {
      sortfcn = &namecmp;
    }
  }
  return av;
}
