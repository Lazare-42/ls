/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_place_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 13:55:44 by lazrossi          #+#    #+#             */
/*   Updated: 2017/08/10 16:46:34 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_ls	*ft_place_elem_according_to_last_modif(t_ls *stock, t_ls *new)
{
	t_ls	*check;
	int		t1;
	int		t2;

	check = stock;
	t1 = check->stat.st_mtimespec.tv_sec;
	t2 = new->stat.st_mtimespec.tv_sec;
	if (t2 >= t1)
	{
		new->next = stock;
		return (stock = new);
	}
	while (check->next && t2 <= (t1 = check->next->stat.st_mtimespec.tv_sec))
		check = check->next;
	new->next = check->next;
	check->next = new;
	return (stock);
}

t_ls	*ft_place_elem_according_to_last_access(t_ls *stock, t_ls *new)
{
	t_ls	*check;
	int		t1;
	int		t2;

	check = stock;
	t1 = check->stat.st_atimespec.tv_sec;
	t2 = new->stat.st_atimespec.tv_sec;
	if (t2 >= t1)
	{
		new->next = stock;
		return (stock = new);
	}
	while (check->next && t2 <= (t1 = check->next->stat.st_atimespec.tv_sec))
		check = check->next;
	new->next = check->next;
	check->next = new;
	return (stock);
}

t_ls	*ft_place_elem_according_to_creation(t_ls *stock, t_ls *new)
{
	t_ls	*check;
	int		t1;
	int		t2;

	check = stock;
	t1 = check->stat.st_birthtimespec.tv_sec;
	t2 = new->stat.st_birthtimespec.tv_sec;
	if (t2 >= t1)
	{
		new->next = stock;
		return (stock = new);
	}
	while (check->next && t2 <=
			(t1 = check->next->stat.st_birthtimespec.tv_sec))
		check = check->next;
	new->next = check->next;
	check->next = new;
	return (stock);
}

t_ls	*ft_place_elem_according_to_size(t_ls *stock, t_ls *new)
{
	t_ls	*check;
	int		t1;
	int		t2;

	check = stock;
	t1 = check->stat.st_size;
	t2 = new->stat.st_size;
	if (t2 >= t1)
	{
		new->next = stock;
		return (stock = new);
	}
	while (check->next && t2 <= (t1 = check->next->stat.st_size))
		check = check->next;
	new->next = check->next;
	check->next = new;
	return (stock);
}

t_ls	*ft_place_elem(t_ls *stock, t_ls *new, int sort_options)
{
	t_ls	*check;

	check = stock;
	if (!(stock))
		return (stock = new);
	if (sort_options & CMD_T)
		return (ft_place_elem_according_to_last_modif(stock, new));
	else if (sort_options & CMD_LAST_ACCESS)
		return (ft_place_elem_according_to_last_access(stock, new));
	else if (sort_options & CMD_S)
		return (ft_place_elem_according_to_size(stock, new));
	else if (sort_options & CMD_U)
		return (ft_place_elem_according_to_creation(stock, new));
	if (ft_strcmp(check->name, new->name) > 0)
	{
		new->next = stock;
		return (stock = new);
	}
	while (check->next && ft_strcmp(check->next->name, new->name) < 0)
		check = check->next;
	new->next = check->next;
	check->next = new;
	return (stock);
}
