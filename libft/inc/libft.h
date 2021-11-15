#ifndef LIBFT__H
# define LIBFT__H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../srcs/ft_printf/inc/ft_printf.h"

typedef struct s_list
{
	void *content;
	struct s_list *next;
}				t_list;

/* c_type.c */
int ft_isalpha(int c);
int ft_isdigit(int c);
int ft_isalnum(int c);
int ft_isascii(int c);
int ft_isprint(int c);

/* string.c */
size_t ft_strlen(const char *s);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t ft_strlcat(char *dst, const char *src, size_t dstsize);
char *ft_strdup(const char *s1);

/* memstr.c */
void *ft_memset(void *b, int c, size_t len);
void ft_bzero(void *s, size_t n);
void *ft_memcpy(void *dst, const void *src, size_t n);
void *ft_memccpy(void *dst, const void *src, int c, size_t n);
void *ft_memmove(void *dst, const void *src, size_t len);
void *ft_memchr(const void *s, int c, size_t n);
int ft_memcmp(const void *s1, const void *s2, size_t n);
void *ft_calloc(size_t count, size_t size);

/* strsearch.c */
char *ft_strchr(const char *s, int c);
char *ft_strrchr(const char *s, int c);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strnstr(const char *haystack, const char *needle, size_t len);

/* converter.c */
int ft_atoi(const char *str);
int ft_toupper(int c);
int ft_tolower(int c);
char *ft_itoa(int n);
char *ft_itoahexa(long n);
char *ft_unitoa_base(unsigned int n, char *base);

/* alloc_string.c */
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strtrim(char const *s1, char const *set);
char *ft_strmapi(char const *s, char (*f)(unsigned int, char));
void ft_striteri(char *s, void (*f)(unsigned int, char*));

/* ft_split.c */
char **ft_split(char const *s, char c);

/* ft_put_fd.c */
void ft_putchar_fd(char c, int fd);
void ft_putstr_fd(char *s, int fd);
void ft_putendl_fd(char *s, int fd);
void ft_putnbr_fd(int n, int fd);
void	ft_putchar(char c);
void	ft_putstr(char *str);

/* list.c */
t_list *ft_lstnew(void *content);
void ft_lstadd_front(t_list **alst, t_list *new);
int ft_lstsize(t_list *lst);
t_list *ft_lstlast(t_list *lst);
void ft_lstadd_back(t_list **alst, t_list *new);
void ft_lstdelone(t_list *lst, void (*del)(void*));
void ft_lstclear(t_list **lst, void (*del)(void*));
void ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*));

#endif