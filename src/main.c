/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/13 23:45:57 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/30 02:37:45 by dewalter    ###    #+. /#+    ###.fr     */
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

	prompt = 1;
	if ((xterm = getenv("TERM")) == NULL)
	{
		ft_putstr_fd("Please set the environment variable TERM;\n", STDERR_FILENO);
		return (-1);
	}
	if (tgetent(NULL, xterm) == ERR)
		return (-1);
	ft_putstr(tgetstr("cl", NULL));
	while (get_stdin(&line, environ, prompt) > 0)
	{
		ft_strdel(&line);
	}
	sleep(150);
}
