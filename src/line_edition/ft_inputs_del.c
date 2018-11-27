/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_inputs_del.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/07 16:11:53 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/21 00:56:41 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		ft_pushed_key_backspace(t_shell *sh, char key[])
{
	int		tmp_cursor;

	(void)key;
	if (g_cmd && g_cursor_pos > 0)
	{
		tmp_cursor = g_cursor_pos;
		while (g_cursor_pos)
			ft_pushed_left(sh);
		ft_chardel_at(&g_cmd, tmp_cursor - 1);
		TERMCAP("cd");
		if (g_cmd)
		{
			ft_reprint_cmd(sh);
			g_cursor_pos = ft_strlen(g_cmd);
			while (g_cursor_pos >= tmp_cursor)
				ft_pushed_left(sh);
		}
	}
	return (0);
}

int		ft_pushed_key_del(t_shell *sh, char key[])
{
	int		tmp_cursor;

	(void)key;
	if (g_cmd && g_cursor_pos >= 0 && g_cursor_pos != (int)ft_strlen(g_cmd))
	{
		tmp_cursor = g_cursor_pos;
		while (g_cursor_pos)
			ft_pushed_left(sh);
		ft_chardel_at(&g_cmd, tmp_cursor);
		TERMCAP("cd");
		if (g_cmd)
		{
			ft_reprint_cmd(sh);
			g_cursor_pos = ft_strlen(g_cmd);
			while (g_cursor_pos > tmp_cursor)
				ft_pushed_left(sh);
		}
	}
	return (0);
}
