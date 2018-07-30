/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/13 23:45:57 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/30 13:32:30 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

int		main(void)
{
	extern char **environ;
	char *xterm;
	char *line;
	e_prompt prompt;

	prompt = 0;
	g_env = ft_tabdup(environ);
	if ((xterm = getenv("TERM")) == NULL)
	{
		ft_putstr_fd("Please set the environment variable TERM;\n", STDERR_FILENO);
		return (-1);
	}
	if (tgetent(NULL, xterm) == ERR)
		return (-1);
	ft_putstr(tgetstr("cl", NULL));
	while (get_stdin(&line, prompt) > 0)
	{
		ft_strdel(&line);
	}
	sleep(150);
}
