/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   move.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/19 04:30:23 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/18 23:34:58 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	move_right(void)
{
	t_sz sz;

	ioctl(0, TIOCGWINSZ, &sz);
	if (get_cursor_position(0) == sz.ws_col)
		tputs(tgetstr("do", NULL), 1, ft_putchar);
	else
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
}

int		ft_outtc(int c)
{
	return (write(0, &c, 1));
}

void	move_left(t_editor *ed)
{
	t_sz sz;

	char buf[32];
	ioctl(0, TIOCGWINSZ, &sz);
	if (get_cursor_position(0) == 1 && ed->cursor_str_pos)
	{
		if (ed->line[ed->cursor_str_pos] == '\n')
			move_to_previous_new_line(ed);
		else
		{
			tputs(tgoto(tgetstr("sr", NULL), 1, 1), 1, ft_putchar);
			tputs(tgoto(tgetstr("ch", NULL), 0, sz.ws_col - 1), 1, ft_putchar);
		}
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_outtc);
	/*int i = 0;
	while (i < sizeof(buf)-1)
	{
		if (read(0, buf+i, 1) != 1)
			break;
		i++;
	}*/
}
