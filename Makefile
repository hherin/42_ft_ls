NAME=	ft_ls

SRCS=	./src/main.c \
			./src/fileInfo_utils.c \
			./src/option.c \
			./src/sort.c \
			./src/ls_routine.c \
			./src/print.c
	
OBJS=	${SRCS:.c=.o}

CFLAG:= -g -Wall -Werror -Wextra

all:	${NAME}

%.o:%.c
		gcc ${CFLAG} -o $@ -c $<

${NAME}:	${OBJS}
		@make -C lib
		gcc ${CFLAG} -o ${NAME} ${OBJS} lib/libftprintf.a 

clean:
		@make clean -C lib
		@rm -rf srcs/*.o

fclean:	clean
		@make fclean -C lib
		@rm -rf ${NAME} a.out

re: fclean all

.PHONY: all clean fclean re
