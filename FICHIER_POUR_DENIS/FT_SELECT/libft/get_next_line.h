/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <gmadec@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 00:59:58 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/25 13:15:51 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# ifndef BUFF_SIZE
#  define BUFF_SIZE 3
# endif
# ifdef CHECK
#  define CHECK(x, y) if (!x) return (y)
# endif
# ifndef CHECK
#  define CHECK(x, y) if (!x) return (y)
# endif
# ifdef STR
#  define STR now->str_lst.str
# endif
# ifndef STR
#  define STR now->str_lst.str
# endif
# ifdef LEN
#  define LEN(x) ft_strlen(x)
# endif
# ifndef LEN
#  define LEN(x) ft_strlen(x)
# endif

int			get_next_line(const int fd, char **line);

#endif
