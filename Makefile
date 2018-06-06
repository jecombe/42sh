# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/02/01 13:46:52 by dzonda       #+#   ##    ##    #+#        #
#    Updated: 2018/06/06 15:33:13 by jecombe     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all re clean fclean

NAME = 21sh

LIB = libft.a

SRC_PATH = srcs

SRC_NAME =	\
			ft_minishell.c \
			ft_error.c \
			ft_env_manage.c \
			ft_tree_manage.c \
			ft_init.c \
			ft_init_tools.c \
			ft_lexer.c \
			ft_solver.c \
			ft_builtin_cd.c \
			ft_builtin_echo.c \
			ft_builtin_env.c \
			ft_builtin_exit.c \
			ft_builtin_tools.c

OBJ_PATH = objs

OBJ_NAME = $(SRC_NAME:.c=.o)

SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CC = gcc

CFLAGS = -Wall -Wextra -Werror # -fsanitize=address # -g3  

CPPFLAGS = -Iincludes

LDFLAGS = -Llibft

LDLIBS = -lft

all: $(LIB) $(NAME)

$(LIB):
	@cd ./libft/ && $(MAKE)

$(NAME): $(OBJS)
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@echo "\033[1;32m[ $(NAME) ] Compiled\033[0m"


$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@cd ./libft/ && $(MAKE) clean
	@/bin/rm -f $(OBJS)
	@echo "\033[1;31mAll .o [ $(NAME) ] deleted\033[0m"

fclean: clean
	@cd ./libft/ && rm -f $(LIB)
	@/bin/rm -f $(NAME)
	@echo "\033[1;31m[ $(LIB) ] deleted\033[0m"
	@echo "\033[1;31m[ $(NAME) ] deleted\033[0m"

re: fclean all
