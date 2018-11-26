/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 07:40:58 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/06 17:20:48 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		ft_putcmd(t_shell *sh, int new_pos)
{
	int		cursor_tmp;
	int		cursor_max;

	if (g_cmd)
	{
		cursor_tmp = g_cursor_pos;
		while (g_cursor_pos)
			ft_pushed_left(sh);
		cursor_max = ft_reprint_cmd(sh);
		g_cursor_pos = new_pos;
		while (--cursor_max > g_cursor_pos)
			ft_pushed_left(sh);
	}
}

int			ft_count_line_cmd(t_shell *sh)
{
	int		y;
	char	*cmd;
	int		i;
	int		x;

	y = 0;
	x = 0;
	i = -1;
	cmd = NULL;
	while (++i < sh->prompt_len)
		ft_add_to_str(&cmd, ' ', i);
	cmd = g_cmd ? ft_strjoin_free(cmd, g_cmd) : cmd;
	i = -1;
	while (cmd && cmd[++i])
	{
		if (cmd[i] == '\n' || (x + 1) % sh->ws.ws_col == 0)
		{
			x = 0;
			y++;
		}
		else
			x++;
	}
	ft_strdel(&cmd);
	return (y);
}

void		ft_get_cols(t_ws *ws)
{
	ioctl(STDOUT_FILENO, TIOCGWINSZ, ws);
	if (!ws->ws_col)
		ws->ws_col = 80;
	if (!ws->ws_row)
		ws->ws_row = 80;
}
