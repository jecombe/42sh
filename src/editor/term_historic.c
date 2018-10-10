/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   historic.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 10:01:52 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/10 15:08:07 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	down_key(t_editor **ed)
{
	(*ed)->hist -= (*ed)->hist == -3 ? 0 : 1;
	if ((*ed)->hist < 0 && !((*ed)->hist <= -3))
	{
		ft_strdel(&(*ed)->line);
		go_to_begin_of_line(*ed);
		delete_from_cursor_to_end(*ed);
		if ((*ed)->tmp_line)
		{
			ft_strdel(&(*ed)->line);
			(*ed)->line = ft_strdup((*ed)->tmp_line);
			ft_strdel(&(*ed)->tmp_line);
		}
		(*ed)->hist = -2;
		(*ed)->cursor_str_pos = (*ed)->line ? ft_strlen((*ed)->line) : 0;
		return (0);
	}
	(*ed)->hist--;
	return ((*ed)->hist < 0 ? 0 : 1);
}

size_t		count_new_lines(char *line, size_t first_char_pos)
{
	int i;
	int line_len;
	size_t sum;
	t_sz	ws;

	i = -1;
	line_len = first_char_pos;
	sum = 0;
	if (ioctl(2, TIOCGWINSZ, &ws) == -1)
		return (-1);
	while (line[++i])
	{
		if (ws.ws_col == line_len || line[i] == '\n')
		{
			line_len = 0;
			sum++;
		}
		line_len++;
	}
	return (sum);
}

int		term_historic(t_editor **ed)
{
	int new_line_sum;

	new_line_sum = 0;
	if (UP_KEY)
	{
		if ((*ed)->hist <= -2)
		{
			(*ed)->tmp_line = ft_strdup((*ed)->line);
			(*ed)->hist = 0;
		}
	}
	else if (DOWN_KEY)
		if (!down_key(ed))
			return (0);
	go_to_begin_of_line(*ed);
	delete_from_cursor_to_end(*ed);
	history_get(ed);
	ft_putstr((*ed)->line);
	(*ed)->last_row = get_cursor_position(1);
	(*ed)->cursor_str_pos = ft_strlen((*ed)->line) - 1;
	if ((new_line_sum = count_new_lines((*ed)->line, (*ed)->first_char)) > 0)
		(*ed)->first_row = (*ed)->last_row - new_line_sum;
	else
	{
		while ((*ed)->cursor_str_pos)
			move_cursor_left(*ed);
		(*ed)->first_row = get_cursor_position(1);
	}
	while ((*ed)->cursor_str_pos != ft_strlen((*ed)->line) - 1)
		move_cursor_right(*ed);
	(*ed)->cursor_str_pos = ft_strlen((*ed)->line);
	return (0);
}
