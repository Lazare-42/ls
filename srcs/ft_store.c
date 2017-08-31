/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 01:51:31 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/31 01:47:31 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <sys/xattr.h>
#include <pwd.h>
#include <time.h>
#include "ls.h"

t_ls		*ft_new_elem(char *name, const char *foldername, int **max_padding, int sort_options)
{
	t_ls *new;
	char *path;

	if (!(name))
		return (NULL);
	if (!(new = malloc(sizeof(t_ls))))
		return (NULL);
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
		return (NULL);
	}
	*max_padding = ft_max_size(new, *max_padding, sort_options);
	if (foldername)
		ft_strdel(&path);
	return (new);
}

int		*ft_new_int_tab(int *new)
{
	new[0] = 0;
	new[1] = 0;
	new[2] = 0;
	new[3] = 0;
	new[4] = 0;
	return (new);
}

int *ft_store(char *foldername, DIR *dir, int sort_options, t_ls **stock)
{
	struct dirent	*dent;
	int				*max;

	max = malloc(sizeof(int) * 5);
	max = ft_new_int_tab(max);
	if (dir != NULL)
	{
		while ((dir && (dent = readdir(dir))))
		{
			if (!(sort_options & CMD_A) && dent->d_name[0] == '.')
				dent = NULL;
			if (dent && !(*stock))
			{
				(*stock) = ft_new_elem(dent->d_name, foldername, &max, sort_options);
				((*stock)) ? (*stock)->color = 1 : 0;
			}
			else if (dent)
			{
				if (!ft_place_elem((*stock), dent->d_name, foldername, &max, sort_options))
					ft_rotate(&(*stock), dent->d_name, foldername);
			}
		}
	}
	else
		(*stock) =	ft_new_elem(NULL, foldername, &max, sort_options);
	return (max);
}
