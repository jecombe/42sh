# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/24 18:33:54 by dzonda       #+#   ##    ##    #+#        #
#    Updated: 2018/10/02 04:04:38 by dzonda      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all re clean fclean lib

NAME = 101sh

MAKE = make
CC = gcc
CFLAGS = -Wall -Werror -Wextra
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
			editor/ft_putfreshstr.c \
			editor/find_env_var.c \
			editor/prompt_git.c \
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
			lexer/lexer.c \
			lexer/lexer_break_words.c \
			lexer/lexer_utils.c \
			parser/attrib_parsing.c \
			parser/convert_token.c \
			parser/free_parse.c \
			parser/parse_error.c \
			parser/malloc_parsing.c \
			parser/manage_parsing.c \
			parser/parsing.c \
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
			execute/loop_redirections.c \
			execute/sequences.c \
			execute/open_file_redirections.c \
			execute/return_flag_redirections.c \
			execute/return_command.c \
			execute/heredoc.c \
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
			builtins/export.c \
			builtins/ft_assign.c \
			builtins/hash.c \
			builtins/hash_utils.c \
			builtins/history.c	\
			builtins/history_utils.c \
			builtins/ft_read.c	\
			builtins/ft_read_utils.c

OBJS_FOLDERS = 	\
				heart init editor ft_select lexer parser extension execute \
				builtins

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))
OBJS = $(addprefix $(OBJS_PATH),$(OBJS_NAME))
OBJS_FOLDERS_BIS = $(addprefix $(OBJS_PATH),$(OBJS_FOLDERS))

NB_FILES = $(words $(SRCS_NAME))

all: $(NAME)

$(NAME): lib $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS)
	@echo "\033[1;32m[ $(NAME) ] Compiled\033[0m"

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJS_PATH) $(OBJS_FOLDERS_BIS) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@$(eval CURSOR=$(shell echo $$(($(CURSOR) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(CURSOR) * 100 / $(NB_FILES)))))
	@if [ $(CURSOR) != 1 ]; then\
		(printf "\e[?25l" && printf "\033[1A");\
		fi # hide cursor & move up except first time
	@echo "\033[93m[ $(NAME) ] Compiling: \033[0m\033[1m[$(PERCENT)%] \033[0m$@                       "
	@printf "\e[?25h" #show cursor

val:
	@$(shell echo "#false positive for any executable (it seems) \
	# macOS 10.12.6 \
	# valgrind 3.13.0 \
	{ \
		libtrace initialization false positive \
		Memcheck:Param \
		msg->desc.port.name \
		fun:mach_msg_trap \
		fun:mach_msg \
		fun:task_set_special_port \
		fun:_os_trace_create_debug_control_port \
		fun:_libtrace_init \
	}" > $HOME/.valgrind.supp)
	valgrind --suppressions=${HOME}/.valgrind.supp --leak-check=full --track-origins=yes ./a.out
	#valgrind --leak-check=full --track-origins=yes ./a.out

valgrind: lldb
	valgrind --leak-check=full --track-origins=yes ./a.out

lldb:
	gcc -ggdb3 src/*/*.c libft/src/*.c -I include -I libft/include -ltermcap

lib:
	@make -C $(LIB_PATH)

clean:
	@$(MAKE) -C $(LIB_PATH) clean
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIB_PATH) fclean
	@$(RM) $(NAME)
	@rm -rf a.out
	@echo "\033[1;31m[ $(NAME) ] deleted\033[0m"
	@rm -rf obj

re: fclean all
