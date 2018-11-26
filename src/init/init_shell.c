/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_shell.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/13 22:58:19 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 09:17:42 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			ft_init_vars(int ac, const char **av)
{
	char	*path;

	path = NULL;
	if (!(path = search_path_of_101sh(av[0])))
		return (EXIT_FAILURE);
	if (init_files(path))
	{
		ft_strdel(&path);
		return (EXIT_FAILURE);
	}
	if (init_set(ac, av) || init_env(path))
	{
		ft_strdel(&path);
		return (EXIT_FAILURE);
	}
	if (init_builtins((const char *)path))
	{
		ft_strdel(&path);
		return (EXIT_FAILURE);
	}
	ft_strdel(&path);
	return (EXIT_SUCCESS);
}

void		ft_init_signals(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGWINCH, ft_handle_resize);
}

int			init_shell(int ac, const char **av)
{
	pid_t shell_pgid;

	if (isatty(STDIN_FILENO))
	{
		while (tcgetpgrp(STDIN_FILENO) != (shell_pgid = getpgrp()))
			kill(-shell_pgid, SIGTTIN);
		ft_init_signals();
		shell_pgid = getpid();
		tcsetpgrp(STDIN_FILENO, shell_pgid);
		ft_init_vars(ac, av);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
