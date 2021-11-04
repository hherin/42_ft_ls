#include <dirent.h>
#include <stdio.h>
#include "libft/inc/libft.h"

int main(void)
{
    DIR *dirp = opendir(".");
    if (dirp == NULL)
            return (1);
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL) {
        printf("name %s\n", dp->name);
    }
    (void)closedir(dirp);
    return (0);
}