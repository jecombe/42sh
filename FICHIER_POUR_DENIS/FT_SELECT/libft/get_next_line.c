/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <gmadec@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/10 13:28:03 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/02/25 21:55:04 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

static char	*ft_joint(char *s1, char *s2)
{
	char				*tmp;

	tmp = ft_strjoin(s1, s2);
	ft_strdel(&s1);
	return (tmp);
}

static int	ft_manage_list(t_list **begin, t_list **now, t_list **after, int fd)
{
	if (!*begin)
	{
		CHECK((*begin = malloc(sizeof(t_list))), -1);
		(*begin)->next = NULL;
		(*begin)->str_lst.str = ft_strdup("");
		(*begin)->pos.x = fd;
	}
	*now = *begin;
	while (!((*now)->pos.x == fd) && (*now)->next)
		*now = (*now)->next;
	if (!((*now)->pos.x == fd))
	{
		CHECK((*after = malloc(sizeof(t_list))), -1);
		(*after)->next = NULL;
		(*after)->str_lst.str = ft_strdup("");
		(*after)->pos.x = fd;
		(*now)->next = *after;
		*now = (*now)->next;
	}
	return (0);
}

static int	ft_stack_tmp(int fd, t_list **now)
{
	char				*buf;
	int					i;
	int					ret;

	i = 0;
	ret = 0;
	CHECK((buf = malloc(sizeof(char) * BUFF_SIZE + 1)), -1);
	if (!(*now)->str_lst.str || !ft_strchr((*now)->str_lst.str, '\n'))
		while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			if (!(*now)->str_lst.str)
				(*now)->str_lst.str = ft_strdup(buf);
			else
				(*now)->str_lst.str = ft_joint((*now)->str_lst.str, buf);
			if (ft_strchr((*now)->str_lst.str, '\n'))
				break ;
			i++;
		}
	free(buf);
	if (ret == -1)
		return (-1);
	return (LEN((*now)->str_lst.str) ? 1 : 0);
}

int			get_next_line(const int fd, char **line)
{
	static	t_list		*begin = NULL;
	t_list				*now;
	t_list				*after;
	char				*tmp;
	int					i;

	i = 0;
	CHECK(!(ft_manage_list(&begin, &now, &after, fd) || BUFF_SIZE <= 0), -1);
	CHECK(!((i = ft_stack_tmp(fd, &now)) == -1 || i == 0), i == -1 ? -1 : 0);
	if (ft_strchr(STR, '\n'))
	{
		*line = STR[0] == '\n' ? ft_strdup("") :
		ft_strsub(STR, 0, ft_strchr(STR, '\n') - STR);
		tmp = STR[0] == '\n' && !STR[0] ? NULL :
		ft_strdup(now->str_lst.str + LEN(*line) + 1);
		ft_strdel(&now->str_lst.str);
		now->str_lst.str = tmp ? ft_strdup(tmp) : NULL;
		ft_strdel(&tmp);
		return (1);
	}
	if (!ft_strchr(STR, '\n') && LEN(STR) == 0)
		return (0);
	*line = ft_strdup(STR);
	STR = ft_strdup("");
	return (1);
}
