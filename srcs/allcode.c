/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:41:23 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 01:40:20 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static	void	ft_print_and_send(char *name,
		int options, t_ls *stock, char *new_name)
{
	char *add_slash;

	add_slash = ft_strjoin(name, "/");
	new_name = ft_strjoin(add_slash, stock->name);
	ft_putchar('\n');
	ft_putstr(new_name);
	ft_putstr(":");
	ft_putchar('\n');
	ls(new_name, options, 1);
	ft_memdel((void**)&(new_name));
	ft_memdel((void**)&(add_slash));
}

void			ft_cmd_r(t_ls *stock, char *name, int options)
{
	t_ls	*tmp;
	char	*new_name;

	new_name = NULL;
	tmp = stock;
	if (tmp)
	{
		if (tmp->left)
			ft_cmd_r(tmp->left, name, options);
		if (S_ISDIR(tmp->stat.st_mode) && ft_strcmp("..", tmp->name)
				&& ft_strcmp(".", tmp->name))
			ft_print_and_send(name, options, tmp, new_name);
		if (tmp->right)
			ft_cmd_r(tmp->right, name, options);
	}
}
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:30:17 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 17:26:48 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

char		ft_mode(int mode)
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

static void	ft_print(t_ls *stock, char *foldername,
		int *max_size, int file_mode)
{
	time_t	local_time;
	char	*path;

	local_time = time(&local_time);
	if (stock)
	{
		if (stock->left)
			ft_print(stock->left, foldername, max_size, file_mode);
		(file_mode) ? ft_putchar('\n') : 0;
		path = (ft_strcmp(stock->name, foldername)) ?
			find_path(stock->name, foldername) : foldername;
		ft_print_rights(stock, path);
		ft_print_grp_usr(stock, max_size);
		ft_print_time(stock, local_time);
		ft_putchar(' ');
		ft_print_name(stock->name, stock->stat.st_mode);
		(S_ISLNK(stock->stat.st_mode)) ? print_lnkabout(path) : 0;
		(ft_strcmp(stock->name, foldername)) ? ft_memdel((void**)&path) : 0;
		if (stock->right)
			ft_print(stock->right, foldername, max_size, file_mode);
	}
}

