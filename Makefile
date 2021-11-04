NAME=	ft_ls

SRCS=	./main.c

OBJS=	${SRCS:.c=.o}

CFLAG=	-g3 -fsanitize=address -Wall -Werror -Wextra

all:	${NAME}

%.o:%.c
		gcc ${CFLAG} -o $@ -c $<

${NAME}:	${OBJS}
			@make -C libft
			gcc ${CFLAG} -o $@ -c $< libft/libft.a

clean:
		@make clean -C libft 
		@rm -rf srcs/*.o

fclean:	clean
		@make fclean -C libft 
		@rm -rf ${NAME} a.out

re: fclean all

.PHONY: all clean fclean re