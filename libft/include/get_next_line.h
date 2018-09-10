/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/19 16:47:05 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 01:00:30 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define GNL_SIZE 3

# include "./libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_gnline
{
	int				fd;
	char			*str;
	size_t			index;
	struct s_gnline	*next;
}					t_gnline;

int					get_next_line(const int fd, char **line);

#endif
