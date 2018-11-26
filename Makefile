# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/24 18:33:54 by dzonda       #+#   ##    ##    #+#        #
#    Updated: 2018/11/25 16:33:03 by gmadec      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all re clean fclean lib

NAME = 42sh

MAKE = make
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wunused -Wunreachable-code
CPPFLAGS = -I ./include/
LDLIBS = -lft -ltermcap
LDFLAGS = -Llibft/
RM = rm -f

SRCS_PATH = ./src/
OBJS_PATH = ./obj/
INCS_PATH = ./include/
LIB_PATH = ./libft/

SRCS_NAME =	\
			heart/sh42.c \
			heart/signal.c \
			heart/sh42_exit.c \
			init/init_shell.c \
			init/init_files.c \
			init/init_env.c \
			init/init_set.c \
			init/init_builtins.c \
			init/envset_add.c \
			init/utils.c \
			init/envset_manage.c \
			ft_select/ft_arrows.c \
			ft_select/ft_lex_tab.c \
			ft_select/ft_manage_count.c \
			ft_select/ft_first_sort.c \
			ft_select/ft_free_t_select.c \
			ft_select/ft_init_select.c \
			ft_select/ft_is_file.c \
			ft_select/ft_manage_touch.c \
			ft_select/ft_params_by_line.c \
			ft_select/ft_prepare_print.c \
			ft_select/ft_tab_manage_path.c \
			ft_select/ft_print_params.c \
			ft_select/ft_search_big_param.c \
			ft_select/ft_search_tab.c \
			ft_select/ft_select.c \
			ft_select/tabulator.c \
			ft_select/ft_manage_cursor_tab.c \
			ft_select/ft_manage_tab.c \
			ft_select/ft_tabsplit.c \
			ft_select/utils.c \
			lexer/prelexer.c \
			lexer/lexer.c \
			lexer/lexer_break_words.c \
			lexer/lexer_break_sub.c \
			lexer/lexer_utils.c \
			parser/attrib_parsing.c \
			parser/convert_token.c \
			parser/free_parse.c \
			parser/parse_error.c \
			parser/malloc_parsing.c \
			parser/manage_parsing.c \
			parser/parsing.c \
			extension/extension_error.c \
			extension/quotes_manager.c \
			extension/add_tild.c \
			extension/subshell_manager.c \
			extension/extension.c \
			extension/dollar_sub.c \
			extension/bquote_manager.c \
			extension/backslash_manager.c \
			extension/ft_split_b_quote.c \
			extension/ft_dollar.c \
			extension/bquote_ext1.c \
			extension/bquote_ext2.c \
			extension/ft_free_n_seq.c \
			extension/ft_free_n_op.c \
			extension/ft_free_n_redirect.c \
			extension/utils_parcour_tab.c \
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
			execute/manage_loop_fd.c \
			execute/execute.c \
			execute/check_file_directory.c \
			builtins/builtins.c \
			builtins/builtins_errors.c \
			builtins/ft_env_tools.c \
			builtins/ft_env.c \
			builtins/ft_setenv.c \
			builtins/ft_unsetenv.c \
			builtins/ft_cd.c \
			builtins/echo.c \
			builtins/exit.c \
			builtins/unset.c \
			builtins/set.c \
			builtins/export.c \
			builtins/hash.c \
			builtins/hash_utils.c \
			builtins/history.c	\
			builtins/history_utils.c \
			builtins/ft_read.c	\
			builtins/ft_read_utils.c \
			line_edition/prompt.c \
			line_edition/prompt_git.c \
			line_edition/init_term.c \
			line_edition/get_user_input.c \
			line_edition/ft_putfreshstr.c \
			line_edition/utils_tab_and_hist.c \
			line_edition/ft_inputs.c \
			line_edition/ft_inputs_arrows.c \
			line_edition/ft_inputs_ctrl.c \
			line_edition/ft_inputs_del.c \
			line_edition/utils.c \
			line_edition/ft_cmd_split.c \
			line_edition/cursor.c

OBJS_FOLDERS = 	\
				heart init ft_select lexer parser extension execute builtins \
				line_edition

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))
OBJS = $(addprefix $(OBJS_PATH),$(OBJS_NAME))
OBJS_FOLDERS_BIS = $(addprefix $(OBJS_PATH),$(OBJS_FOLDERS))

NB_FILES = $(words $(SRCS_NAME))
SHELL = /bin/bash # just because sh print -n from echo
COLS = $(shell tput cols)
DEL_DSYMFILE = $(shell [ -e a.out.dSYM ] && echo rm -rf a.out.dSYM)

all: $(NAME)

$(NAME): init lib $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS)
	@printf "\e[?25h"	# set cursor to visible
	@tput setaf 10 	# set green color
	@tput bold
	@$(eval CURSOR := $(if $(CURSOR),$(CURSOR),0)) # is CURSOR var set ?
	@echo -n "[ $(NAME)    ] Compiled $(CURSOR)/$(NB_FILES) files."
	@tput sgr0 	# reset color
	@tput el 	# clear from cursor to end of line
	@echo ""
	@tput el 	# clear from cursor to end of line

init:
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@tput cuu 4

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(eval CURSOR=$(shell echo $$(($(CURSOR) + 1))))
	@$(eval PERCENT=$(shell printf "[%3d/%3d - \e[1m\e[93m%3d%%\e[0m]" $(CURSOR) $(NB_FILES) $$(($(CURSOR) * 100 / $(NB_FILES)))))
	@$(eval LOADSIZE=$(shell echo $$(($(CURSOR) * $(COLS) / $(NB_FILES)))))
	@printf "\e[?25l\e[s\e[35m\e[44m"
	@tput setaf $$((($(CURSOR)%7)+9))
	@number=1 ; while [[ $$i -le $(LOADSIZE)-1 ]] ; do \
        	printf "▌" ; \
        	((i = i + 1)) ; \
    	done
	@printf "\e[0K\e[0m\n\e[1m\e[93m"
	@echo -n "[ $(NAME) ] Compiling: "
	@printf "\e[0m"			# reset color
	@echo -n "$(PERCENT) $@"
	@printf "\e[0K\n\e[u\e[?25h"
	@mkdir $(OBJS_PATH) $(OBJS_FOLDERS_BIS) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

val: lldb
	valgrind --suppressions=.valgrind.supp --leak-check=full --track-origins=yes ./a.out

valgrind: lldb
	valgrind --suppressions=.valgrind.supp --leak-check=full --track-origins=yes ./a.out

valsup: lldb
	valgrind --gen-suppressions=all --leak-check=full --track-origins=yes --show-leak-kinds=all ./a.out

lldb:
	gcc -ggdb3 src/*/*.c libft/src/*.c -I include -I libft/include -ltermcap

lib:
	@make -C $(LIB_PATH)

clean:
	@$(MAKE) -C $(LIB_PATH) clean
	@$(RM) $(OBJS)
	@rm -rf obj

fclean: clean
	@$(MAKE) -C $(LIB_PATH) fclean
	@$(RM) $(NAME)
	@rm -rf a.out
	@printf "\e[1;31m"	# set red color
	@echo "[ $(NAME)   ] deleted."
	@printf "\e[0m"		# reset color
	@rm -rf obj
	$(DEL_DSYMFILE)

re: fclean all
