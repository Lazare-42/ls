#include "ls.h"
#include "libft.h"

void	ft_CMD_R(t_ls *stock,char *name, int options)
{
	t_ls *tmp;
	char *new_name;

	tmp = stock;
	while (stock)
	{
		new_name = NULL;
		if (S_ISDIR(stock->stat.st_mode) && ft_strcmp("..", stock->name) && ft_strcmp(".", stock->name))
		{
			new_name = ft_strjoin(ft_strjoin(name, "/"), stock->name);
			ft_putstr(new_name);
			ft_putstr(":\n");
			ls(new_name, options);
		}
		if (new_name)
			ft_bzero(new_name, ft_strlen(new_name));
		stock = stock->next;
		new_name = NULL;
	}
}
#include "ls.h"
#include "libft.h"
#include <sys/xattr.h> // for extended file attributes impression (@)
#include <pwd.h> // for getpwuid
#include <grp.h> // for getgrgido
#include <time.h> //self_explanatory

char 	ft_print_rights(t_ls *stock, char *path)
{
	int attributes;
	acl_t acl;
	char c;
	int mode;

	mode = stock->stat.st_mode;
	attributes = listxattr(path, NULL, stock->stat.st_size, XATTR_NOFOLLOW);
	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	(S_ISREG(stock->stat.st_mode)) ? c = '-' : (S_ISDIR(mode)) ? c = 'd' : 
		(S_ISBLK(mode)) ? c = 'b' : (S_ISCHR(mode)) ? c = 'c' : (S_ISFIFO(mode))? 
		c = 'p' : (S_ISLNK(mode)) ? c = 'l' : (S_ISSOCK(mode)) ? c = 's' : (c = '?')
		;
	ft_putchar (c);
	ft_putchar( (stock->stat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar( (stock->stat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar( (stock->stat.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar( (stock->stat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar( (stock->stat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar( (stock->stat.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar( (stock->stat.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar( (stock->stat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar( (stock->stat.st_mode & S_IXOTH) ? 'x' : '-');
	(attributes) ? ft_putchar('@') : (acl) ? ft_putchar('+') : ft_putchar(' ');
	//(acl) ? acl_free((void*)acl) : 0;
	return (c);
}

void    ft_print_GRP_USR(t_ls *stock, int *max_size)
{
	struct group *grp;

	ft_put_whites(max_size[0], stock->stat.st_nlink, 1);
	ft_putnbr(stock->stat.st_nlink);
	ft_putchar(' ');
	ft_putstr(getpwuid(stock->stat.st_uid)->pw_name);
	ft_put_whites(max_size[1], 
			ft_strlen(getpwuid(stock->stat.st_uid)->pw_name), 2);
	grp = getgrgid(stock->stat.st_gid);
	ft_putstr(grp->gr_name);
	ft_put_whites(max_size[2], ft_strlen(grp->gr_name), 3);
}

void	ft_print_name(unsigned char c, char *name, int st_mode)
{
	if (c == 'd')
	{
		ft_putstr(" \e[0;96m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else if (st_mode & S_IXUSR)
	{
		ft_putstr(" \033[0;31m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else if (c == 'l')
	{
		ft_putstr(" \033[0;35m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
	else
	{
		ft_putstr(" \e[0m");
		ft_putstr(name);
		ft_putstr("\e[0m");
	}
}


int		ft_CMD_l(t_ls *stock, char *foldername)
{
	int  *max_size;
	time_t local_time;
	char *file_time;
	char *path;
	char c;
	local_time = time(&local_time);

	max_size = ft_max_size(stock);
	while (stock)
	{
		ft_putchar('\n');
		path = find_path(stock->name, foldername);
		c = ft_print_rights(stock, path);
		ft_print_GRP_USR(stock, max_size);
		ft_put_whites(max_size[3], stock->stat.st_size, 4);
		ft_putnbr((int)stock->stat.st_size);
		ft_putchar(' ');
		file_time = ctime(&(stock->stat.st_mtime));
		(((int)local_time - (int)stock->stat.st_mtime) > 15778800) ? ft_putstr(ft_strsub(file_time, 4, 7)), ft_putstr(ft_strsub(&file_time[19], 0, 5)) : ft_putstr(ft_strsub(file_time, 4, 12));
		ft_putchar(' ');
		ft_print_name(c, stock->name, stock->stat.st_mode);
		stock = stock->next;
	}
	return(1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 14:43:44 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/10 14:44:19 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_free(t_ls **stock)
{
	t_ls *tmp;
	while (*stock)
	{
		tmp = (*stock)->next;
		free (*stock);
		*stock = tmp;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:14:10 by lazrossi          #+#    #+#             */
/*   Updated: 2017/03/30 10:30:09 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_CMD_r(t_ls **begin_list)
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
		list = list->next;
		p->next = q;
		q = p;
	}
	*begin_list = p;
}
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

int *ft_new_int_tab(int *new)
{
	new[0] = 0;
	new[1] = 0;
	new[2] = 0;
	new[3] = 0;
	return (new);
}

int	*ft_max_size(t_ls *stock)
{
	int *max;
	int val;
	struct group *grp;
	t_ls *tmp;
	int k;
	
	k = 0;
	max = malloc(sizeof(int) * 4);
	max = ft_new_int_tab(max);
	tmp = stock;
	while (tmp)
	{
		(tmp->stat.st_nlink > max[0]) ? max[0] = tmp->stat.st_nlink : max[0];
		val = ft_strlen(getpwuid(tmp->stat.st_uid)->pw_name);
		(val > max[1] )? max[1] = val : max[1]; 
		grp = getgrgid(tmp->stat.st_gid);
		val = ((int)ft_strlen(grp->gr_name));
		(val > max[2] )? max[2] = val : max[2];
		((int)tmp->stat.st_size > max[3]) ?  max[3] = (int)tmp->stat.st_size : max[3];
		k = k + tmp->stat.st_blocks;
		tmp = tmp->next;
	}
	max[0] = ft_strlen(ft_itoa(max[0]));
	max[3] = ft_strlen(ft_itoa(max[3]));
	ft_putstr("total ");
	ft_putnbr(k);
	return (max);
}
#include "ls.h"
#include "libft.h"

t_ls *ft_place_elem_according_to_time(t_ls *stock, t_ls *new)
{
	t_ls *check;
	int t1;
	int t2;

	check = stock;
	t1 = check->stat.st_mtimespec.tv_sec;
	t2 = new->stat.st_mtimespec.tv_sec;
	if (t2 >= t1)
	{
		new->next = stock;
		return (stock = new);
	}
	while(check->next &&  t2 <= (t1 = check->next->stat.st_mtimespec.tv_sec))
		check = check->next;
	new->next = check->next;
	check->next = new;
	return (stock);
}

t_ls *ft_place_elem(t_ls *stock, t_ls *new, int time)
{
	t_ls	*check;

	check = stock;
	if (time == 1)
		return (ft_place_elem_according_to_time(stock, new));

	if (ft_strcmp(check->name, new->name) > 0)
	{
		new->next = stock;
		return (stock = new);
	}
	while (check->next && ft_strcmp(check->next->name, new->name) < 0)
		check = check->next;
	new->next = check->next;
	check->next = new;
	return (stock);
}
#include "ls.h"
#include "libft.h"

int	ft_longest_name(t_ls *stock)
{
	int i;
	t_ls *tmp;

	i = 0;
	tmp = stock;
	while (tmp)
	{
		i = ((int)ft_strlen(tmp->name) > i) ? (int)ft_strlen(tmp->name) : i;
		tmp = tmp->next;
	}
	return (i);
}

void ft_print_normal(t_ls *stock)
{
	t_ls *tmp;
	int i;
	int j;

	j = 0;
	i = ft_longest_name(stock);
	tmp = stock;
	while (tmp)
	{
		if (tmp->name)
			ft_putstr(tmp->name);
		j = (int)ft_strlen(tmp->name);
		while (j < i)
		{
			ft_putchar(' ');
			j++;
		}
		ft_putchar(' ');
		tmp = tmp->next;
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
/*   Updated: 2017/07/12 08:41:05 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"
#include <sys/xattr.h>
#include <pwd.h>
#include <time.h>
#include "ls.h"

char	*find_path(char *name, const char *dirname)
{
	char *path;

	path = ft_strjoin((char*)dirname, "/");
	path = ft_strjoin(path, name);
	return (path);
}

static t_ls	*ft_new_elem(char *name, const char *dirname, t_ls *stock, int time)
{
	t_ls *new;
	char *path;

	if (!(name))
		return (stock);
	if (!(new = malloc(sizeof(t_ls))))
		exit (1);
	new->next = NULL;
	new->name = ft_strdup(name);
	path = find_path(name, dirname);
	if (!stock)
	{
		if (lstat(path, &(new->stat)))
		{
			ft_strdel(&path);
			ft_putstr(strerror(errno));
		}
		ft_strdel(&path);
		return (new);
	}
	lstat(path, &(new->stat));
	return (ft_place_elem(stock, new, time));
}

t_ls	*ft_store(char *foldername, DIR *dir, int time)
{
	t_ls	*stock = NULL;
	struct dirent *dent;

	if (dir != NULL)
	{
		while((dir && (dent = readdir(dir))))
			stock = ft_new_elem(dent->d_name, foldername, stock, time);
	}
	return (stock);
}

t_ls  *ft_advance_stock_if_no_a(t_ls *stock, int options)
{
	t_ls *tmp_1;
	t_ls *tmp_2;
	if (!(options & CMD_t))
	{
		while (stock && (stock)->name[0] == '.')
		{
			tmp_1 = (stock)->next;
			free (stock);
			stock = tmp_1;
		}
		return (stock);
	}
	if (stock->name[0] == '.' && stock->next)
		return (ft_advance_stock_if_no_a((stock->next), options));
	tmp_1 = stock;
	while (tmp_1)
	{
		tmp_2 = tmp_1;
		tmp_1 = tmp_1->next;
		if (tmp_1 && tmp_1->name[0] == '.')
		{
			tmp_2->next = tmp_1->next;
			free(tmp_1);
			tmp_1 = tmp_2;
		}
	}
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
/*   Updated: 2017/07/12 08:42:08 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

void	ls(char *name, int options)
{
	t_ls *stock;
	DIR *dir;

	dir = NULL;
	dir = opendir(name);
	stock = (options & CMD_t) ? ft_store(name, dir,  1) : ft_store(name, dir,  0);
	stock = (options & CMD_a) ? stock : ft_advance_stock_if_no_a(stock, options);
	(options & CMD_r) ? ft_CMD_r(&(stock)) : stock;
	(options & CMD_l) ? ft_CMD_l(stock, name) : ft_print_normal(stock);
	if (dir)
		closedir(dir);
	ft_putchar('\n');
	if (options & CMD_R)
		ft_putchar('\n');
	(options & CMD_R) ? ft_CMD_R(stock, name, options) : options;
	//ft_free(&stock);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 14:14:42 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/04 02:47:53 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

static void			ft_print_usage_error(char error);
static int 		ft_stock_commands(char command, int command_options);

static void      ft_send_files_to_ls(char **folder, int command_options)
{
	struct stat *buffstatt;

	if (*folder && !(ft_strcmp(*folder, "--")))
		folder++;
	while (*folder)
	{
		buffstatt = malloc(sizeof(stat));
		if (!(stat(*folder, buffstatt)))
			ls(*folder, command_options);
		//free(buffstatt);
		folder++;
	}
}

static int		ft_check_file_errors(char **folder)
{
	struct stat *buffstatt;

	while (*folder)
	{
		buffstatt = malloc(sizeof(stat));
		if (stat(*folder, buffstatt) == -1)
		{
			ft_putstr("ft_ls: ");
			ft_putstr(*folder);
			ft_putstr(": No such file or directory\n");
			return (1);
		}
		//free(buffstatt);
		folder++;
	}
	return (0);
}


static int				ft_check_usage(char ***av)
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

static int 		ft_stock_commands(char command, int command_options)
{
	if (command == 'l' || command == 'R' || command == 'a'
			|| command == 'r' || command == 't')
	{
		if (command == 'l')
			command_options = command_options | CMD_l;
		if (command == 'R')
			command_options = command_options | CMD_R;
		if (command == 'a')
			command_options = command_options | CMD_a;
		if (command == 'r')
			command_options = command_options | CMD_r;
		if (command == 't')
			command_options = command_options | CMD_t;
	}
	else 
		return (0);
	return (command_options);
}

static void			ft_print_usage_error(char error)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(error);
	ft_putchar('\n');
	ft_putstr("usage: ls [-lRart] [file ...]");
	ft_putchar('\n');
}

int				main(int ac, char **av)
{
	int command_options;

	command_options = 0;
	ac++;
	if ((command_options = ft_check_usage(&av)) == -1)
	{
		ft_print_usage_error(**av);
		return (-1);
	}
	if (*av && !(ft_strcmp(*av, "--")))
		av++;
	if (ft_check_file_errors(av))
		return (-1);
	if (*av)
	{
		ft_send_files_to_ls(av, command_options);
	}
	else
		ls(".", command_options);
	return (0);
}
