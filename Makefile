NAME=	ft_ls

SRCS=	./srcs/main.c \
		./srcs/file_info_tools.c \
		./srcs/parse_cmd.c \
		./srcs/utils.c \
		./srcs/display_files.c \
		srcs/rec_file_process.c

OBJS=	${SRCS:.c=.o}

CFLAG:=	-g3 -fsanitize=address -Wall -Werror -Wextra

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
