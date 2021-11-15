#ifndef FT_LS__H
# define FT_LS__H

# include <sys/types.h> // for type off_t
# include <sys/stat.h> // For stat()
# include <dirent.h> //opendir + readdir
# include "libft/inc/libft.h"
# include <stdbool.h> // for bool type
/*
	struct dirent : d_type = 4 if dir 
				= 8 if file or not symbolik file
				= 10 if symbolik link
*/
# include <time.h> // for type time_t
# include <pwd.h>  // getpwuid
# include <grp.h>   // getgrgid

# define RECURSIVE 1
# define ROOT 0

extern struct option opt;
extern struct directory *dir_list;
extern bool default_path;

struct directory
{
	char *name;
	char *full_path;
	DIR *open_dir;
	int is_valid;
	struct stat buf;
	struct dirent *read_dir;
	struct directory *next;
	struct directory *prev;
};

struct option
{
	bool long_format;
	bool recursive;
	bool hidded;
	bool reverse;
	bool modif_order;
};

/* utils.c */
void err_exit_msg(const char *msg);
struct directory *new_directory(const char *name, const char *pre_name);
struct directory *add_new_directory(struct directory *head, struct directory *new);

/* init_ls.c */
void init_ls(char **av);

/* dir_process.c */
void directory_processor(struct directory *dir, int rec_state);

/* print.c */
void print_dir_content(struct directory *head);
void print_not_found_dir(char *name);
void print_dir_name(char *name);

/* timer.c */
int datecmp(struct timespec t1, struct timespec t2);

/* free_dir.c */
void free_dir_list(struct directory *head);

void print_list(void); // debug fction

#endif