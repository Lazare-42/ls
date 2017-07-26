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

char	*find_path(char *name, const char *foldername)
{
	char *path;

	path = ft_strjoin((char*)foldername, "/");
	path = ft_strjoinfree(&path, &name, 'L');
	return (path);
}

static t_ls	*ft_new_elem(char *name, const char *foldername, t_ls *stock, int time)
{
	t_ls *new;
	char *path;

	if (!(name))
		return (stock);
	if (!(new = malloc(sizeof(t_ls))))
		exit (1);
	new->next = NULL;
	new->name = ft_strdup(name);
	path = find_path(name, foldername);
	if (lstat(path, &(new->stat)))
	{
		ft_strdel(&path);
		ft_putstr(strerror(errno));
	}
	ft_strdel(&path);
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
