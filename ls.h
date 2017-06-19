/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 17:14:32 by lazrossi          #+#    #+#             */
/*   Updated: 2017/06/19 18:26:08 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LS_H
# define LS_H

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

typedef struct		s_ls
{
	char			*name;
	struct 			stat stat;
	struct 			s_ls *next;
	
}					t_ls;

#endif
