/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:30:17 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 17:06:39 by lazrossi         ###   ########.fr       */
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


int		ft_cmd_ll(t_ls *stock, char *foldername, int *max_size)
{
	time_t	local_time;
	char	*path;
	t_ls	*tmp;

	tmp = stock;
	local_time = time(&local_time);
	(!stock) ? ft_putchar('\n') : 0;
	if (tmp)
	{
		path = find_path(stock->name, foldername);
		ft_print_rights(stock, path);
		ft_print_grp_usr(stock, max_size);
		ft_print_time(stock, local_time);
		ft_putchar(' ');
		ft_print_name(stock->name, stock->stat.st_mode);
		(S_ISLNK(stock->stat.st_mode)) ? print_lnkabout(path) : 0;
		if (tmp->left)
		{
			ft_putchar('\n');
			(ft_cmd_ll(tmp->left, foldername, max_size));
		}
		if (tmp->right)
		{
			ft_putchar('\n');
			(ft_cmd_ll(tmp->right, foldername, max_size));
		}
		ft_memdel((void**)&path);
	}
	return (1);
}

int		ft_cmd_l(t_ls *stock, char *foldername, int *max_size)
{
	ft_cmd_ll(stock, foldername, max_size);
	ft_memdel((void**)&max_size);
	return (1);
}
