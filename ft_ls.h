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

extern struct option opt; //*opt;

extern struct file_info *files;

struct file_info
{
	char *name;		// change it into list for opti
	DIR *open;
	struct dirent *read;
	bool directory;
	struct stat info;
	struct file_info *next;
	struct file_info *prev;
};

struct option
{
	bool long_format;
	bool recursive;
	bool hidded;
	bool reverse;
	bool modif_order;
};


void err_exit_msg(const char *msg);

/* file_info_utils.c */
struct file_info *new_file(const char *name);
void add_new_file(struct file_info *new);
bool file_list_empty(void);

/* init_ls.c */
void commande_parsing(char **av);

void print_list(void); // debug fction

#endif