/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 01:51:31 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/10 14:42:13 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"
#include <sys/xattr.h>
#include <pwd.h>
#include <time.h>
#include "ls.h"

static t_ls	*ft_new_elem(char *name, const char *dirname, t_ls *stock)
{
	t_ls *new;
	char *path;

	if (!(name))
		return (stock);
	if (!(new = malloc(sizeof(t_ls))))
		exit (1);
	new->name = ft_strdup(name);
	path = ft_strjoin((char*)dirname, "/");
	path = ft_strjoin(path, name);
	if (!stock)
	{
		stat(path, &(new->stat));
		return (new);
	}
	return (ft_place_elem(path, stock, new));
}

t_ls	*ft_store(char *foldername)
{
	t_ls	*stock = NULL;
	DIR *dir;
	struct dirent *dent;

	dir = opendir(foldername);
	if (dir != NULL)
	{
		while((dent = readdir(dir)))
		{
			if (dent)
				stock = ft_new_elem(dent->d_name, foldername, stock);
		}
	}
	closedir(dir);
	return (stock);
}

void ft_advance_stock_if_no_a(t_ls **stock)
{
	t_ls *tmp;
	while (*stock && (*stock)->name[0] == '.')
	{
		tmp = (*stock)->next;
	//	free (*stock);
		*stock = tmp;
	}
}

