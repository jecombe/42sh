/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 03:53:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/04 21:56:02 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/stdin.h"
#include "../include/lexer.h"
//#include "../include/parsing.h"
#include "../include/execute.h"

#define cv ft_convert_token_to_string

void				ft_watch_result(char *line, t_lex lex, t_seq *n_seq)
{
	int				i = -1;
	t_op			*n_op;
	t_redirect		*n_redirect;

	printf("%sLINE :%s\n%s\n", RED, END, line);
	printf("%sLEXER : \n%s", RED, END);
	while (lex.name[++i])
		printf(".%s. .%s.\n", lex.name[i], ft_convert_token_to_string(lex.token[i]));
	while (n_seq)
	{
		n_op = n_seq->op;
		while (n_op)
		{
			if (n_op->cmd)
			{
				i = -1;
				while (n_op->cmd[++i])
					printf("CMD[%d] == %s\n", i, n_op->cmd[i]);
			}
			n_redirect = n_op->redirect;
			while (n_redirect)
			{
				printf("FD == %s, redirect == %s FILE == %s\n", n_redirect->fd, cv(n_redirect->redirect), n_redirect->file);
				n_redirect = n_redirect->next;
			}
			printf("n_op->token == %s\n", cv(n_op->token));
			n_op = n_op->next;
		}
		printf("n_seq->token == %s\n", cv(n_seq->token));
		n_seq = n_seq->next;
	}
	ft_putstr(END);
}

int					ft_term_init(char **environ)
{
	char			*term;

	g_env = ft_tabdup(environ);
	if (!(term = getenv("TERM")))
		term = "xterm-256color";
	if (tgetent(NULL, term) == ERR)
		return (1);
	return (0);
}

void				ft_101sh(void)
{
	e_prompt		prompt;
	char			*line;
	t_lex			lex;
	t_seq			*b_seq;

	prompt = PROMPT;
	line = NULL;
	while (get_stdin(&line, prompt))
	{
		if (line)
		{
			lex = ft_lexer(line);
			b_seq = ft_parsing(lex);
			if (b_seq)
			//******EXECUTER LES COMMANDES******//
			ft_solver(b_seq, g_env);
			ft_watch_result(line, lex, b_seq);
			ft_strdel(&line);
			ft_free_b_seq(&b_seq);
		}
	}
}

int					main(int ac, char *av[])
{
	extern char		**environ;

	if (ft_term_init(environ))
		return (EXIT_FAILURE);
	ft_101sh();
	return (EXIT_SUCCESS);
}
