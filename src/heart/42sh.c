/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 03:53:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/13 16:18:52 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void	ft_watch_result(char *line, t_lex lex, t_seq *n_seq);

int					heart_of_101sh(char *line, int fd_base)
{
	t_lex			lex;
	t_seq			*seq;
	pid_t pid;

	ft_memset(&lex, 0, sizeof(t_lex));
	seq = NULL;
	lex = lexer(line);
	if ((seq = ft_parsing(lex)))
	{
		if (!extension(&seq))
		{
			//ft_watch_result(line, lex, seq);
			ft_sequence(seq, fd_base, pid);
			history_add(line);
		}
		else
			printf("!!!!!!!!!!!!!SSSSEEEQQQ\n");
		ft_free_b_seq(&seq);
	}
	ft_lexer_del(&lex);
	ft_strdel(&line);
	return (EXIT_SUCCESS);
}

static void			shell(void)
{
	e_prompt		prompt;
	char			*line;

	prompt = PROMPT;
	line = NULL;
	while (get_stdin(&line, &prompt))
		if (line && (!(prompt = prelexer(line))))
			heart_of_101sh(line, 1);
}

int			main(int ac, const char **av)
{
	if (!isatty(0))
		return (0);
	if (init_shell(ac, av))
		return (EXIT_FAILURE);
	signal_shell();
	shell();
	exit_shell(av[0]);
	return (EXIT_SUCCESS);
}
