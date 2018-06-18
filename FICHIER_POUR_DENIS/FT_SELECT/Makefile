# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/05/04 01:34:45 by gmadec       #+#   ##    ##    #+#        #
#    Updated: 2018/05/04 01:34:48 by gmadec      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY= all clean fclean all
.SILENT=

NAME	= ft_select
SRCS =	 main.c ft_error.c ft_disable_raw.c \
		ft_save_raw_off.c ft_enable_raw.c ft_manage_entry.c \
		ft_read_entry.c ft_print_params.c ft_get_size_term.c \
		ft_manage_touch.c ft_arrows.c ft_outc.c \
		ft_init_select.c ft_count_line.c ft_search_big_param.c \
		ft_is_file.c ft_del_maillon.c ft_first_sort.c \
		ft_count_params.c ft_char_by_line.c \
		ft_prepare_print.c ft_params_by_line.c ft_select_sp.c \
		ft_free_t_select.c ft_signal.c ft_save_shell.c ft_searchdyn.c
OBJS	= ${SRCS:.c=.o}
INC		= ./
FLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@cc $(FLAGS) $(SRCS) -o $(NAME) -I libft/includes\
	 -L libft/ -lft -L /usr/lib -ltermcap
%.o: %.c
	@cc -c $< -o $@ $(FLAGS) -I$(INC)
clean:
	@rm -f $(OBJS)
	@$(shell cd libft && make fclean)
fclean: clean
	@rm -f $(NAME)
	@rm -f libft.a
re: fclean all
