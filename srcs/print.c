#include "../ft_ls.h"

void print_dir_content(struct directory *head)
{
	struct directory *tmp = opt.reverse ? head->prev : head->next;

	while (tmp != head)
	{
		ft_putstr_fd(tmp->name, 1);
		// printf("%s --- add %p\n", tmp->name, tmp);
		ft_putchar_fd('\n', 1);
		tmp = opt.reverse ? tmp->prev : tmp->next;
	}
	ft_putchar_fd('\n', 1);
}