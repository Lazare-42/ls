NAME = ft_ls

SOURCES = ./ft_cmd_g.c \
./ft_cmd_l.c \
./ft_cmd_one.c \
./ft_cmd_recurs.c \
./ft_find_path.c \
./ft_padding.c \
./ft_parsing.c \
./ft_place_element.c \
./ft_print_errors.c \
./ft_print_info.c \
./ft_print_info2.c \
./ft_print_normal.c \
./ft_store.c \
./ls.c \
./main.c \
./rotate.c 

LIBDIR = libft
SDIR = srcs
CFLAGS = -Wall -Wextra -Werror
INCDIR = includes
LDFLAGS = -L$(LIBDIR) -lft
CC = clang
SRCS = $(addprefix $(SDIR)/, $(SOURCES:.c=.c))
OBJS = $(addprefix $(SDIR)/, $(SOURCES:.c=.o))
OK = echo "[32m OK ✓ [0m"

all: lib $(NAME)

lib:
	@echo "Compiling libft ..."
	@-make -C $(LIBDIR)
	@$(OK)

$(NAME): $(OBJS)
	@echo "Compiling  ..."
	@-$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(INCDIR) $(LDFLAGS)
	@$(OK)

clean:
	@/bin/rm -rf $(SDIR)
	@make -C $(LIBDIR) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all
