#ifndef FT_LS__H
# define FT_LS__H

# include <dirent.h>
# include <sys/stat.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h> 
# include <pwd.h>
# include <grp.h>
# include <time.h>

# include "../lib/inc/libft.h"
# include "../lib/inc/ft.h"

#define REC 1
#define SHOWALL option[(int)'a']
#define LFORM option[(int)'l']
#define REVERSE option[(int)'r']
#define TIME option[(int)'t']
#define RECURS option[(int)'R']

typedef struct fileInfo
{
    char *name;
    char *fullpath;
    struct stat sinfo;
    bool is_dir;
    int size;
	struct fileInfo *next;
	struct fileInfo *prev;
}       fileInfo;


void display_list_content(fileInfo *head, bool rev, bool longf);
void display_file(fileInfo *f, bool longf, size_t max[4]);
fileInfo *parse_cmd(int ac, char **av, bool option[256]);
fileInfo *create_new_file(char *name, char *file_path);
fileInfo *add_new_file(fileInfo *head, fileInfo *new, bool timesorted, int (*as)(fileInfo*, fileInfo*), int (*ds)(fileInfo*, fileInfo*));
void free_fileinfo(fileInfo *head);


#endif