/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   escape_sequence.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:17:49 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/09 23:53:22 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

char	*cursor_position_escape_sequence(int row, int col)
{
	char *h_pos;
	char *v_pos;
	char *cursor_pos;

	v_pos = ft_itoa(get_cursor_position(1) - row);
	h_pos = ft_itoa(get_cursor_position(0) - col);
	cursor_pos = ft_strnew(6 + ft_strlen(v_pos) + ft_strlen(h_pos));
	ft_strcpy(cursor_pos, "\E[");
	ft_strcat(cursor_pos, v_pos);
	ft_strcat(cursor_pos, ";");
	ft_strcat(cursor_pos, h_pos);
	ft_strcat(cursor_pos, "H");
	ft_strdel(&h_pos);
	ft_strdel(&v_pos);
	return (cursor_pos);
}

void	reset_cursor_position_escape_sequence(char **cursor_positon)
{
	if (cursor_positon)
	{
		ft_putstr(*cursor_positon);
		ft_strdel(cursor_positon);
	}
}
