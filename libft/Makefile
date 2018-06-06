# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzonda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/10 20:37:15 by dzonda            #+#    #+#              #
#    Updated: 2018/04/19 06:06:28 by dzonda      ###    #+. /#+    ###.fr      #
#                                                                              #
# **************************************************************************** #

.PHONY: all re clean fclean

NAME = libft.a

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror

SRCS = ./srcs/

INCLUDES = ./includes/

FILES = $(SRCS)get_next_line.c \
		$(SRCS)ft_atoi.c \
		$(SRCS)ft_bzero.c \
		$(SRCS)ft_isalnum.c \
		$(SRCS)ft_isalpha.c \
		$(SRCS)ft_isascii.c \
		$(SRCS)ft_isblank.c \
		$(SRCS)ft_isdigit.c \
		$(SRCS)ft_islower.c \
		$(SRCS)ft_isprint.c \
		$(SRCS)ft_isspace.c \
		$(SRCS)ft_isupper.c \
		$(SRCS)ft_itoa.c \
		$(SRCS)ft_lstadd.c \
		$(SRCS)ft_lstdel.c \
		$(SRCS)ft_lstdelone.c \
		$(SRCS)ft_lstiter.c \
		$(SRCS)ft_lstmap.c \
		$(SRCS)ft_lstnew.c \
		$(SRCS)ft_memalloc.c \
		$(SRCS)ft_memccpy.c \
		$(SRCS)ft_memchr.c \
		$(SRCS)ft_memcmp.c \
		$(SRCS)ft_memcpy.c \
		$(SRCS)ft_memdel.c \
		$(SRCS)ft_memmove.c \
		$(SRCS)ft_memset.c \
		$(SRCS)ft_nbrlen.c \
		$(SRCS)ft_putchar.c \
		$(SRCS)ft_putchar_fd.c \
		$(SRCS)ft_putendl.c \
		$(SRCS)ft_putendl_fd.c \
		$(SRCS)ft_putnbr.c \
		$(SRCS)ft_putnbr_fd.c \
		$(SRCS)ft_putstr.c \
		$(SRCS)ft_putstr_fd.c \
		$(SRCS)ft_stradel.c \
		$(SRCS)ft_strcat.c \
		$(SRCS)ft_strchr.c \
		$(SRCS)ft_strclr.c \
		$(SRCS)ft_strcmp.c \
		$(SRCS)ft_strcpy.c \
		$(SRCS)ft_strdel.c \
		$(SRCS)ft_strdup.c \
		$(SRCS)ft_strequ.c \
		$(SRCS)ft_striter.c \
		$(SRCS)ft_striteri.c \
		$(SRCS)ft_strjoin.c \
		$(SRCS)ft_strlcat.c \
		$(SRCS)ft_strlen.c \
		$(SRCS)ft_strmap.c \
		$(SRCS)ft_strmapi.c \
		$(SRCS)ft_strncat.c \
		$(SRCS)ft_strncmp.c \
		$(SRCS)ft_strncpy.c \
		$(SRCS)ft_strnequ.c \
		$(SRCS)ft_strnew.c \
		$(SRCS)ft_strnstr.c \
		$(SRCS)ft_strrchr.c \
		$(SRCS)ft_strsplit.c \
		$(SRCS)ft_strstr.c \
		$(SRCS)ft_strsub.c \
		$(SRCS)ft_strtrim.c \
		$(SRCS)ft_tolower.c \
		$(SRCS)ft_toupper.c \
		$(SRCS)ft_wordcount.c \
		$(SRCS)ft_wordlen.c


OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	clear
	@ar rcs $(NAME) $(OBJS)
	@echo "\033[1;32m[ $(NAME) ] Compiled\033[0m"

./%.o : ./%.c
	@$(CC) $(CC_FLAGS) -I $(INCLUDES) -o $@ -c $<
	@clear
	@echo "\033[1m[ $@ ] Compiled\033[0m"

clean:
	@/bin/rm -f $(OBJS)
	@echo "\033[1;31mAll .o [ $(NAME) ] deleted\033[0m"


fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\033[1;31m[ $(NAME) ] deleted\033[0m"

re: fclean all
