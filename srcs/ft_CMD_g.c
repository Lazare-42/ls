/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_g.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:30:17 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 17:27:37 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

static void	ft_print_grp(t_ls *stock, int *max_size)
{
	struct group *grp;

	ft_put_whites(max_size[0], stock->stat.st_nlink, 1);
	ft_putnbr(stock->stat.st_nlink);
	ft_putchar(' ');
	grp = getgrgid(stock->stat.st_gid);
	if (grp)
	{
		ft_putstr(grp->gr_name);
		ft_put_whites(max_size[2], ft_strlen(grp->gr_name), 3);
		ft_put_whites(max_size[3], stock->stat.st_size, 4);
		ft_putnbr((int)stock->stat.st_size);
		ft_putchar(' ');
		return ;
	}
	ft_putstr(strerror(errno));
	ft_put_whites(max_size[2], ft_strlen(strerror(errno)), 3);
}

void		ft_print(t_ls *stock, char *foldername, int *max_size,
		int file_mode)
{
	time_t	local_time;
	char	*path;

	local_time = time(&local_time);
	if (stock)
	{
		if (stock->left)
			ft_print(stock->left, foldername, max_size, file_mode);
		(file_mode) ? ft_putchar('\n') : 0;
		path = (ft_strcmp(foldername, stock->name)) ?
			find_path(stock->name, foldername) : foldername;
		(max_size[6]) ? ft_print_inode(stock->stat.st_ino) : 0;
		ft_print_rights(stock, path);
		ft_print_grp(stock, max_size);
		ft_print_time(stock, local_time);
		ft_putchar(' ');
		ft_print_name(stock->name, stock->stat.st_mode);
		(S_ISLNK(stock->stat.st_mode)) ? print_lnkabout(path) : 0;
		(ft_strcmp(foldername, stock->name)) ? ft_memdel((void**)&path) : 0;
		if (stock->right)
			ft_print(stock->right, foldername, max_size, file_mode);
	}
}

int			ft_cmd_g(t_ls *tmp, char *foldername, int *max_size, int file_mode)
{
	t_ls *stock;

	stock = tmp;
	if (file_mode)
	{
		ft_putstr("total ");
		ft_putnbr(max_size[4]);
	}
	ft_print(stock, foldername, max_size, file_mode);
	return (1);
}
