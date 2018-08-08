# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/24 18:33:54 by dzonda       #+#   ##    ##    #+#        #
#    Updated: 2018/08/08 02:29:23 by gmadec      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all re clean fclean lib

NAME = 101sh

MAKE = make
CC = gcc
CFLAGS = #-Wall -Werror -Wextra
CPPFLAGS = -I./
LDLIBS = -lft -ltermcap
LDFLAGS = -Llibft/
RM = rm -f

SRCS_PATH = ./src/
OBJS_PATH = ./obj/
INCS_PATH = ./include/
LIB_PATH = ./libft/

SRCS_NAME =	\
			main.c \
			stdin/add_char.c \
			stdin/backspace.c \
			stdin/clear_window.c \
			stdin/cursor_position.c \
			stdin/delete_from_cursor_to_end.c \
			stdin/end_of_text.c \
			stdin/escape_sequence.c \
			stdin/find_env_var.c \
			stdin/get_stdin.c \
			stdin/go_to_begin_of_line.c \
			stdin/go_to_end_of_line.c \
			stdin/move_cursor_down.c \
			stdin/move_cursor_left.c \
			stdin/move_cursor_right.c \
			stdin/move_cursor_up.c \
			stdin/move_word_left.c \
			stdin/move_word_right.c \
			stdin/paste_clipboard.c \
			stdin/prompt.c \
			stdin/signal.c \
			lexer/ft_lexer.c \
			lexer/ft_lexer_break_words.c \
			lexer/ft_lexer_tokens.c \
			lexer/ft_lexer_utils.c \
			parser/ft_attrib_parsing.c \
			parser/ft_convert_token.c \
			parser/ft_free_parse.c \
			parser/ft_malloc_parsing.c \
			parser/ft_manage_parsing.c \
			parser/ft_parsing.c \
			extension/extension.c \
			extension/ft_split_b_quote.c \
			extension/ft_dollar.c \
			execute/binary.c \
			execute/execute.c \
			execute/solver.c \
			execute/utils.c \
			execute/check_command.c \
			redirections/open_file_redirections.c \
			redirections/return_flag_redirections.c \
			redirections/heredoc.c \
			builtins/builtins.c \
			builtins/cd.c \
			builtins/echo.c \
			builtins/exit.c \
			builtins/env.c \
			builtins/setenv.c \
			builtins/unsetenv.c

OBJS_FOLDERS = builtins stdin lexer parser extension execute redirections
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
