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
# include <fcntl.h>
# include <sys/ioctl.h>

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


void rec_file_process(fileInfo *head, bool option[256], bool recstate);

/* format_setters */
void set_max_field(const fileInfo *head, size_t max[4]);
void set_max_files(const fileInfo *head, size_t max[4]);

/* parse_cmp */
fileInfo *parse_cmd(int ac, char **av, bool option[256]);

/* utils */
int dir_total_size(fileInfo *head);
int alpha_sorted(fileInfo *new, fileInfo *tmp);
int date_sorted(fileInfo *new, fileInfo *tmp);
int fileInfo_size(fileInfo *head);
int parse_a_sorted(fileInfo *new, fileInfo *tmp);
int parse_d_sorted(fileInfo *new, fileInfo *tmp);

/* display_files */
void display_repo_name(fileInfo *f, bool rec, int size, int recindex);
void display_list_content(fileInfo *head, bool rev, bool longf);
void display_file(fileInfo *f, bool longf, size_t max[4], fileInfo *head);

/* fileinfo_tools */
void del_fileInfo(fileInfo *f);
fileInfo *create_new_file(char *name, char *file_path);
fileInfo *add_new_file(fileInfo *head, fileInfo *new, bool timesorted, int (*as)(fileInfo*, fileInfo*), int (*ds)(fileInfo*, fileInfo*));
void free_fileinfo(fileInfo *head);
int import_curr_repo(char *dir, fileInfo *head, bool timesort, bool showall);
size_t get_max_strlen(fileInfo *head);

#endif