#include "ls.h"

void	ft_print_errors(char *name)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

void			ft_print_usage_error(char error)
{
	ft_putstr_fd("./ft_ls: illegal option -- ", 2);
	ft_putchar_fd(error, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage: ./ft_ls [-lRartufgSU1] [file ...]", 2);
	ft_putchar_fd('\n', 2);
}
