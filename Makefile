# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lazrossi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/26 20:03:26 by lazrossi          #+#    #+#              #
#    Updated: 2017/07/26 20:20:52 by lazrossi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ft_CMD_r.c ft_free.c ft_list_reverse.c ft_place_element.c ft_print_normal.c ft_store.c ls.c main.c ft_CMD_l.c ft_padding.c

OBJECT = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C libft/ 
	gcc -Wall -Wextra -Werror -I libft -c $(SRC)
	gcc -Wall -Wextra -Werror -I libft $(OBJECT) -L libft -lft -o $(NAME)


