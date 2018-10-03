/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   historic.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 10:01:52 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 21:48:13 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void	print_str(t_editor **ed)
{
	int			loop;

	loop = 0;
	if ((*ed)->line)
	{
		(*ed)->cursor_str_pos = ft_strlen((*ed)->line);
		while ((*ed)->line[loop])
			add_char_to_line((*ed)->line[loop++], *ed);
	}
}

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
			print_str(ed);
		}
		(*ed)->hist = -2;
		(*ed)->cursor_str_pos = (*ed)->line ? ft_strlen((*ed)->line) : 0;
		return (0);
	}
	(*ed)->hist--;
	return ((*ed)->hist < 0 ? 0 : 1);
}

int		term_historic(t_editor **ed)
{
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
	if ((*ed)->line)
	{
		ft_putstr((*ed)->line);
		(*ed)->last_row = get_cursor_position(1);
		(*ed)->cursor_str_pos = ft_strlen((*ed)->line);
		(*ed)->cursor_str_pos--;
		while ((*ed)->cursor_str_pos)
			move_cursor_left(*ed);
		(*ed)->first_row = get_cursor_position(1);
		while ((*ed)->cursor_str_pos != ft_strlen((*ed)->line) - 1)
			move_cursor_right(*ed);
	}
	return (0);
}
