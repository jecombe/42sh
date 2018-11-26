/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_inputs.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/19 22:41:54 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/16 23:13:21 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		ft_input_check(char key[], char buf[])
{
	if (!strncmp(key, buf, 4) ||
	(!strncmp(key, buf, 2) && key[2] == -101 && buf[2] >= 65 && buf[2] <= 66) ||
	(!strncmp(key, buf, 2) && key[2] == -102 && buf[2] >= 67 && buf[2] <= 68) ||
	(!strncmp(key, buf, 3) && key[3] == -101 && buf[3] >= 65 && buf[3] <= 66) ||
	(!strncmp(key, buf, 3) && key[3] == -102 && buf[3] >= 67 && buf[3] <= 68) ||
	(!strncmp(key, buf, 2) && key[2] == -103 && buf[2] >= 70 && buf[2] <= 72))
		return (1);
	return (0);
}

void	ft_init_input_keys(t_shell *sh)
{
	ft_memcpy(sh->keys[0].key, FT_KEY_BCKSPACE, 4);
	sh->keys[0].f = &ft_pushed_key_backspace;
	ft_memcpy(sh->keys[1].key, FT_KEY_ENTER, 4);
	sh->keys[1].f = &ft_pushed_key_enter;
	ft_memcpy(sh->keys[2].key, FT_KEY_LEFTRIGHT, 4);
	sh->keys[2].f = &ft_pushed_left_right;
	ft_memcpy(sh->keys[3].key, FT_KEY_UPDOWN, 4);
	sh->keys[3].f = &ft_pushed_up_down;
	ft_memcpy(sh->keys[4].key, FT_KEY_CTRL_C, 4);
	sh->keys[4].f = &ft_pushed_key_ctrl_c;
	ft_memcpy(sh->keys[5].key, FT_KEY_CTRL_D, 4);
	sh->keys[5].f = &ft_pushed_key_ctrl_d;
	ft_memcpy(sh->keys[6].key, FT_KEY_CTRL_L, 4);
	sh->keys[6].f = &ft_pushed_key_ctrl_l;
	ft_memcpy(sh->keys[7].key, FT_KEY_TAB, 4);
	sh->keys[7].f = &ft_pushed_key_tab;
	ft_memcpy(sh->keys[8].key, FT_KEY_DEL, 4);
	sh->keys[8].f = &ft_pushed_key_del;
	ft_memcpy(sh->keys[9].key, FT_KEY_ALT_UD, 4);
	sh->keys[9].f = &ft_pushed_key_altup_altdown;
	ft_memcpy(sh->keys[10].key, FT_KEY_ALT_LR, 4);
	sh->keys[10].f = &ft_pushed_key_altleft_altright;
	ft_memcpy(sh->keys[11].key, FT_KEY_HOME_END, 4);
	sh->keys[11].f = &ft_pushed_key_home_end;
	sh->keys[12].f = NULL;
}

int		ft_pushed_key_home_end(t_shell *sh, char key[])
{
	if (!ft_strcmp(FT_KEY_HOME, key))
		while (g_cursor_pos > 0)
			ft_pushed_left_right(sh, FT_KEY_LEFT);
	if (!ft_strcmp(FT_KEY_END, key))
		while (g_cursor_pos < (int)ft_strlen(g_cmd))
			ft_pushed_left_right(sh, FT_KEY_RIGHT);
	return (0);
}

int		ft_pushed_key_enter(t_shell *sh, char key[])
{
	if (sh->tabu != -1)
		return (ft_pushed_key_tab(sh, key));
	ft_pushed_key_home_end(sh, FT_KEY_END);
	g_cmd = ft_strjoin_free(g_cmd, "\n");
	get_term_raw_mode(0);
	write(1, "\n", 1);
	return (1);
}

int		ft_pushed_key_tab(t_shell *sh, char key[])
{
	tabulator(&sh, 1, key);
	return (0);
}
