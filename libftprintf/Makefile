CC	= gcc

HDRS = inc/ft_printf.h \
		inc/macro.h \
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
				./src/type/ft_type_pourcent.c\
				./src/type/ft_typeC.c\
				./src/type/ft_typeD.c\
				./src/type/ft_typeP.c\
				./src/type/ft_typeS.c\
				./src/type/ft_typeU.c\
				./src/type/ft_typeX.c\
				./src/type/ft_typeXmaj.c\
				./src/ft_getopt.c\
				./src/ft_printf.c\
				./src/ft_struct_print.c\

OBJS	= ${SRCS:.c=.o}

CFLAGS	= -g3 -fsanitize=address -Wall -Wextra -Werror


${NAME}: ${OBJS}
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
