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

void rec_file_process(fileInfo *head, bool option[256], bool recstate);


/* ================================= */
void display_list_content(fileInfo *head, bool rev, bool longf);
void display_file(fileInfo *f, bool longf);


/* ================================= */
fileInfo *parse_cmd(int ac, char **av, bool option[256]);


/* ================================= */
int alpha_sorted(fileInfo *new, fileInfo *tmp);
int date_sorted(fileInfo *new, fileInfo *tmp);
int parse_a_sorted(fileInfo *new, fileInfo *tmp);
int parse_d_sorted(fileInfo *new, fileInfo *tmp);

/* ================================= */
int import_curr_repo(char *dir, fileInfo *head, bool timesort, bool showall);
fileInfo *create_new_file(char *name, char *file_path);
void free_fileinfo(fileInfo *head);
fileInfo *add_new_file(fileInfo *head, fileInfo *new, bool timesorted, int (*as)(fileInfo*, fileInfo*), int (*ds)(fileInfo*, fileInfo*));
void del_fileInfo(fileInfo *f);

#endif