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
		lstat(path, &(new->stat));
		return (new);
	}
	lstat(path, &(new->stat));
	return (ft_place_elem(stock, new, time));
}

t_ls	*ft_store(char *foldername, int time)
{
	t_ls	*stock = NULL;
	DIR *dir;
	struct dirent *dent;

	dir = opendir(foldername);
	if (dir != NULL)
	{
		while((dent = readdir(dir)))
			stock = ft_new_elem(dent->d_name, foldername, stock, time);
	}

	closedir(dir);
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
