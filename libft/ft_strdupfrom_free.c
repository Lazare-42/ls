/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupfrom_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 00:41:20 by lazrossi          #+#    #+#             */
/*   Updated: 2017/12/21 01:28:18 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "include/libft.h"

char	*ft_strdupfrom_free(const char **src, int from)
{
	char	*str;

	str = ft_strdup(&(*src)[from]);
	ft_memdel((void**)src);
	return (str);
}
