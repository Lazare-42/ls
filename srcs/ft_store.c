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

t_ls		*ft_new_elem(char *name, const char *foldername)
{
	t_ls *new;
	char *path;

	if (!(name))
		return (NULL);
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
		ft_strdel(&path);
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
				stock = ft_place_elem(&stock, dent->d_name, foldername);
		}
	}
	else
		stock = ft_place_elem(&stock, NULL, foldername);
	return (stock);
}
