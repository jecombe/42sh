/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/13 23:45:57 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/07 00:24:51 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

t_shell		*shell_init(t_shell *sh, char **env)
{
	if (!(sh = (t_shell*)malloc(sizeof(t_shell))))
		return (NULL);
	sh->err = 0;
	sh->line = NULL;
	g_save_line = NULL;
	g_save_home = NULL;
	g_bin_exit = 0;
	getcwd(sh->last_path, sizeof(sh->last_path));
	if (!(sh->my_env = ft_tabdup(env)))
		return (NULL);
	return (sh);
}

int		main(void)
{
	extern char **environ;
	t_shell *sh;
	char *xterm;

	sh = NULL;
	if ((sh = shell_init(sh, environ)) == NULL)
		return (-1);
	if ((xterm = getenv("TERM")) == NULL)
	{
		ft_putstr_fd("Please set the environment variable TERM;\n", STDERR_FILENO);
		return (-1);
	}
	if (tgetent(NULL, xterm) == ERR)
		return (-1);
	signal(SIGINT, myhandler_interrupt);
	ft_putstr(tgetstr("cl", NULL));
	while (get_stdin(sh, &sh->line) > 0)
	{
		ft_strdel(&sh->line);
	}
}
