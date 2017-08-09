#include "ls.h"

void	ft_print_name(char *name, int st_mode)
{
	if (S_ISDIR(st_mode))
	{
		ft_putstr("\e[0;96m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else if (S_ISLNK(st_mode))
	{
		ft_putstr("\033[0;35m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else if (st_mode & S_IXUSR)
	{
		ft_putstr("\033[0;31m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else
		ft_putstr(name);
}
