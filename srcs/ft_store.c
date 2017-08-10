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

static t_ls	*ft_new_elem(char *name, const char *foldername, t_ls *stock, int sort_options)
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
		path = find_path(name, (char*)foldername);
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
		return (ft_place_elem(stock, new, sort_options));
	}
	return (new);
}

t_ls	*ft_store(char *foldername, DIR *dir, int sort_options)
{
	t_ls			*stock;
	struct dirent 	*dent;

	stock = NULL;
	if (dir != NULL)
	{
		while ((dir && (dent = readdir(dir))))
		{
			if (!(sort_options & CMD_a) && dent->d_name[0] == '.')
				dent = NULL;
			if (dent)
				stock = ft_new_elem(dent->d_name, foldername, stock, sort_options);
		}
	}
	else
		stock = ft_new_elem(foldername, NULL, stock, sort_options); 
	return (stock);
}
