# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dewalter <dewalter@le-101.fr>              +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/02/22 01:51:44 by dewalter     #+#   ##    ##    #+#        #
#    Updated: 2018/06/06 21:57:55 by dewalter    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all re clean fclean

NAME = 21sh

HEADER = shell.h \
#		 stdin.h \

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a
LIBFT_INC = -L $(LIBFT_PATH) -lft
INCLUDE = -I ./includes/ -I $(LIBFT_PATH)includes

CC = gcc

COLOR = echo

CC_FLAGS = -Wall -Werror -Wextra

SRC =		main.c \
			shell.c \
			get_stdin.c \
			prompt.c \
			signal.c \
			find_env_var.c \
			cursor_position.c \

OBJ = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CC_FLAGS) $(OBJ) -L $(LIBFT_PATH) -lft -o $(NAME) -lncurses
	@ printf "\033[1mCompilation du projet \033[34m%-16s$@\033[0m \033[1men \033[31m%-17s$@\033[0m ✅\n"

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c ./includes/$(HEADER)
	@mkdir -p $(OBJ_PATH)
	@ $(CC) $(CC_FLAGS) $(INCLUDE) -o $@ -c $<
	@ printf "\033[1mCompilation de \033[36m%-25s\033[37m\ten \033[32m%-26s\033[0m ✅\n" $< $@

clean:
	@/bin/rm -rf $(OBJ_PATH)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all
