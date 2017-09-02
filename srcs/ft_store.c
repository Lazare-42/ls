/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 01:51:31 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 05:35:11 by lazrossi         ###   ########.fr       */
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
		return (NULL);
	}
	*max_padding = ft_max_size(new, *max_padding, sort_options);
	if (foldername)
		ft_strdel(&path);
	return (new);
}

int		*ft_store(char *foldername, DIR *dir, int sort_options, t_ls **stock)
{
	struct dirent	*dent;
	t_ls			*new_stock;
	int				*max;

	if (!(max = (int*)ft_memalloc(sizeof(int) * 5)))
		exit(1);
	if (dir != NULL)
	{
		while ((dir && (dent = readdir(dir))))
		{
			(!(sort_options & CMD_A) && dent->d_name[0] == '.') ?
				dent = NULL : 0; 
			if (dent && !(*stock))
			{
				(*stock) = ft_new_elem(dent->d_name, foldername,
						&max, sort_options);
				((*stock)) ? (*stock)->color = 1 : 0;
			}
			else if (dent)
			{
				new_stock = ft_new_elem(dent->d_name, foldername,
						&max, sort_options);
				if (!(ft_place_elem((*stock), new_stock, &max, sort_options)))
					ft_rotate(stock, new_stock, sort_options);
			}
		}
	}
	else
		(*stock) = ft_new_elem(foldername, NULL, &max, sort_options);
	return (max);
}
