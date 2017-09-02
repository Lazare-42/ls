/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:30:17 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 02:41:36 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

char	ft_mode(int mode)
{
	char c;

	if (S_ISREG(mode))
		c = '-';
	else if (S_ISDIR(mode))
		c = 'd';
	else if (S_ISBLK(mode))
		c = 'b';
	else if (S_ISCHR(mode))
		c = 'c';
	else if (S_ISFIFO(mode))
		c = 'p';
	else if (S_ISLNK(mode))
		c = 'l';
	else if (S_ISSOCK(mode))
		c = 's';
	else
		(c = '?');
	return (c);
}
void	ft_print(t_ls *stock, char *foldername, int *max_size)
{
	time_t	local_time;
	char	*path;

	local_time = time(&local_time);
	if (stock)
	{
		if (stock->left)
			ft_print(stock->left, foldername, max_size);
		ft_putchar('\n');
		path = find_path(stock->name, foldername);
		ft_print_rights(stock, path);
		ft_print_grp_usr(stock, max_size);
		ft_print_time(stock, local_time);
		ft_putchar(' ');
		ft_print_name(stock->name, stock->stat.st_mode);
		(S_ISLNK(stock->stat.st_mode)) ? print_lnkabout(path) : 0;
		ft_memdel((void**)&path);
		if (stock->right)
			ft_print(stock->right, foldername, max_size);
	}
}

int		ft_cmd_l(t_ls *tmp, char *foldername, int *max_size)
{
	t_ls *stock;

	stock = tmp;
	(!stock) ? ft_putchar('\n') : 0;
	ft_putstr("total ");
	ft_putnbr(max_size[4]);
	ft_print(stock, foldername, max_size);
	return (1);
}
