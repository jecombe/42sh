# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/24 18:33:54 by dzonda       #+#   ##    ##    #+#        #
#    Updated: 2018/09/21 17:22:54 by jecombe     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all re clean fclean lib

NAME = 101sh

MAKE = make
CC = gcc
CFLAGS = #-Wall -Werror -Wextra
CPPFLAGS = -I ./include/
LDLIBS = -lft -ltermcap
LDFLAGS = -Llibft/
RM = rm -f

SRCS_PATH = ./src/
OBJS_PATH = ./obj/
INCS_PATH = ./include/
LIB_PATH = ./libft/

SRCS_NAME =	\
			heart/42sh.c \
			heart/signal.c \
			heart/42sh_exit.c \
			init/init_shell.c \
			init/init_files.c \
			init/init_env.c \
			init/init_set.c \
			init/init_builtins.c \
			init/envset_add.c \
			init/utils.c \
			init/envset_manage.c \
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
			editor/term_historic.c \
			editor/term_init.c \
			editor/find_env_var.c \
			ft_select/ft_arrows.c \
			ft_select/ft_char_by_line.c \
			ft_select/ft_count_line.c \
			ft_select/ft_count_params.c \
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
			ft_select/ft_select.c \
			ft_select/tabulator.c \
			ft_select/ft_tabsplit.c \
			ft_select/utils.c \
			ft_select/ft_select_sp.c \
			lexer/prelexer.c \
			lexer/ft_lexer.c \
			lexer/ft_lexer_break_words.c \
			lexer/ft_lexer_utils.c \
			parser/ft_attrib_parsing.c \
			parser/ft_convert_token.c \
			parser/ft_free_parse.c \
			parser/parse_error.c \
			parser/ft_malloc_parsing.c \
			parser/ft_manage_parsing.c \
			parser/ft_parsing.c \
			parser/manage_assign.c \
			extension/extension_error.c \
			extension/quotes_manager.c \
			extension/add_tild.c \
			extension/extension.c \
			extension/bquote_manager.c \
			extension/backslash_manager.c \
			extension/ft_split_b_quote.c \
			extension/ft_dollar.c \
			extension/bquote_ext1.c \
			extension/bquote_ext2.c \
			extension/ft_free_n_seq.c \
			extension/ft_free_n_op.c \
			extension/ft_free_n_redirect.c \
			execute/binary.c \
			execute/binary_signal.c \
			execute/solver.c \
			execute/utils.c \
			execute/check_command.c \
			execute/sequences.c \
			execute/separate.c \
			execute/open_file_redirections.c \
			execute/return_flag_redirections.c \
			execute/heredoc.c \
			execute/init_struct.c \
			builtins/builtins.c \
			builtins/builtins_errors.c \
			builtins/ft_env_tools.c \
			builtins/ft_env.c \
			builtins/ft_setenv.c \
			builtins/ft_unsetenv.c \
			builtins/ft_cd.c \
			builtins/ft_cd_utils.c \
			builtins/echo.c \
			builtins/exit.c \
			builtins/unset.c \
			builtins/set.c \
			builtins/ft_export.c \
			builtins/ft_assign.c \
			builtins/ft_hash.c \
			builtins/ft_hash_utils.c \
			builtins/history.c

OBJS_FOLDERS = 	\
				heart init editor ft_select lexer parser extension execute \
				builtins

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))
OBJS = $(addprefix $(OBJS_PATH),$(OBJS_NAME))
OBJS_FOLDERS_BIS = $(addprefix $(OBJS_PATH),$(OBJS_FOLDERS))

all: $(NAME)

$(NAME): lib $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS)
	@echo "\033[1;32m[ $(NAME) ] Compiled\033[0m"

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJS_PATH) $(OBJS_FOLDERS_BIS) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@echo "\033[1m[ $@ ] Compiled\033[0m"
	@echo "\033[2A"
	@echo "\033[K"
	@echo "\033[2A"

lib:
	@make -C $(LIB_PATH)

clean:
	@$(MAKE) -C $(LIB_PATH) clean
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIB_PATH) fclean
	@$(RM) $(NAME)
	@echo "\033[1;31m[ $(NAME) ] deleted\033[0m"
	@rm -rf obj

re: fclean all
