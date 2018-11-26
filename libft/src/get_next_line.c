/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 17:43:12 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 12:16:47 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static int			ft_initgnline(int fd, t_gnline **list, t_gnline **stack)
{
	if (!(*list = (t_gnline *)malloc(sizeof(t_gnline))))
		return (0);
	(*list)->fd = fd;
	(*list)->str = ft_strdup("");
	(*list)->index = 0;
	(*list)->next = NULL;
	*stack = *list;
	return (1);
}

int					ft_gnl_init(int fd, t_gnline **list, t_gnline **stack)
{
	if (*list == NULL)
	{
		if (!ft_initgnline(fd, list, stack))
			return (0);
	}
	else
	{
		*stack = *list;
		while (*stack && (*stack)->next && (*stack)->fd != fd)
			*stack = (*stack)->next;
		if ((*stack)->fd != fd)
		{
			if (!((*stack)->next = (t_gnline *)malloc(sizeof(t_gnline))))
				return (0);
			*stack = (*stack)->next;
			(*stack)->fd = fd;
			(*stack)->str = ft_strdup("");
			(*stack)->index = 0;
			(*stack)->next = NULL;
		}
	}
	return (1);
}

static int			ft_fill(t_gnline *stack, char **line)
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

static int			ft_free_gnl(t_gnline **list)
{
	t_gnline *tmp;
	t_gnline *tmp_2;

	tmp = *list;
	tmp_2 = tmp;
	while (tmp)
	{
		free(tmp->str);
		tmp_2 = tmp->next;
		free(tmp);
		tmp = tmp_2;
	}
	return (-1);
}

int					get_next_line(int fd, char **line)
{
	static t_gnline	*list;
	t_gnline		*stack;
	char			*buff;

	if (!line && fd == -101)
		return (ft_free_gnl(&list));
	buff = ft_strnew(GNL_SIZE);
	if (!line || GNL_SIZE < 1 || fd < 0 || (read(fd, buff, 0)) < 0)
		return (-1);
	if (!(ft_gnl_init(fd, &list, &stack)))
		return (0);
	while ((stack->index = read(fd, buff, GNL_SIZE)) > 0)
	{
		stack->str = ft_strjoin_free(stack->str, buff);
		ft_strdel(&buff);
		buff = ft_strnew(GNL_SIZE);
		if ((ft_strchr(stack->str, '\n')))
			break ;
	}
	ft_strdel(&buff);
	return (ft_fill(stack, line));
}
