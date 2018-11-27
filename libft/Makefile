# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzonda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/10 20:37:15 by dzonda            #+#    #+#              #
#    Updated: 2018/11/23 06:36:00 by gmadec      ###    #+. /#+    ###.fr      #
#                                                                              #
# **************************************************************************** #

.PHONY: all re clean fclean

NAME = libft.a

MAKE = make
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I./
RM = rm -f

SRCS_PATH = ./src/
OBJS_PATH = ./obj/
INCS_PATH = ./include/

SRCS_NAME =	\
			ft_atoi.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isblank.c \
			ft_isdigit.c \
			ft_islower.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_isupper.c \
			ft_itoa.c \
			ft_lstadd.c \
			ft_lstdel.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_nbrlen.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_stradel.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strdup_free.c \
			ft_strequ.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strjoin_free.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strsplit.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_strtrim.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_wordcount.c \
			ft_wordlen.c \
			get_next_line.c \
			ft_tabdel.c \
			ft_tabdup.c \
			ft_tablen.c \
			ft_getenv.c \
			ft_strdel_in_tab.c \
			ft_str_isalnum.c \
			ft_malloc_cmd.c \
			ft_putstr_color.c \
			ft_add_str_at.c \
			ft_strreplace.c \
			ft_add_to_str.c \
			ft_str_isblank.c \
			ft_strisdigit.c \
			ft_reverse_tab.c \
			ft_concat_tab_to_str.c \
			ft_addstrtostrat.c \
			ft_insert_char_in_str.c \
			ft_chardel_at.c \
			ft_mini_printf.c \
			ft_isquote.c

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))
OBJS = $(addprefix $(OBJS_PATH),$(OBJS_NAME))

NB_FILES = $(words $(SRCS_NAME))
SHELL = /bin/bash # just because sh print -n from echo
COLS = $(shell tput cols)

all: $(NAME)

$(NAME) : init $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "\e[?25h"	# set cursor to visible
	@tput setaf 10 	# set green color
	@tput bold
	@$(eval CURSOR := $(if $(CURSOR),$(CURSOR),0)) # is CURSOR var set ?
	@echo -n "[ $(NAME) ] Compiled $(CURSOR)/$(NB_FILES) files."
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

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c
	@$(eval CURSOR=$(shell echo $$(($(CURSOR) + 1))))
	@$(eval PERCENT=$(shell printf "[%3d/%3d - \e[1m\e[93m%3d%%\e[0m]" $(CURSOR) $(NB_FILES) $$(($(CURSOR) * 100 / $(NB_FILES)))))	
	@$(eval LOADSIZE=$(shell echo $$(($(CURSOR) * $(COLS) / $(NB_FILES)))))
	@printf "\e[?25l\e[s\e[32m\e[44m"
	@number=1 ; while [[ $$i -le $(LOADSIZE)-1 ]] ; do \
        	printf "▌" ; \
        	((i = i + 1)) ; \
    	done
	@printf "\e[0K\e[0m\n\e[1m\e[93m"
	@echo -n "[ $(NAME) ] Compiling: "
	@printf "\e[0m"			# reset color
	@echo -n "$(PERCENT) $@"
	@printf "\e[0K\n\e[u\e[?25h"
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@$(RM) $(OBJS)
	@rm -rf obj

fclean: clean
	@$(RM) $(NAME)
	@printf "\e[1;31m"	# set red color
	@echo "[ $(NAME) ] deleted."
	@printf "\e[0m"		# reset color
	@rm -rf obj

re: fclean all
