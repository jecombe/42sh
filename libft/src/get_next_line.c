/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 17:43:12 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 00:58:01 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/get_next_line.h"

int					ft_gnl_init(int fd, t_gnline **list, t_gnline **stack)
{
	if (*list == NULL)
	{
		if (!(*list = (t_gnline *)malloc(sizeof(t_gnline))))
			return (0);
		(*list)->fd = fd;
		(*list)->str = ft_strdup("");
		(*list)->index = 0;
		(*list)->next = NULL;
	}
	while (*list && (*list)->fd != fd)
		list = &(*list)->next;
	if (!(*list))
	{
		if (!(*stack = (t_gnline *)malloc(sizeof(t_gnline))))
			return (0);
		(*stack)->fd = fd;
		(*stack)->str = ft_strdup("");
		(*stack)->index = 0;
		(*stack)->next = *list;
		*list = *stack;
	}
	else
		*stack = *list;
	return (1);
}

int					ft_fill(t_gnline *stack, char **line)
{
	int				i;
	char			*tmp;

	i = 0;
	if (stack->index != 0 || (ft_strcmp(stack->str, "") != 0))
	{
		while (stack->str[i] && (stack->str[i] != '\n'))
			i++;
		*line = ft_strsub(stack->str, 0, i);
		tmp = ft_strsub(stack->str, i + 1, ft_strlen(stack->str) - (i + 1));
		ft_strdel(&(stack)->str);
		stack->str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else
	{
		*line = NULL;
		return (0);
	}
	return (1);
}

int					get_next_line(int fd, char **line)
{
	static t_gnline	*list;
	t_gnline		*stack;
	char			*buff;
	char			*tmp;

	buff = ft_strnew(GNL_SIZE);
	if (!line || GNL_SIZE < 1 || fd < 0 || (read(fd, buff, 0)) < 0)
		return (-1);
	if (!(ft_gnl_init(fd, &list, &stack)))
		return (0);
	while ((stack->index = read(fd, buff, GNL_SIZE)) > 0)
	{
		tmp = ft_strdup(stack->str);
		ft_strdel(&stack->str);
		stack->str = ft_strjoin(tmp, buff);
		ft_strdel(&tmp);
		ft_strdel(&buff);
		buff = ft_strnew(GNL_SIZE);
		if ((ft_strchr(stack->str, '\n')))
			break ;
	}
	ft_strdel(&buff);
	return (ft_fill(stack, line));
}
