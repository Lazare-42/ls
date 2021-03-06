/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isalpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 16:31:25 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/28 16:31:28 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

int	ft_str_isalpha(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}
