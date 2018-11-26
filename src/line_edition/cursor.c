/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/27 09:50:31 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/23 11:28:32 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	ft_pushed_right(t_shell *sh)
{
	int		pos;
	int		right_xpos;
	int		zell;

	if (g_cmd && g_cursor_pos < (int)ft_strlen(g_cmd))
	{
		pos = ft_recup_cursor_pos(sh, &zell, &right_xpos);
		if (right_xpos > 0)
			TERMCAP("nd");
		else if (right_xpos == 0)
		{
			TERMCAP("sf");
			TERMCAP("cr");
		}
		g_cursor_pos++;
	}
}

void	ft_pushed_left(t_shell *sh)
{
	int		pos;
	int		left_xpos;
	int		zell;

	zell = 0;
	if (g_cursor_pos > 0)
	{
		pos = ft_recup_cursor_pos(sh, &left_xpos, &zell);
		if (pos == 0)
		{
			TERMCAP("up");
			while (pos < left_xpos)
			{
				TERMCAP("nd");
				pos++;
			}
		}
		else
			TERMCAP("le");
		g_cursor_pos--;
	}
}
