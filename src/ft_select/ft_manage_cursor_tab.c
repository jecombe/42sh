/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_cursor_tab.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 10:48:53 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/17 11:36:02 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	place_cursor_before(t_shell *sh)
{
	int		i;

	i = g_cursor_pos;
	while (g_cursor_pos)
		ft_pushed_left(sh);
	g_cursor_pos = i;
	TERMCAP("cr");
	i = ft_count_line_cmd(sh);
	while (i + 1)
	{
		TERMCAP("dl");
		i--;
	}
}

void	place_cursor_after(t_shell *sh)
{
	int		i;

	i = ft_count_line_cmd(sh);
	while (i + 1)
	{
		TERMCAP("al");
		i--;
	}
	display_prompt(0);
	i = g_cursor_pos;
	g_cursor_pos = 0;
	ft_reprint_cmd(sh);
	g_cursor_pos = g_cmd ? ft_strlen(g_cmd) : 0;
	while (g_cursor_pos > i)
		ft_pushed_left(sh);
	g_cursor_pos = i;
}
