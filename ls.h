/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 17:14:32 by lazrossi          #+#    #+#             */
/*   Updated: 2017/06/28 17:56:46 by lazrossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LS_H
# define LS_H

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <stdlib.h>

#define CMD_l 1
#define CMD_R 2
#define CMD_a 4
#define CMD_r 8
#define CMD_t 16
#define ERROR 8000

void	ft_ls(char *foldername, int options);
void	ls(char *name);

typedef struct		s_ls
{
	char			*name;
	struct 			stat stat;
	struct 			s_ls *next;
}					t_ls;

#endif
