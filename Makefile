NAME=	ft_ls

SRCS=	./srcs/main.c \
		./srcs/init_ls.c \
		./srcs/utils.c \
		./srcs/dir_process.c \
		./srcs/list_handler.c \
		./srcs/print.c 

OBJS=	${SRCS:.c=.o}

CFLAG:=	-g3 -fsanitize=address -Wall -Werror -Wextra

all:	${NAME}

%.o:%.c
		gcc ${CFLAG} -o $@ -c $<

${NAME}:	${OBJS}
		@make -C libftprintf
		gcc ${CFLAG} -o ${NAME} ${OBJS} libftprintf/libftprintf.a 

clean:
		@make clean -C libftprintf
		@rm -rf srcs/*.o

fclean:	clean
		@make fclean -C libftprintf
		@rm -rf ${NAME} a.out

re: fclean all

.PHONY: all clean fclean re
