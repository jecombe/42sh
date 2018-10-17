/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   historic.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 10:01:52 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/17 19:38:42 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		down_key(t_editor **ed)
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

size_t			count_new_lines(char *line, size_t first_char_pos)
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

int				term_historic(t_editor **ed)
{
	int new_line_sum;
	int ret;

	ret = 0;
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
		dprintf(2, "first_row0: %zu\n" , (*ed)->first_row);
	go_to_begin_of_line(*ed);
		dprintf(2, "first_row1: %zu\n" , (*ed)->first_row);
	delete_from_cursor_to_end(*ed);
		dprintf(2, "first_row2: %zu\n" , (*ed)->first_row);
	history_get(ed);
		dprintf(2, "first_row3: %zu\n" , (*ed)->first_row);
	new_line_sum = count_new_lines((*ed)->line, (*ed)->first_char);
		dprintf(2, "new_line_sum: %d\n", new_line_sum);
	if ((ret = new_line_sum + (*ed)->first_row) > (*ed)->ws_row)
	{
		dprintf(2, "ret: %d\n", ret);
		dprintf(2, "ws_row: %zu\n", (*ed)->ws_row);
		ret = ret / 2;
			(*ed)->first_row = (*ed)->first_row - ret;
		while (ret > (*ed)->ws_row)
		{
			(*ed)->first_row--;
			tputs(tgetstr("sf", NULL), 1, ft_putchar);
			ret--;

		}
	}
		dprintf(2, "OK\n");
	ft_putstr((*ed)->line);
	(*ed)->cursor_str_pos = ft_strlen((*ed)->line);

	/*
	if ((new_line_sum = count_new_lines((*ed)->line, (*ed)->first_char)) > 0)
	{
		dprintf(2, "new_line_sum: %d\n", new_line_sum);
		(*ed)->first_row = (*ed)->last_row - new_line_sum;
		dprintf(2, "first_row: %zu\n" , (*ed)->first_row);
	}
	else
	{
		while ((*ed)->cursor_str_pos)
			move_cursor_left(*ed);
		(*ed)->first_row = get_cursor_position(1);
	}
	while ((*ed)->cursor_str_pos != ft_strlen((*ed)->line) - 1)
		move_cursor_right(*ed);*/
	(*ed)->cursor_str_pos = ft_strlen((*ed)->line);
	(*ed)->cur_col = get_cursor_position(0);
	(*ed)->cur_row = get_cursor_position(1);
	(*ed)->last_row = (*ed)->cur_row;
	(*ed)->last_char = (*ed)->cur_col;
		dprintf(2, "first_row: %zu\n" , (*ed)->first_row);
	return (0);
}
