/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_inputs_arrows.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/07 15:56:11 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/18 05:49:01 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	ft_pushed_key_altup_altdown_check(t_shell *sh, char *key, int lr[2],
		int target)
{
	if (!ft_strncmp(FT_KEY_ALT_UP, key, 4) ? !g_cursor_pos : lr[1] == -1)
	{
		TERMCAP("rc");
		return (1);
	}
	else
	{
		if (!ft_strncmp(FT_KEY_ALT_UP, key, 4))
		{
			if (lr[0] < target)
				target = lr[0];
			ft_pushed_left(sh);
		}
		else
			ft_pushed_right(sh);
		while (ft_recup_cursor_pos(sh, &lr[0], &lr[1]) != target &&
		(!ft_strncmp(FT_KEY_ALT_UP, key, 4) ? g_cursor_pos :
		lr[1] != -1 && lr[1] != 0))
			!ft_strncmp(FT_KEY_ALT_UP, key, 4) ? ft_pushed_left(sh) :
				ft_pushed_right(sh);
	}
	return (0);
}

int			ft_pushed_key_altup_altdown(t_shell *sh, char key[])
{
	int target;
	int cur_pos;
	int lr[2];

	ft_memset(lr, 0, sizeof(lr));
	cur_pos = g_cursor_pos;
	TERMCAP("sc");
	target = ft_recup_cursor_pos(sh, &lr[0], &lr[1]);
	while (!ft_strncmp(FT_KEY_ALT_UP, key, 4) ?
	g_cursor_pos && lr[1] != 0 : (lr[1] != -1 && lr[1] != 0))
	{
		!ft_strncmp(FT_KEY_ALT_UP, key, 4) ?
		ft_pushed_left(sh) : ft_pushed_right(sh);
		ft_recup_cursor_pos(sh, &lr[0], &lr[1]);
	}
	if (ft_pushed_key_altup_altdown_check(sh, key, lr, target))
		g_cursor_pos = cur_pos;
	return (0);
}

int			ft_pushed_key_altleft_altright(t_shell *sh, char key[])
{
	int i;

	i = g_cursor_pos;
	while (!ft_strncmp(FT_KEY_ALT_LEFT, key, 4) ? i > 0 : i <
			(int)ft_strlen(g_cmd))
	{
		if ((i == 0 || ft_isspace(g_cmd[i - 1])) && !ft_isspace(g_cmd[i]) &&
				ft_isprint(g_cmd[i]) && i != g_cursor_pos)
			break ;
		!ft_strncmp(FT_KEY_ALT_LEFT, key, 4) ? i-- : i++;
	}
	if (!((i == 0 || ft_isspace(g_cmd[i - 1])) && !ft_isspace(g_cmd[i]) &&
				ft_isprint(g_cmd[i]) && i != g_cursor_pos))
		return (0);
	while (g_cursor_pos != i)
		!ft_strncmp(FT_KEY_ALT_LEFT, key, 4) ?
		ft_pushed_left_right(sh, FT_KEY_LEFT) :
		ft_pushed_left_right(sh, FT_KEY_RIGHT);
	return (0);
}

int			ft_pushed_left_right(t_shell *sh, char key[])
{
	if (sh->tabu != -1)
		return (ft_pushed_key_tab(sh, key));
	else if (!ft_strcmp(FT_KEY_LEFT, key))
		ft_pushed_left(sh);
	else if (!ft_strcmp(FT_KEY_RIGHT, key))
		ft_pushed_right(sh);
	return (0);
}

int			ft_pushed_up_down(t_shell *sh, char key[])
{
	if (sh->tabu != -1)
		return (ft_pushed_key_tab(sh, key));
	else
		history_get(sh, key);
	return (0);
}
