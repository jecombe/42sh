/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signal.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/13 22:39:45 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/16 03:21:33 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

void	myhandler_interrupt(int signal)
{
	char buf[4096];

	if (signal == SIGINT)
	{
		if ((g_row_number - g_cursor_row_number) != 0)
			tputs(tgoto(tgetstr("DO", NULL), 0, g_row_number - g_cursor_row_number), 1, ft_putchar);
		getcwd(buf, sizeof(buf));
		ft_putchar('\n');
		display_prompt(buf, g_save_home, 2, cut_pwd_dir(buf));
		g_cursor_row_number = get_cursor_position(1);
		g_cursor_col_pos = get_cursor_position(0);
		g_row_number = g_cursor_row_number;
		g_home_position = g_cursor_row_number;
		g_bin_exit = 1;
		if (g_save_line)
			ft_strdel(&g_save_line);
		ft_putchar(7);
		g_cursor_str_pos = 0;
		return ;
	}
}

void	myhandler_winsize_change(int signal)
{
	if (signal == SIGWINCH)
	{
	}
}
