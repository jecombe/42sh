/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   shell_signal.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@le-101.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/11 17:32:26 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/05/28 05:55:06 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

void	myhandle(int signal)
{
	char buf[4096];

	if (signal == SIGINT)
	{
		getcwd(buf, sizeof(buf));
		ft_putchar('\n');
		display_prompt(buf, g_save_home, 2, cut_pwd_rep(buf));
		g_bin_exit = 1;
		if (g_save_line)
			ft_strdel(&g_save_line);
		ft_putchar(7);
		return ;
	}
}

void	term_signal(int signal, t_fd *cur, t_minish *sh)
{
	if (signal == 4)
	{
		free(cur);
		free_minish(sh, NULL, NULL, 0);
		ft_putendl("exit");
		exit(0);
	}
}
