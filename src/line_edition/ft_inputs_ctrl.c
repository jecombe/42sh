/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_inputs_ctrl.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/07 16:12:31 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 21:55:09 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		ft_pushed_key_ctrl_c(t_shell *sh, char key[])
{
	(void)key;
	add_to_set("?", "1");
	ft_pushed_key_home_end(sh, FT_KEY_END);
	TERMCAP("do");
	TERMCAP("cr");
	if (g_prompt == E_HDOC && !ft_strcmp(key, FT_KEY_CTRL_C))
		g_h = 1;
	g_prompt = PROMPT;
	get_term_raw_mode(0);
	ft_strdel(&g_cmd);
	return (1);
}

int		ft_pushed_key_ctrl_d(t_shell *sh, char key[])
{
	(void)key;
	if (!g_cmd)
	{
		free(g_cmd);
		get_term_raw_mode(0);
		if (g_prompt == E_HDOC)
			return (ft_pushed_key_ctrl_c(sh, key));
		g_cmd = ft_strdup(FT_KEY_CTRL_D);
		ft_putstr("\n");
		return (1);
	}
	return (0);
}

int		ft_pushed_key_ctrl_l(t_shell *sh, char key[])
{
	(void)sh;
	(void)key;
	ft_handle_resize(0);
	return (0);
}
