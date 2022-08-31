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

enum option_values {SHOW_HIDDEN, LONG_FORMAT, REVERSE, BY_MODIF_TIME, RECURSIVE};

typedef struct info
{
    char *filename;
    char *fullpath;
    char *parent;
    struct stat statp;
    bool is_dir;
	struct info *next;
	struct info *prev;
}       fileInfo;

extern fileInfo *main_list, *sub_list;

int size_list(fileInfo *head);      // NOT USED

typedef int (*Sortfcn)(fileInfo *, fileInfo*);

/** print.c **/
void print_list(fileInfo *head, bool options[5]);

/** option.c **/
char **get_options(char **av, bool options[5], Sortfcn *func);

/** ls_routine.c **/
void parse_argument(fileInfo *head, fileInfo *new, int (*sortfcn)(fileInfo*, fileInfo*));
void ls_routine(fileInfo *head, bool options[5], int (*sortfcn)(fileInfo *, fileInfo *));

/** utils/sort.c **/
int namecmp(fileInfo *a, fileInfo *b);
int revnamecmp(fileInfo *a, fileInfo *b);
int datecmp(fileInfo *a, fileInfo *b);
int revdatecmp(fileInfo *a, fileInfo *b);

/** utils/fileInfo.c **/
void add_file_into_dir(fileInfo *head, fileInfo *new, int (*sortfcn)(fileInfo*, fileInfo*));
void fileInfo_add_front(fileInfo *elem, fileInfo *new);
void free_fileInfo_list(fileInfo *head);
fileInfo *create_element(char *filename, char *parent);
fileInfo *create_root_list();

/* format_setters */
void set_max_field(const fileInfo *head, int max[4]);
void set_max_files(const fileInfo *head, int max[4]);
int dir_total_size(fileInfo *head);

#endif