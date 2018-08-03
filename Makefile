# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dewalter <dewalter@le-101.fr>              +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/02/22 01:51:44 by dewalter     #+#   ##    ##    #+#        #
#    Updated: 2018/08/01 10:17:28 by dewalter    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all re clean fclean

NAME = 42sh

HEADER = stdin.h \

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a
LIBFT_INC = -L $(LIBFT_PATH) -lft
INCLUDE = -I ./includes/ -I $(LIBFT_PATH)includes

CC = gcc

COLOR = echo

CC_FLAGS = -Wall -Werror -Wextra -g

SRC =		main.c \
			get_stdin.c \
			prompt.c \
			signal.c \
			find_env_var.c \
			cursor_position.c \
			backspace.c \
			clear_window.c \
			escape_sequence.c \
			go_to_begin_of_line.c \
			go_to_end_of_line.c \
			move_cursor_up.c \
			move_cursor_down.c \
			move_cursor_left.c \
			move_cursor_right.c \
			move_word_left.c \
			move_word_right.c \
			end_of_text.c \
			add_char.c \
			delete_from_cursor_to_end.c \
			paste_clipboard.c \
			tabulator.c \
			historic.c \

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
