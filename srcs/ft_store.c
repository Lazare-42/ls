/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 01:51:31 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/26 14:35:53 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/xattr.h>
#include <pwd.h>
#include <time.h>
#include "ls.h"

char	*find_path(char *name, const char *foldername)
{
	char *path;

	path = ft_strjoin((char*)foldername, "/");
	path = ft_strjoinfree(&path, &name, 'L');
	return (path);
}
void	ft_print_errors(char *name)
{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
}

static t_ls	*ft_new_elem(char *name, const char *foldername, t_ls *stock, int time)
{
	t_ls *new;
	char *path;

	if (!(name))
		return (stock);
	if (!(new = malloc(sizeof(t_ls))))
		return (NULL);
	new->next = NULL;
	new->name = ft_strdup(name);
	if (foldername)
		path = find_path(name, foldername);
	else
		path = name;
	if (lstat(path, &(new->stat)))
	{
		ft_strdel(&path);
		ft_print_errors(new->name);
		return (NULL);
	}
	if (foldername)
	{
		ft_strdel(&path);
		return (ft_place_elem(stock, new, time));
	}
	return (new);
}

t_ls	*ft_store(char *foldername, DIR *dir, int time)
{
	t_ls			*stock;
	struct dirent 	*dent;

	stock = NULL;
	if (dir != NULL)
	{
		while ((dir && (dent = readdir(dir))))
		{
			if (!(time & CMD_a) && dent->d_name[0] == '.')
				dent = NULL;
			if (dent)
				stock = ft_new_elem(dent->d_name, foldername, stock, time);
		}
	}
	else
		stock = ft_new_elem(foldername, NULL, stock, time); 
	return (stock);
}
