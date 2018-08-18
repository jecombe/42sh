/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 17:43:12 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:37:37 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/get_next_line.h"

int					ft_gnl_init(int fd, t_line **list, t_line **stack)
{
	if (*list == NULL)
	{
		if (!(*list = (t_line *)malloc(sizeof(t_line))))
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
		if (!(*stack = (t_line *)malloc(sizeof(t_line))))
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

int					ft_fill(t_line *stack, char **line)
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
	static t_line	*list;
	t_line			*stack;
	char			*buff;
	char			*tmp;

	buff = ft_strnew(BUFF_SIZE);
	if (!line || BUFF_SIZE < 1 || fd < 0 || (read(fd, buff, 0)) < 0)
		return (-1);
	if (!(ft_gnl_init(fd, &list, &stack)))
		return (0);
	while ((stack->index = read(fd, buff, BUFF_SIZE)) > 0)
	{
		tmp = ft_strdup(stack->str);
		ft_strdel(&stack->str);
		stack->str = ft_strjoin(tmp, buff);
		ft_strdel(&tmp);
		ft_strdel(&buff);
		buff = ft_strnew(BUFF_SIZE);
		if ((ft_strchr(stack->str, '\n')))
			break ;
	}
	ft_strdel(&buff);
	return (ft_fill(stack, line));
}
