/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CMD_r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 01:51:23 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/12 08:45:58 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include "ls.h"
#include "libft.h"
#include <pwd.h>
#include <time.h>
#include <grp.h>

void	ft_put_whites(int max_str_len,int  fillup, int options)
{
	if (options == 1 || options == 4)
		fillup = ft_strlen(ft_itoa(fillup));
	while (fillup <= max_str_len)
	{
		ft_putchar(' ');
		fillup++;
	}
	ft_putchar(' ');
}

int		ft_max_size(t_ls *stock, int options)
{
	int max;
	int tmp_val;
	struct group *grp;
	t_ls *tmp;

	max = 0;
	tmp = stock;
	while (tmp && options == 1)
	{
		(tmp->stat.st_nlink > max) ? max = tmp->stat.st_nlink : max;
		tmp = tmp->next;
	}
	while (tmp && options == 2)
	{
		tmp_val = ft_strlen(getpwuid(tmp->stat.st_uid)->pw_name);
		(tmp_val > max) ? max = tmp_val: max;
		tmp = tmp->next;
	}
	while (tmp && options == 3)
	{
		grp = getgrgid(tmp->stat.st_gid);
		((int)ft_strlen(grp->gr_name) > max) ? max = (int)ft_strlen(grp->gr_name) : max;
		tmp = tmp->next;
	}
	while (tmp && options == 4)
	{
		((int)tmp->stat.st_size > max) ?  max = (int)tmp->stat.st_size : max;
		tmp = tmp->next;
	}
	if (options == 1 || options == 4)
		max = ft_strlen(ft_itoa(max));
	return (max);
}

int		ft_CMD_r(t_ls *stock, char *foldername)
{
	char *time;
	int  max_size_size;
	int  max_name_size;
	int max_group_size;
	int	max_bytes_size;
    int  i = 0;

	max_size_size = ft_max_size(stock, 1);
	max_name_size = ft_max_size(stock, 2);
	max_group_size = ft_max_size(stock, 3);
	max_bytes_size = ft_max_size(stock, 4);
	while (stock)
	{

		ft_putchar (S_ISDIR(stock->stat.st_mode) ? 'd' : '-');
		ft_putchar( (stock->stat.st_mode & S_IRUSR) ? 'r' : '-');
		ft_putchar( (stock->stat.st_mode & S_IWUSR) ? 'w' : '-');
		ft_putchar( (stock->stat.st_mode & S_IXUSR) ? 'x' : '-');
		ft_putchar( (stock->stat.st_mode & S_IRGRP) ? 'r' : '-');
		ft_putchar( (stock->stat.st_mode & S_IWGRP) ? 'w' : '-');
		ft_putchar( (stock->stat.st_mode & S_IXGRP) ? 'x' : '-');
		ft_putchar( (stock->stat.st_mode & S_IROTH) ? 'r' : '-');


		i = listxattr(find_path(stock->name, foldername), NULL, stock->stat.st_size, XATTR_SHOWCOMPRESSION);
		if (i)
			ft_putchar('@');
		else
			ft_putchar(' ');

		ft_put_whites(max_size_size, stock->stat.st_nlink, 1);
		ft_putnbr(stock->stat.st_nlink);
		ft_putchar(' ');

		ft_putstr(getpwuid(stock->stat.st_uid)->pw_name);
		ft_put_whites(max_name_size, ft_strlen(getpwuid(stock->stat.st_uid)->pw_name), 2);

		struct group *grp;
		grp = getgrgid(stock->stat.st_gid);
		ft_putstr(grp->gr_name);
		ft_put_whites(max_group_size, ft_strlen(grp->gr_name), 3);

		ft_put_whites(max_bytes_size, stock->stat.st_size, 4);
		ft_putnbr((int)stock->stat.st_size);
		ft_putchar(' ');
		time = ctime(&(stock->stat.st_mtime));
		if (time[23] < '7')
		{
			ft_putstr(ft_strsub(time, 4, 7));
			ft_putstr(ft_strsub(&time[19], 0, 5));
		}
		else
		{
			time = ft_strsub(ctime(&(stock->stat.st_mtime)), 4, 12);
			ft_putstr(time);
		}

		ft_putchar(' ');
		ft_putstr(stock->name);
		ft_putchar('\n');
		stock = stock->next;
	}
	return (1);
}
