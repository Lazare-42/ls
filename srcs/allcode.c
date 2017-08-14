/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:41:23 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 13:43:13 by lazrossi         ###   ########.fr       */
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
	int		i;

	i = 1;
	new_name = NULL;
	tmp = stock;
	while (tmp)
	{
		if (i)
			ft_putchar('\n');
		if (S_ISDIR(tmp->stat.st_mode) && ft_strcmp("..", tmp->name)
				&& ft_strcmp(".", tmp->name))
			ft_print_and_send(name, options, tmp, new_name);
		tmp = tmp->left;
		i = 0;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_g.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 15:44:10 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 17:07:02 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
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

int			ft_cmd_g(t_ls *tmp, char *foldername, int file_mode)
{
	int		*max_size;
	time_t	local_time;
	char	*path;
	t_ls	*stock;

	stock = tmp;
	max_size = ft_max_size(stock, file_mode);
	local_time = time(&local_time);
	(!stock) ? ft_putchar('\n') : 0;
	while (stock)
	{
		path = find_path(stock->name, foldername);
		ft_print_rights(stock, path);
		ft_print_grp(stock, max_size);
		ft_print_time(stock, local_time);
		ft_putchar(' ');
		ft_print_name(stock->name, stock->stat.st_mode);
		(S_ISLNK(stock->stat.st_mode)) ? print_lnkabout(path) : 0;
		(stock->left) ? ft_putchar('\n') : 0;
		stock = stock->left;
		ft_memdel((void**)&path);
	}
	ft_memdel((void**)&max_size);
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

int		ft_cmd_l(t_ls *tmp, char *foldername, int file_mode)
{
	int		*max_size;
	time_t	local_time;
	char	*path;
	t_ls	*stock;

	stock = tmp;
	max_size = ft_max_size(stock, file_mode);
	local_time = time(&local_time);
	(!stock) ? ft_putchar('\n') : 0;
	if (stock)
	{
		path = find_path(stock->name, foldername);
		ft_print_rights(stock, path);
		ft_print_grp_usr(stock, max_size);
		ft_print_time(stock, local_time);
		ft_putchar(' ');
		ft_print_name(stock->name, stock->stat.st_mode);
		(S_ISLNK(stock->stat.st_mode)) ? print_lnkabout(path) : 0;
		if (stock->left)
		{
			ft_putchar('\n');
			return (ft_cmd_l(stock->left, foldername, file_mode));
		}
		if (stock->right)
		{
			ft_putchar('\n');
			return (ft_cmd_l(stock->right, foldername, file_mode));
		}
		ft_memdel((void**)&path);
		ft_memdel((void**)&max_size);
	}
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
/*   Updated: 2017/08/10 13:43:37 by lazrossi         ###   ########.fr       */
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
/*   Updated: 2017/08/10 13:45:08 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_free(t_ls **stock)
{
	t_ls *tmp;

	while (*stock)
	{
		tmp = (*stock)->left;
		free((*stock)->name);
		ft_memdel((void**)stock);
		*stock = tmp;
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
/*   Created: 2017/08/10 13:45:32 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 13:49:52 by lazrossi         ###   ########.fr       */
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

int		*ft_new_int_tab(int *new)
{
	new[0] = 0;
	new[1] = 0;
	new[2] = 0;
	new[3] = 0;
	return (new);
}

int		*ft_fillup_val(t_ls *tmp, int *max, int file_mode)
{
	int				val;
	struct group	*grp;
	int				k;

	k = 0;
	while (tmp)
	{
		(tmp->stat.st_nlink > max[0]) ? max[0] = tmp->stat.st_nlink : max[0];
		val = ft_strlen(getpwuid(tmp->stat.st_uid)->pw_name);
		(val > max[1]) ? max[1] = val : max[1];
		grp = getgrgid(tmp->stat.st_gid);
		(grp) ? val = ((int)ft_strlen(grp->gr_name)) : 0;
		(val > max[2]) ? max[2] = val : max[2];
		((int)tmp->stat.st_size > max[3]) ?
			max[3] = (int)tmp->stat.st_size : max[3];
		k = k + tmp->stat.st_blocks;
		tmp = tmp->left;
	}
	if (file_mode)
	{
		ft_putstr("total ");
		ft_putnbr(k);
		ft_putchar('\n');
	}
	return (max);
}

int		*ft_max_size(t_ls *stock, int file_mode)
{
	t_ls	*tmp;
	int		*max;
	char	*len;

	tmp = NULL;
	max = malloc(sizeof(int) * 4);
	max = ft_new_int_tab(max);
	tmp = stock;
	max = ft_fillup_val(tmp, max, file_mode);
	len = ft_itoa(max[0]);
	max[0] = ft_strlen(len);
	ft_strdel(&len);
	len = ft_itoa(max[3]);
	max[3] = ft_strlen(len);
	ft_strdel(&len);
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
/*   Updated: 2017/08/10 16:54:05 by lazrossi         ###   ########.fr       */
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

int		ft_check_file_errors(char **folder)
{
	struct stat buffstatt;

	while (folder && *folder)
	{
		if (lstat(*folder, &buffstatt))
		{
			ft_print_errors(*folder);
			return (0);
		}
		folder++;
	}
	return (1);
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
/*   Updated: 2017/08/10 16:46:34 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_ls	*ft_place_elem_according_to_last_modif(t_ls *stock, t_ls *new)
{
	t_ls	*check;
	int		t1;
	int		t2;

	check = stock;
	t1 = check->stat.st_mtimespec.tv_sec;
	t2 = new->stat.st_mtimespec.tv_sec;
	if (t2 >= t1)
	{
		new->left = stock;
		return (stock = new);
	}
	while (check->left && t2 <= (t1 = check->left->stat.st_mtimespec.tv_sec))
		check = check->left;
	new->left = check->left;
	check->left = new;
	return (stock);
}

t_ls	*ft_place_elem_according_to_last_access(t_ls *stock, t_ls *new)
{
	t_ls	*check;
	int		t1;
	int		t2;

	check = stock;
	t1 = check->stat.st_atimespec.tv_sec;
	t2 = new->stat.st_atimespec.tv_sec;
	if (t2 >= t1)
	{
		new->left = stock;
		return (stock = new);
	}
	while (check->left && t2 <= (t1 = check->left->stat.st_atimespec.tv_sec))
		check = check->left;
	new->left = check->left;
	check->left = new;
	return (stock);
}

t_ls	*ft_place_elem_according_to_creation(t_ls *stock, t_ls *new)
{
	t_ls	*check;
	int		t1;
	int		t2;

	check = stock;
	t1 = check->stat.st_birthtimespec.tv_sec;
	t2 = new->stat.st_birthtimespec.tv_sec;
	if (t2 >= t1)
	{
		new->left = stock;
		return (stock = new);
	}
	while (check->left && t2 <=
			(t1 = check->left->stat.st_birthtimespec.tv_sec))
		check = check->left;
	new->left = check->left;
	check->left = new;
	return (stock);
}

t_ls	*ft_place_elem_according_to_size(t_ls *stock, t_ls *new)
{
	t_ls	*check;
	int		t1;
	int		t2;

	check = stock;
	t1 = check->stat.st_size;
	t2 = new->stat.st_size;
	if (t2 >= t1)
	{
		new->left = stock;
		return (stock = new);
	}
	while (check->left && t2 <= (t1 = check->left->stat.st_size))
		check = check->left;
	new->left = check->left;
	check->left = new;
	return (stock);
}

t_ls	*ft_place_elem(t_ls *stock, t_ls *new, int sort_options)
{
	t_ls	*check;

	check = stock;
	if (!(stock))
		return (stock = new);
	if (sort_options & CMD_T)
		return (ft_place_elem_according_to_last_modif(stock, new));
	else if (sort_options & CMD_LAST_ACCESS)
		return (ft_place_elem_according_to_last_access(stock, new));
	else if (sort_options & CMD_S)
		return (ft_place_elem_according_to_size(stock, new));
	else if (sort_options & CMD_U)
		return (ft_place_elem_according_to_creation(stock, new));
	if (ft_strcmp(check->name, new->name) > 0)
	{
		new->left = stock;
		return (stock = new);
	}
	while (check->left && ft_strcmp(check->left->name, new->name) < 0)
		check = check->left;
	if (check->left)
	{
	new->left = NULL;
	check->right = new;
	return (stock);
	}
	new->left = check->left;
	check->left = new;
	return (stock);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:58:26 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 13:58:42 by lazrossi         ###   ########.fr       */
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
/*   Updated: 2017/08/10 17:07:24 by lazrossi         ###   ########.fr       */
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

void	ft_print_rights(t_ls *stock, char *path)
{
	int		attributes;
	acl_t	acl;
	char	c;
	int		mode;

	mode = stock->stat.st_mode;
	attributes = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	c = ft_mode(mode);
	ft_putchar(c);
	ft_putchar((stock->stat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((stock->stat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((stock->stat.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((stock->stat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((stock->stat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((stock->stat.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((stock->stat.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((stock->stat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((stock->stat.st_mode & S_IXOTH) ? 'x' : '-');
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
	ft_putstr(getpwuid(stock->stat.st_uid)->pw_name);
	ft_put_whites(max_size[1],
			ft_strlen(getpwuid(stock->stat.st_uid)->pw_name), 2);
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

	path_size = readlink(fpath, buf, 1024);
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
/*   Updated: 2017/08/10 14:05:44 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/ioctl.h>

int		ft_longest_name(t_ls *stock)
{
	int		i;
	t_ls	*tmp;

	i = 0;
	tmp = stock;
	while (tmp)
	{
		i = ((int)ft_strlen(tmp->name) > i) ? (int)ft_strlen(tmp->name) : i;
		tmp = tmp->left;
	}
	return (i);
}

void	ft_print_normal(t_ls *stock)
{
	t_ls			*tmp;
	struct winsize	max;
	int				i;
	int				maxx;
	int				j;

	j = 0;
	maxx = 0;
	i = ft_longest_name(stock);
	tmp = stock;
	ioctl(1, TIOCGWINSZ, &max);
	while (tmp)
	{
		j = (int)ft_strlen(tmp->name);
		maxx += j;
		(maxx >= max.ws_col) ? ft_putchar('\n') : 0;
		(maxx >= max.ws_col) ? maxx = j : 0;
		ft_print_name(tmp->name, tmp->stat.st_mode);
		while (j++ <= i && ++maxx < max.ws_col && tmp->left)
			ft_putchar(' ');
		if (!(tmp->left))
			ft_putchar('\n');
		tmp = tmp->left;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 01:51:31 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 16:44:08 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/xattr.h>
#include <pwd.h>
#include <time.h>
#include "ls.h"

static t_ls		*ft_new_elem(char *name, const char *foldername,
		t_ls *stock, int sort_options)
{
	t_ls *new;
	char *path;

	if (!(name))
		return (stock);
	if (!(new = malloc(sizeof(t_ls))))
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	new->name = ft_strdup(name);
	(foldername) ? path = find_path(name, (char*)foldername) : 0;
	(!(foldername)) ? path = name : 0;
	if (lstat(path, &(new->stat)))
	{
		ft_strdel(&path);
		ft_print_errors(new->name);
		return (NULL);
	}
	if (foldername)
	{
		ft_strdel(&path);
		return (ft_place_elem(stock, new, sort_options));
	}
	return (new);
}

t_ls			*ft_store(char *foldername, DIR *dir, int sort_options)
{
	t_ls			*stock;
	struct dirent	*dent;

	stock = NULL;
	if (dir != NULL)
	{
		while ((dir && (dent = readdir(dir))))
		{
			if (!(sort_options & CMD_A) && dent->d_name[0] == '.')
				dent = NULL;
			if (dent)
				stock = ft_new_elem(dent->d_name,
						foldername, stock, sort_options);
		}
	}
	else
		stock = ft_new_elem(foldername, NULL, stock, sort_options);
	return (stock);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 14:43:46 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 19:59:58 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ls(char *name, int options, int file_mode)
{
	t_ls	*stock;
	t_ls    *tmp;
	DIR		*dir;
	int		i;

	i = 1;
	dir = NULL;
	if (file_mode && !(dir = opendir((const char *)name)))
	{
		ft_print_errors(name);
		return ;
	}
	stock = ft_store(name, dir, options);
	(options & CMD_REVERSE) ? ft_cmd_reverse(&(stock)) : 0;
	tmp = stock;
	((options & CMD_L && (!(options & CMD_G)))) ?
		ft_cmd_l(tmp, name, file_mode) : 0;
	((options & CMD_L && (!(options & CMD_G)))) ? i = 0 : 0;
	(options & CMD_G) ? i = 0 : 0;
	(options & CMD_G) ? ft_cmd_g(stock, name, file_mode) : 0;
	(i && (!(options & CMD_1))) ? ft_print_normal(stock) : 0;
	(i && (options & CMD_1)) ? ft_cmd_1(stock) : 0;
	((options & CMD_L || options & CMD_G) && (!(options & CMD_R))) ?
		ft_putchar('\n') : 0;
	(dir) ? closedir(dir) : 0;
	((options & CMD_R) ? ft_cmd_r(stock, name, options) : 0);
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
/*   Updated: 2017/08/10 14:22:34 by lazrossi         ###   ########.fr       */
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
		(j && *name) ? ft_putchar('\n') : 0;
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
