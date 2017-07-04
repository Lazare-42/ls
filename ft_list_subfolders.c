/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_subfolders.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 03:06:57 by lazrossi          #+#    #+#             */
/*   Updated: 2017/07/04 03:07:19 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_list_subfolders(char *name, t_ls *stock, int options)
{
	char *dir;

	while (stock)
	{
		if (S_ISDIR(stock->stat.st_mode) && (!(strcmp(stock->name,".") == 0 || strcmp(stock->name,"..") == 0 || (*stock->name) == '.' )))
		{
			dir = ft_strjoin(ft_strjoin(name, "/"), (stock->name));
			ls(dir, options);
			return (1);
		}
		stock = stock->next;
	}
	return (0);
}
