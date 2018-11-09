/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signal.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/29 05:34:53 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 09:03:10 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		ft_handle_resize(int sig)
{
	int		tmp_cursor;
	t_shell	sh;

	(void)sig;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &sh.ws);
	sh.prompt_len = g_cmd ? ft_strlen(g_cmd) : 0;
	tmp_cursor = g_cursor_pos;
	TERMCAP("cl");
	display_prompt(g_prompt);
	g_cursor_pos = 0;
	g_cmd ? ft_reprint_cmd(&sh) : 0;
	g_cursor_pos = g_cmd ? ft_strlen(g_cmd) : 0;
	while (tmp_cursor < g_cursor_pos)
		ft_pushed_left(&sh);
}

void		ft_handle_sigint(int sig)
{
	(void)sig;
	ft_putchar('\n');
}
