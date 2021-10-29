NAME= ft_ls

CC= GCC

CFLAGS= -g3 -fsanitize=address -Wall -Wextra -Werror


all: ${NAME}

${NAME}:
	make -C libft

clean:
	make clean -C libft

fclean:
	make fclean -C libft