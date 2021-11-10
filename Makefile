NAME=	ft_ls

SRCS=	./main.c \
		./srcs/init_ls.c \
		./srcs/utils.c \
		./srcs/dir_process.c \
		./srcs/timer.c \
		./srcs/print.c \
		./srcs/free_dir.c

OBJS=	${SRCS:.c=.o}

CFLAG:=	-g3 -fsanitize=address -Wall -Werror -Wextra

all:	${NAME}

%.o:%.c
		gcc ${CFLAG} -o $@ -c $<

${NAME}:	${OBJS}
		@make -C libft
		gcc ${CFLAG} -o ${NAME} ${OBJS} libft/libft.a 

clean:
		@make clean -C libft 
		@rm -rf srcs/*.o

fclean:	clean
		@make fclean -C libft 
		@rm -rf ${NAME} a.out

re: fclean all

.PHONY: all clean fclean re
