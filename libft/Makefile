NAME=	libft.a

SRCS=	./srcs/is_type.c \
		./srcs/stringh.c \
		./srcs/memstr.c \
		./srcs/strsearch.c \
		./srcs/converter.c \
		./srcs/alloc_string.c \
		./srcs/ft_split.c \
		./srcs/ft_put_fd.c \
		./srcs/list.c \
		./srcs/ft_printf/src/type/ft_type_pourcent.c \
		./srcs/ft_printf/src/type/ft_typeC.c \
		./srcs/ft_printf/src/type/ft_typeD.c \
		./srcs/ft_printf/src/type/ft_typeP.c \
		./srcs/ft_printf/src/type/ft_typeS.c \
		./srcs/ft_printf/src/type/ft_typeU.c \
		./srcs/ft_printf/src/type/ft_typeX.c \
		./srcs/ft_printf/src/type/ft_typeXmaj.c \
		./srcs/ft_printf/src/ft_getopt.c \
		./srcs/ft_printf/src/ft_printf.c \
		./srcs/ft_printf/src/ft_struct_print.c \

OBJS=	${SRCS:.c=.o}

CFLAG=	-g3 -fsanitize=address -Wall -Werror -Wextra

all:	${NAME}

%.o:%.c
		gcc ${CFLAG} -o $@ -c $<

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}

clean:
		@rm -rf srcs/*.o

fclean:	clean
		@rm -rf ${NAME} a.out

re: fclean all

.PHONY: all clean fclean re