/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 09:29:17 by lazrossi          #+#    #+#             */
/*   Updated: 2017/09/06 12:44:47 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"
#include <stdlib.h>

void	ft_tabdel(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_memdel((void**)&str[i]);
		i++;
	}
	ft_memdel((void**)&str);
}
