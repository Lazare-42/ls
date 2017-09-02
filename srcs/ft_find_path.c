/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:43:36 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/02 17:22:48 by lazrossi         ###   ########.fr       */
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
