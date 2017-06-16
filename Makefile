NAME = ft_ls

NAME_LIB = libft/libft.a

SRC_LIB = ./libft/

SRC_LS = ./test.c

OBJECTS_LS = $(SRC_LS:.c=.o)

all : $(NAME_LIB) $(NAME)

$(NAME_LIB): 
	cd ./libft/	$(MAKE) Makefile

$(NAME): $(OBJECTS_LS) $(NAME_LIB)
	gcc -Wall -Werror -Wextra -o $(NAME) -I libft/libft.a $(OBJECTS_LS) 

%.o: %.c
	gcc -c -Wall -Wextra -Werror -o $@ $^

clean:
	rm -f $(OBJECTS_LS)
	make clean ./libft/

fclean: clean
	rm -f $(NAME)
	rm -f $(OBJECTS_LS)

re: fclean all
	

