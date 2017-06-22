/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 19:08:21 by lazrossi          #+#    #+#             */
/*   Updated: 2017/06/22 17:15:05 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

int ft_print_normal(t_ls *stock);

t_ls	*ft_store(char *foldername, t_ls	*stock)
{
	DIR *dir;
	struct dirent *dent;
	dir = opendir(foldername);
	t_ls *tmp;

	if(dir != NULL)
	{
		while((dent = readdir(dir)) != NULL)
		{
			if (!stock)
			{
				stock = malloc(sizeof(t_ls));
				(stock)->next = NULL;
			}
			else 
			{
				tmp = malloc(sizeof(t_ls));
				tmp->next = stock;
				stock = tmp;
			}
			(stock)->name = ft_strnew(ft_strlen(dent->d_name));
			(stock)->name = ft_strdup(dent->d_name);
			stat(stock->name, &(stock->stat));
		}
		if (closedir(dir))
			return (NULL);
	}
	 ft_print_normal(stock);
	return (stock);
}

int ft_print_normal(t_ls *stock)
{
	while (stock && stock->next)
	{
		if((strcmp(stock->name,".")==0 || strcmp(stock->name,"..")==0 || (*stock->name) == '.' ))
		{
		}
		else 
			printf("%s\n", stock->name);
		stock = stock->next;
	}
	return (1);
}

int main()
{
	t_ls *stock = NULL;
	t_ls *new = NULL;
	stock = ft_store(".", stock);
	while (stock)
	{
	  if ( S_ISDIR(stock->stat.st_mode) && (!(strcmp(stock->name,".")==0 || strcmp(stock->name,"..")==0 || (*stock->name) == '.' )))
		return (ft_store(stock->name, new));
	  if (stock->next)
		  stock = stock->next;
	  else
		  break;
	}
	return (0);
}