int			ft_cmd_l(t_ls *tmp, char *foldername, int *max_size, int file_mode)
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:35:50 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 13:36:10 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_cmd_1(t_ls *stock)
{
	t_ls *tmp;

	tmp = stock;
	while (tmp)
	{
		ft_print_name(tmp->name, tmp->stat.st_mode);
		ft_putchar('\n');
		tmp = tmp->left;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:43:36 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 17:22:48 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	*find_path(char *name, char *foldername)
{
	char *path;

	path = ft_strjoin(foldername, "/");
	path = ft_strjoinfree(&path, &name, 'L');
	return (path);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:44:14 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 20:42:19 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_free(t_ls **stock)
{

	if ((*stock) && (*stock)->left)
		ft_free(&(*stock)->left);
	if ((*stock) && (*stock)->right)
		ft_free(&(*stock)->right);
	if (*stock)
	{
		ft_strdel(&((*stock)->name));
		ft_memdel((void**)stock);
	}
}

void	ft_cmd_reverse(t_ls **begin_list)
{
	t_ls*list;
	t_ls*q;
	t_ls*p;

	list = *begin_list;
	p = NULL;
	q = NULL;
	while (list)
	{
		p = list;
		list = list->left;
		p->left = q;
		q = p;
	}
	*begin_list = p;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 04:21:09 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 20:59:30 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include "ls.h"
#include <pwd.h>
#include <time.h>
#include <grp.h>

void	ft_put_whites(int max_str_len, int fillup, int options)
{
	char *tmp;

	tmp = NULL;
	if (options == 1 || options == 4)
	{
		tmp = ft_itoa(fillup);
		fillup = ft_strlen(tmp);
		ft_strdel(&tmp);
	}
	while (fillup < max_str_len)
	{
		ft_putchar(' ');
		fillup++;
	}
	(options != 3) ? ft_putchar(' ') : 0;
	if (options != 1 && options != 3)
		ft_putchar(' ');
}

int		*ft_fillup_val(t_ls *stock, int *max, int sort_options)
{
	int				val;
	struct group	*grp;
	int				k;

	k = 0;
	if (stock && ((sort_options & CMD_L) || (sort_options & CMD_G)))
	{
		(stock->stat.st_nlink > max[0]) ? max[0] = stock->stat.st_nlink : 0;
		val = (getpwuid(stock->stat.st_uid)) ?
			ft_strlen(getpwuid(stock->stat.st_uid)->pw_name) : 0;
		(val > max[1]) ? max[1] = val : 0;
		grp = getgrgid(stock->stat.st_gid);
		(grp) ? val = ((int)ft_strlen(grp->gr_name)) : 0;
		(val > max[2]) ? max[2] = val : 0;
		((int)stock->stat.st_size > max[3]) ?
			max[3] = (int)stock->stat.st_size : 0;
		max[4] = max[4] + stock->stat.st_blocks;
		stock->name_len = 0;
	}
	else
	{
		stock->name_len = ft_strlen(stock->name);
		(stock->name_len > max[0]) ? max[0] = stock->name_len : 0;
	}
	return (max);
}

int		*ft_max_size(t_ls *stock, int *max, int sort_options)
{
	max = ft_fillup_val(stock, max, sort_options);
	return (max);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:50:16 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 02:56:21 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ft_check_usage(char ***av)
{
	int	command_options;

	command_options = 0;
	++*av;
	while (*av)
	{
		if (**av && ***av == '-')
		{
			if (**av && *(**av + 1) == '-')
				return (command_options);
			++**av;
			while (***av)
			{
				if (ft_stock_commands(***av, command_options))
					command_options = ft_stock_commands(***av, command_options);
				else
					return (-1);
				++**av;
			}
		}
		else
			return (command_options);
		++*av;
	}
	return (command_options);
}

void	ft_check_file_errors(char **folder)
{
	struct stat buffstatt;

	while (folder && *folder)
	{
		if (lstat(*folder, &buffstatt))
			ft_print_errors(*folder);
		folder++;
	}
}

int		ft_stock_commands(char command, int command_options)
{
	if (command == 'l' || command == 'R' || command == 'a'
			|| command == 'r' || command == 't' || command == 'u'
			|| command == 'f' || command == 'g' || command == 'S'
			|| command == 'U' || command == '1')
	{
		(command == 'l') ? command_options = command_options | CMD_L : 0;
		(command == 'R') ? command_options = command_options | CMD_R : 0;
		(command == 'a' || command == 'f') ?
			command_options = command_options | CMD_A : 0;
		(command == 'r') ? command_options = command_options | CMD_REVERSE : 0;
		(command == 't') ? command_options = command_options | CMD_T : 0;
		(command == 'u') ?
			command_options = command_options | CMD_LAST_ACCESS : 0;
		(command == 'g') ? command_options = command_options | CMD_G : 0;
		(command == 'S') ? command_options = command_options | CMD_S : 0;
		(command == 'U') ? command_options = command_options | CMD_U : 0;
		(command == '1') ? command_options = command_options | CMD_1 : 0;
	}
	else
		return (0);
	return (command_options);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_place_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:55:44 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 05:08:34 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <stdio.h>

static int		ft_sort_by_rev_options(t_ls *stock,
		t_ls *next_stock, int sort_options)
{
	if (sort_options & CMD_T)
		return (next_stock->stat.st_mtimespec.tv_sec
				- stock->stat.st_mtimespec.tv_sec);
	else if (sort_options & CMD_LAST_ACCESS)
		return (next_stock->stat.st_atimespec.tv_sec
				- stock->stat.st_atimespec.tv_sec);
	else if (sort_options & CMD_S)
		return (next_stock->stat.st_size
				- stock->stat.st_size);
	else if (sort_options & CMD_U)
		return (next_stock->stat.st_birthtimespec.tv_sec
				- stock->stat.st_birthtimespec.tv_sec);
	else
		return (ft_strcmp(stock->name, next_stock->name));
}

int				ft_sort_by_options(t_ls *stock,
		t_ls *next_stock, int sort_options)
{
	if (!(sort_options & CMD_REVERSE))
	{
		if (sort_options & CMD_T)
			return (stock->stat.st_mtimespec.tv_sec -
					next_stock->stat.st_mtimespec.tv_sec);
		else if (sort_options & CMD_LAST_ACCESS)
			return (stock->stat.st_atimespec.tv_sec -
					next_stock->stat.st_atimespec.tv_sec);
		else if (sort_options & CMD_S)
			return (stock->stat.st_size -
					next_stock->stat.st_size);
		else if (sort_options & CMD_U)
			return (stock->stat.st_birthtimespec.tv_sec -
					next_stock->stat.st_birthtimespec.tv_sec);
		else
			return (ft_strcmp(next_stock->name, stock->name));
	}
	return (ft_sort_by_rev_options(stock, next_stock, sort_options));
}

int				ft_place_elem(t_ls *stock, t_ls *next_stock,
		int **max, int sort_options)
{
	if (ft_sort_by_options(stock, next_stock, sort_options) <= 0)
	{
		if (!stock->left)
		{
			stock->left = next_stock;
			if (stock->color == 0)
				return (0);
			return (1);
		}
		else
			return (ft_place_elem(stock->left, next_stock,
						max, sort_options));
	}
	if (!stock->right)
	{
		stock->right = next_stock;
		if (stock->color == 0)
			return (0);
		return (1);
	}
	else
		return (ft_place_elem(stock->right, next_stock,
					max, sort_options));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:58:26 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 02:57:05 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_print_errors(char *name)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

void	ft_print_usage_error(char error)
{
	ft_putstr_fd("./ft_ls: illegal option -- ", 2);
	ft_putchar_fd(error, 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("usage: ./ft_ls [-lRartufgSU1] [file ...]", 2);
	ft_putchar_fd('\n', 2);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:37:13 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 18:41:36 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <time.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void	ft_print_time(t_ls *stock, time_t local_time)
{
	char *tmp;
	char *file_time;

	file_time = ctime(&(stock->stat.st_mtime));
	tmp = NULL;
	if (((int)local_time - (int)stock->stat.st_mtime) > 15778800)
	{
		tmp = ft_strsub(file_time, 4, 7);
		ft_putstr(tmp);
		ft_strdel(&tmp);
		tmp = ft_strsub(&file_time[19], 0, 5);
		ft_putstr(tmp);
		ft_strdel(&tmp);
		return ;
	}
	tmp = ft_strsub(file_time, 4, 12);
	ft_putstr(tmp);
	ft_strdel(&tmp);
}

char	*ft_get_rights(int mode)
{
	char *rights;

	rights = ft_strnew(10);
	rights[0] = (mode & S_IRUSR) ? 'r' : '-';
	rights[1] = (mode & S_IWUSR) ? 'w' : '-';
	rights[2] = (mode & S_IXUSR) ? 'x' : '-';
	rights[2] = (mode & S_ISUID) ? 'S' : '-';
	rights[3] = (mode & S_IRGRP) ? 'r' : '-';
	rights[4] = (mode & S_IWGRP) ? 'w' : '-';
	rights[5] = (mode & S_IXGRP) ? 'x' : '-';
	rights[5] = (mode & S_ISGID) ? 'S' : '-';
	rights[6] = (mode & S_IROTH) ? 'r' : '-';
	rights[7] = (mode & S_IWOTH) ? 'w' : '-';
	rights[8] = (mode & S_IXOTH) ? 'x' : '-';
	rights[9] = '\0';
	return (rights);
}

void	ft_print_rights(t_ls *stock, char *path)
{
	int		attributes;
	acl_t	acl;
	char	c;
	int		mode;
	char	*exec_rights;

	exec_rights = NULL;
	mode = stock->stat.st_mode;
	attributes = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	c = ft_mode(mode);
	ft_putchar(c);
	exec_rights = ft_get_rights(stock->stat.st_mode);
	(exec_rights) ? free(exec_rights) : 0;
	(attributes) ? ft_putchar('@') : 0;
	(acl && (!(attributes))) ? ft_putchar('+') : 0;
	((!acl) && (!attributes)) ? ft_putchar(' ') : 0;
	(acl) ? acl_free((void*)acl) : 0;
}

void	ft_print_grp_usr(t_ls *stock, int *max_size)
{
	struct group *grp;

	ft_put_whites(max_size[0], stock->stat.st_nlink, 1);
	ft_putnbr(stock->stat.st_nlink);
	ft_putchar(' ');
	if (getpwuid(stock->stat.st_uid))
	{
		ft_putstr(getpwuid(stock->stat.st_uid)->pw_name);
		ft_put_whites(max_size[1],
			ft_strlen(getpwuid(stock->stat.st_uid)->pw_name), 2);
	}
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

void	print_lnkabout(char *fpath)
{
	int		path_size;
	char	buf[1024];

	if ((path_size = readlink(fpath, buf, 1024)) == -1)
	{
		ft_print_errors(fpath);
		return ;
	}
	buf[path_size] = '\0';
	ft_putstr(" -> ");
	ft_putstr(buf);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 14:03:25 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 15:59:17 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/ioctl.h>
#include <stdio.h>

void	ft_proper_print(t_ls *tmp, int max_ws_col,
		int max_stock_val, int *total_written)
{
	int i;

	i = max_stock_val;
	if (tmp && tmp->name)
	{
		if (tmp->left)
			ft_proper_print(tmp->left,
					max_ws_col, max_stock_val, total_written);
		*total_written += max_stock_val + max_stock_val;
		(*total_written >= max_ws_col) ? ft_putchar('\n') : 0;
		(*total_written >= max_ws_col) ? *total_written = 0 : 0;
		ft_print_name(tmp->name, tmp->stat.st_mode);
		while (i-- - tmp->name_len >= 0)
			ft_putchar(' ');
		if (tmp->right)
			ft_proper_print(tmp->right,
					max_ws_col, max_stock_val, total_written);
	}
}

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

void	ft_print_normal(t_ls *stock, int max_stock_val)
{
	t_ls			*tmp;
	struct winsize	max;
	int				maxx_ws_col;
	int				total_written;

	tmp = stock;
	ioctl(1, TIOCGWINSZ, &max);
	maxx_ws_col = max.ws_col;
	total_written = 0;
	ft_proper_print(tmp, maxx_ws_col, max_stock_val, &total_written);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 01:51:31 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 19:01:19 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/xattr.h>
#include <pwd.h>
#include <time.h>
#include "ls.h"

t_ls	*ft_new_elem(char *name, const char *foldername,
		int **max_padding, int sort_options)
{
	t_ls *new;
	char *path;

	path = NULL;
	if (!(name))
		return (NULL);
	if (!(new = malloc(sizeof(t_ls))))
		exit(1);
	new->left = NULL;
	new->right = NULL;
	new->color = 0;
	new->name = ft_strdup(name);
	(foldername) ? path = find_path(name, (char*)foldername) : 0;
	(!(foldername)) ? path = name : 0;
	if (lstat(path, &(new->stat)))
	{
		ft_strdel(&path);
		ft_print_errors(new->name);
		ft_strdel(&(new->name));
		ft_memdel((void**)new);
		return (NULL);
	}
	*max_padding = ft_max_size(new, *max_padding, sort_options);
	(path) ? ft_strdel(&path) : 0;
	return (new);
}

int		*ft_store_folder(char *foldername, int *max, t_ls **stock, DIR *dir)
{
	struct dirent	*dent;
	t_ls			*new_stock;

	while ((dir && (dent = readdir(dir))))
	{
		(!(max[5] & CMD_A) && dent->d_name[0] == '.') ?
			dent = NULL : 0;
		if (dent && !(*stock))
		{
			(*stock) = ft_new_elem(dent->d_name, foldername,
					&max, max[5]);
			((*stock)) ? (*stock)->color = 1 : 0;
		}
		else if (dent)
		{
			if (!(new_stock = ft_new_elem(dent->d_name, foldername,
					&max, max[5])))
				return (max);
			if (!(ft_place_elem((*stock), new_stock, &max, max[5])))
				ft_rotate(stock, new_stock, max[5]);
		}
	}
	return (max);
}

int		*ft_store(char *foldername, DIR *dir, int sort_options, t_ls **stock)
{
	int				*max;

	if (!(max = (int*)ft_memalloc(sizeof(int) * 6)))
		exit(1);
	max[5] = sort_options;
	if (dir != NULL)
		max = ft_store_folder(foldername, max, stock, dir);
	else
		(*stock) = ft_new_elem(foldername, NULL, &max, sort_options);
	return (max);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 14:43:46 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 21:13:54 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		*ft_adapt_padding_size(int *max)
{
	char	*len;

	len = ft_itoa(max[0]);
	max[0] = ft_strlen(len);
	ft_strdel(&len);
	len = ft_itoa(max[3]);
	max[3] = ft_strlen(len);
	ft_strdel(&len);
	return (max);
}

void	pursue_ls(char *name, int options, int *max, t_ls *tmp)
{
	int		i;

	i = 1;
	((options & CMD_L && (!(options & CMD_G)))) ? i = 0 : 0;
	(options & CMD_G) ? i = 0 : 0;
	(i && (!(options & CMD_1))) ? ft_print_normal(tmp, max[0]) : 0;
	(i && (options & CMD_1)) ? ft_cmd_1(tmp) : 0;
	((options & CMD_L || options & CMD_G) && (!(options & CMD_R))) ?
		ft_putchar('\n') : 0;
	((options & CMD_R)) ? ft_putchar('\n') : 0;
	((options & CMD_R) ? ft_cmd_r(tmp, name, options) : 0);
}

void	ls(char *name, int options, int file_mode)
{
	t_ls	*stock;
	t_ls	*tmp;
	DIR		*dir;
	int		*max;

	dir = NULL;
	stock = NULL;
	if (file_mode && !(dir = opendir((const char *)name)))
	{
		ft_print_errors(name);
		return ;
	}
	max = ft_store(name, dir, options, &stock);
	tmp = stock;
	((options & CMD_G) ||
	(options & CMD_L)) ? max = ft_adapt_padding_size(max) : 0;
	((options & CMD_L && (!(options & CMD_G)))) ?
		ft_cmd_l(tmp, name, max, file_mode) : 0;
	(options & CMD_G) ? ft_cmd_g(tmp, name, max, file_mode) : 0;
	pursue_ls(name, options, max, tmp);
	(dir) ? closedir(dir) : 0;
	if (max)
		free(max);
	ft_free(&stock);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 14:14:42 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 20:59:12 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static	void	ft_send_folders_to_ls(char **name, int command_options, int j)
{
	struct stat buffstatt;

	while (name && *name)
	{
		if (!(lstat(*name, &buffstatt)))
		{
			if (buffstatt.st_mode & S_IFDIR)
			{
				(j) ? ft_putstr(*name) : 0;
				(j) ? ft_putstr(":\n") : 0;
				ls(*name, command_options, 1);
			}
		}
		++name;
	}
}

static	void	ft_send_files_to_ls(char **folder, int command_options)
{
	struct stat	buffstatt;
	char		**name;
	int			j;

	name = folder;
	j = 0;
	name++;
	(*name) ? j = 1 : 0;
	name = folder;
	while (folder && *folder)
	{
		if (!(lstat(*folder, &buffstatt)))
		{
			if (!(buffstatt.st_mode & S_IFDIR))
				ls(*folder, command_options, 0);
		}
		++folder;
	}
	ft_send_folders_to_ls(name, command_options, j);
}

int				main(int ac, char **av)
{
	int		command_options;
	char	**tmp;

	command_options = 0;
	ac++;
	if ((command_options = ft_check_usage(&av)) == -1)
	{
		ft_print_usage_error(**av);
		return (-1);
	}
	if (*av && !(ft_strcmp(*av, "--")))
		av++;
	if (*av)
	{
		tmp = av;
		ft_check_file_errors(tmp);
		ft_send_files_to_ls(av, command_options);
		return (0);
	}
	else
		ls(".", command_options, 1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 03:54:45 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 04:07:25 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	ft_rotate_2(t_ls **stock)
{
	t_ls	*y;
	t_ls	*x;
	t_ls	*z;

	z = *stock;
	if ((x = (*stock)->left) && !(*stock)->left->color &&
			(y = (*stock)->left->right) && !(*stock)->left->right->color)
	{
		z->left = y->right;
		x->right = y->left;
		y->right = z;
		y->left = x;
		*stock = y;
		return (1);
	}
	return (0);
}

static int	ft_rotate_4(t_ls **stock)
{
	t_ls	*y;
	t_ls	*x;
	t_ls	*z;

	z = *stock;
	if ((y = (*stock)->right) && !(*stock)->right->color &&
			(z = (*stock)->right->right) && !(*stock)->right->right->color)
	{
		x = *stock;
		x->right = y->left;
		y->right = z;
		y->left = x;
		*stock = y;
		return (1);
	}
	return (0);
}

static int	ft_rotate_3(t_ls **stock)
{
	t_ls	*y;
	t_ls	*x;
	t_ls	*z;

	z = *stock;
	if ((z = (*stock)->right) && !(*stock)->right->color &&
			(y = (*stock)->right->left) && !(*stock)->right->left->color)
	{
		x = *stock;
		x->right = y->left;
		z->left = y->right;
		y->right = z;
		y->left = x;
		*stock = y;
		return (1);
	}
	return (0);
}

void		ft_rotate(t_ls **stock, t_ls *new_stock, int sort_options)
{
	t_ls	*y;
	t_ls	*x;
	t_ls	*z;

	z = *stock;
	if ((y = (*stock)->left) && !(*stock)->left->color &&
			(x = (*stock)->left->left) && !(*stock)->left->left->color)
	{
		z->left = y->right;
		y->right = z;
		y->left = x;
		*stock = y;
	}
	else if (ft_rotate_2(stock))
		return ;
	else if (ft_rotate_3(stock))
		return ;
	else if (ft_rotate_4(stock))
		return ;
	else if (ft_sort_by_options(*stock, new_stock, sort_options) <= 0)
		ft_rotate(&(*stock)->left, new_stock, sort_options);
	else
		ft_rotate(&(*stock)->right, new_stock, sort_options);
}
