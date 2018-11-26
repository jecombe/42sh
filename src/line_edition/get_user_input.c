/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_user_input.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/18 20:15:51 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/17 11:35:39 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			ft_recup_cursor_pos(t_shell *sh, int *left_xpos, int *right_xpos)
{
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	*left_xpos = 0;
	*right_xpos = -1;
	while (i < g_cursor_pos + sh->prompt_len)
	{
		ret = ret + 1 == sh->ws.ws_col || (i > sh->prompt_len &&
				g_cmd[i - sh->prompt_len] == '\n') ? ret = 0 : ret + 1;
		if (i == g_cursor_pos + sh->prompt_len - 2)
			*left_xpos = ret;
		i++;
	}
	if (g_cmd && g_cursor_pos < (int)ft_strlen(g_cmd))
		*right_xpos = ret + 1 == sh->ws.ws_col || (i > sh->prompt_len &&
			g_cmd[i - sh->prompt_len] == '\n') ? 0 : ret + 1;
	return (ret);
}

int			ft_reprint_cmd(t_shell *sh)
{
	int		i;
	int		cursor_in_line;

	ft_get_cols(&sh->ws);
	i = g_cursor_pos;
	cursor_in_line = ft_recup_cursor_pos(sh, &cursor_in_line, &cursor_in_line);
	while (g_cmd && g_cmd[i])
	{
		if (!(g_cmd[i] == '\n'))
		{
			tputs(tgetstr("im", NULL), 1, ft_putchar);
			write(1, &g_cmd[i], 1);
			tputs(tgetstr("ei", NULL), 1, ft_putchar);
		}
		if (g_cmd[i] == '\n' || (cursor_in_line + 1) % sh->ws.ws_col == 0)
		{
			tputs(tgetstr("sf", NULL), 1, ft_putchar);
			tputs(tgetstr("cr", NULL), 1, ft_putchar);
			cursor_in_line = 0;
		}
		else
			cursor_in_line++;
		i++;
	}
	return (i);
}

void		ft_insert_to_line(t_shell *sh, char *buff)
{
	int		i;
	int		cursor_max;
	int		cursor_tmp;

	i = -1;
	while (buff[++i])
	{
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		ft_add_to_str(&g_cmd, buff[i], g_cursor_pos);
		cursor_max = ft_reprint_cmd(sh);
		cursor_tmp = g_cursor_pos;
		g_cursor_pos = cursor_max;
		while (--cursor_max > cursor_tmp)
			ft_pushed_left(sh);
		g_cursor_pos = cursor_tmp + 1;
	}
}

int			ft_get_user_input_buff_checker(t_shell *sh, char *buff)
{
	int	i;

	i = -1;
	if (ft_isprint(buff[0]) || (buff[0] < 0 && (int)buff < 0x10FFFF))
	{
		init_tab_and_hist(sh, buff);
		ft_insert_to_line(sh, buff);
	}
	else
	{
		init_tab_and_hist(sh, buff);
		while (sh->keys[++i].f)
			if (ft_input_check(sh->keys[i].key, buff) &&
					sh->keys[i].f(sh, buff))
			{
				tputs(tgetstr("ve", NULL), 1, ft_putchar);
				return (1);
			}
	}
	return (0);
}

char		*ft_get_user_input(t_prompt *prompt)
{
	t_shell	sh;
	char	buff[5];

	ft_memset(&sh, 0, sizeof(sh));
	ft_memset(buff, 0, sizeof(buff));
	if (ft_init_shell_struct(&sh, prompt) == -1)
		return (g_cmd = ft_strdup("exit\n"));
	ft_init_input_keys(&sh);
	get_term_raw_mode(1);
	while (1)
	{
		ft_bzero(buff, 5);
		if (!(read(0, buff, 4)))
			return (NULL);
		tputs(tgetstr("vi", NULL), 1, ft_putchar);
		ft_get_cols(&sh.ws);
		if (ft_get_user_input_buff_checker(&sh, buff))
			return (g_cmd);
		tputs(tgetstr("ve", NULL), 1, ft_putchar);
	}
}
