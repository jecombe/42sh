/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/13 23:45:57 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/08 00:27:41 by dewalter    ###    #+. /#+    ###.fr     */
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

	prompt = 2;
	g_env = ft_tabdup(environ);
	if ((xterm = getenv("TERM")) == NULL)
	{
		ft_putstr_fd("Please set the environment variable TERM;\n", STDERR_FILENO);
		return (-1);
	}
	if (tgetent(NULL, xterm) == ERR)
		return (-1);
	ft_putstr(tgetstr("cl", NULL));
	while (get_stdin(&line, &prompt) > 0)
	{
		printf("line:     [%s]\nprompt: [%u]\n", line, prompt);
		if (line)
		if (ft_strchr(line, 'q'))
		{
			ft_strdel(&line);
				prompt = 0;
		}
		if (prompt == PROMPT || prompt == E_PIPE)
		{
			ft_strdel(&line);
			printf("OK\n");
		}
	}
	sleep(150);
}
