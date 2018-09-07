# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dewalter <dewalter@le-101.fr>              +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/02/22 01:51:44 by dewalter     #+#   ##    ##    #+#        #
#    Updated: 2018/08/31 22:51:48 by dewalter    ###    #+. /#+    ###.fr      #
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

SRC_NAME =		editor/main.c \
				editor/get_stdin.c \
				editor/prompt.c \
				editor/signal.c \
				editor/cursor_position.c \
				editor/backspace.c \
				editor/clear_window.c \
				editor/escape_sequence.c \
				editor/go_to_begin_of_line.c \
				editor/go_to_end_of_line.c \
				editor/move_cursor_up.c \
				editor/move_cursor_down.c \
				editor/move_cursor_left.c \
				editor/move_cursor_right.c \
				editor/move_word_left.c \
				editor/move_word_right.c \
				editor/end_of_text.c \
				editor/add_char.c \
				editor/delete_from_cursor_to_end.c \
				editor/paste_clipboard.c \
				editor/tabulator.c \
				editor/historic.c \
				editor/term_init.c \
				editor/find_env_var.c \
				\
				ft_select/ft_arrows.c \
				ft_select/ft_char_by_line.c \
				ft_select/ft_count_line.c \
				ft_select/ft_count_params.c \
				ft_select/ft_disable_raw.c \
				ft_select/ft_enable_raw.c \
				ft_select/ft_error.c \
				ft_select/ft_first_sort.c \
				ft_select/ft_free_t_select.c \
				ft_select/ft_get_size_term.c \
				ft_select/ft_init_select.c \
				ft_select/ft_is_file.c \
				ft_select/ft_manage_entry.c \
				ft_select/ft_manage_touch.c \
				ft_select/ft_outc.c \
				ft_select/ft_params_by_line.c \
				ft_select/ft_prepare_print.c \
				ft_select/ft_print_params.c \
				ft_select/ft_read_entry.c \
				ft_select/ft_save_raw_off.c \
				ft_select/ft_save_shell.c \
				ft_select/ft_search_big_param.c \
				ft_select/ft_searchdyn.c \
				ft_select/ft_select.c \
				ft_select/ft_select_sp.c \

OBJ = $(addprefix $(OBJ_PATH), $(SRC_NAME:.c=.o))
OBJ_FOLDERS = editor ft_select
OBJ_FOLDERS_BIS = $(addprefix $(OBJ_PATH), $(OBJ_FOLDERS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CC_FLAGS) $(OBJ) -L $(LIBFT_PATH) -lft -o $(NAME) -lncurses
	@ printf "\033[1mCompilation du projet \033[34m%-16s$@\033[0m \033[1men \033[31m%-17s$@\033[0m ✅\n"

$(LIBFT):
	mkdir -p $(OBJ_FOLDERS_BIS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c ./includes/$(HEADER)
	@mkdir -p $(OBJ_PATH) $(OBJ_FOLDERS_BIS)
	@ $(CC) $(CC_FLAGS) $(INCLUDE) -o $@ -c $<
	@ printf "\033[1mCompilation de \033[36m%-25s\033[37m\ten \033[32m%-26s\033[0m ✅\n" $< $@

clean:
	@/bin/rm -rf $(OBJ_PATH)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all
