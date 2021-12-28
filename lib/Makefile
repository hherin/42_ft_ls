CC	= gcc

HDRS =	inc/ft.h \
		inc/libft.h 

RM	= rm -f

NAME	= libftprintf.a

SRCS = 	./lib/alloc_string.c \
		./lib/converter.c \
		./lib/ft_put_fd.c \
		./lib/is_type.c\
		./lib/list.c\
		./lib/memstr.c\
		./lib/stringh.c\
		./lib/strsearch.c\
		./printf/ft_printf.c \
		./printf/ft_strnlen.c \
		./printf/skip_atoi.c \
		./printf/to_c.c \
		./printf/to_n.c \
		./printf/to_nbr.c \
		./printf/to_s.c 

OBJS	= ${SRCS:.c=.o}

CFLAGS	= -g3 -fsanitize=address -Wall -Wextra -Werror


${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}


all: ${NAME}

%.o:%.c 
	${CC} ${CFLAGS} -o $@ -c $<


clean:
	${RM} ${BONUS_OBJS} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all bonus

.PHONY: all clean fclean re