/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 19:08:21 by lazrossi          #+#    #+#             */
/*   Updated: 2017/06/21 17:20:21 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

int ft_print_normal(t_ls **stock);

int	ft_store(char *foldername, t_ls	*(*stock))
{
	DIR *dir;
	struct dirent *dent;
	dir = opendir(foldername);
	t_ls *tmp;

	if(dir != NULL)
	{
		while((dent = readdir(dir)) != NULL)
		{
			if (!(stock))
			{
				(*stock) = malloc(sizeof(t_ls));
				((*stock))->next = NULL;
			}
			else 
			{
				tmp = malloc(sizeof(t_ls));
				tmp->next = (*stock);
				(*stock) = tmp;
			}
			((*stock))->name = ft_strnew(ft_strlen(dent->d_name));
			((*stock))->name = ft_strdup(dent->d_name);
			stat(((*stock))->name, &(((*stock))->stat));
		}
		if (closedir(dir))
			return (-1);
	}
	while (!(ft_print_normal(stock)))
		ft_print_normal(stock);
	return (0);
}

int ft_print_normal(t_ls **stock)
{
	if((strcmp((*stock)->name,".")==0 || strcmp((*stock)->name,"..")==0 || (*(*stock)->name) == '.' ))
	{
	}
	else 
		printf("%s\n", ((*stock))->name);
	(*stock) = ((*stock))->next;
	if (*stock && (*stock)->next)
		return (0);
	if ((*stock) && (!(strcmp((*stock)->name,".")==0 || strcmp((*stock)->name,"..")==0 || (*(*stock)->name) == '.' )))
		printf("%s\n", ((*stock))->name);
	return (1);
}

int main()
{
	t_ls (**stock) = NULL;
	ft_store(".", stock);
	if (!(stock))
		printf("%s\n", "coucou");
	while (*stock && (*stock)->next)
	{
		printf("%s\n", "coucou");

		if (S_ISDIR((*stock)->stat.st_mode) && (!(strcmp((*stock)->name,".")==0 || strcmp((*stock)->name,"..")==0 || (*(*stock)->name) == '.' )))
			ft_store((*stock)->name, stock);
		*stock = (*stock)->next;

	}
	return (0);
}
