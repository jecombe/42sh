/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/13 23:45:57 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 00:57:40 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

t_shell*shell_init(t_shell *sh, char **env)
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
	char *xterm;
	char *line;
	t_shell *sh;

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
	ft_putstr(tgetstr("cl", NULL));
	while (get_stdin(&line, sh) > 0)
	{
		ft_strdel(&line);
	}
	sleep(150);
}
