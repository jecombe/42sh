/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move_word_left.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:54:46 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 17:03:36 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		check_if_previous_word(char *line, size_t cursor_str_pos)
{
	size_t s_pos;
	t_sz sz;

	ft_memset(&sz, 0, sizeof(sz));
	s_pos = cursor_str_pos;
	while (cursor_str_pos > 0)
	{
		if ((line[cursor_str_pos - 1] == ' ' || line
		[cursor_str_pos - 1] == '\t') && line[cursor_str_pos] >= 33
		&& line[cursor_str_pos] <= 126 && cursor_str_pos != s_pos)
			return (cursor_str_pos);
		cursor_str_pos--;
		if (!cursor_str_pos && line[cursor_str_pos] >= 33
		&& line[cursor_str_pos] <= 126)
			return (cursor_str_pos);
	}
	return (-1);
}

void			move_word_left(t_editor *ed)
{
	size_t	previous_word_pos;

	if ((previous_word_pos =
	check_if_previous_word(ed->line, ed->cursor_str_pos)) != -1)
		while (ed->cursor_str_pos > previous_word_pos)
			move_cursor_left(ed);
}
