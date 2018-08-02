/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 03:53:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 03:59:51 by jecombe     ###    #+. /#+    ###.fr     */
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
void 			ft_separate(t_seq *b_seq)
{
	t_op *opera;
	int ok = 0;

	opera = b_seq->op;
	if (opera->next)
	{
			printf("COMMAND-\n");
		while (opera)
		{
			printf("COMMAND-\n");
			// 2 -> retour de ft_solver si il y a echec
			if (ft_solver(opera, g_env) == 2)
			{
				ok = 1;
				//si il y a bien && alors break;
				if (opera->token == AND_IF)
					break;
			}
			opera = opera->next;
		}
	}
	else
	{
		if (ok == 0)
		{
			printf("hdhdhdhdhdhdh\n");
			ft_solver(opera, g_env);
		}
	}
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
			//******EXECUTER LES COMMANDES******//
			//si il y a next dans t_seq
			if (b_seq->token == SEMI)
			{
				while (b_seq)
				{
					//regarde si il y a un next dans t_op
					ft_separate(b_seq);
					//ft_solver(b_seq, g_env);
					b_seq = b_seq->next;
				}
			}
			else
			{
				t_op *pp;
				pp = b_seq->op;
				//regarde si il y a next dans t_op
				printf("laaaaaaaaa\n");
				ft_separate(b_seq);
			}

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
