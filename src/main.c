/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 03:53:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/07 18:36:47 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/stdin.h"
#include "../include/lexer.h"
//#include "../include/parsing.h"
#include "../include/execute.h"
#include "../include/extension.h"

#define cv ft_convert_token_to_string

void				ft_watch_result(char *line, t_lex lex, t_seq *n_seq)
{
	int				i = -1;
	t_op			*n_op;
	t_redirect		*n_redirect;

	printf("\n\n-------------- ANALYSE ---------------\n\n");
	printf("%sLINE :%s\n.%s.\n\n", RED, END, line);
	printf("%sLEXER :%s\n", RED, END);
	while (lex.name[++i])
		printf(".%s. .%s.\n", lex.name[i], ft_convert_token_to_string(lex.token[i]));
	printf("\n%sPARSER :%s\n", RED, END);
	while (n_seq)
	{
		printf("n_seq->token == %s\n", cv(n_seq->token));
		n_op = n_seq->op;
		while (n_op)
		{
			printf("\tn_op->token == %s\n", cv(n_op->token));
			if (n_op->cmd)
			{
				i = -1;
				while (n_op->cmd[++i])
					printf("\t\tCMD[%d] == %s\n", i, n_op->cmd[i]);
			}
			n_redirect = n_op->redirect;
			while (n_redirect)
			{
				printf("\t\t\tFD == %s, redirect == %s FILE == %s\n", n_redirect->fd, cv(n_redirect->redirect), n_redirect->file);
				n_redirect = n_redirect->next;
			}
			n_op = n_op->next;
		}
		ft_putchar('\n');
		n_seq = n_seq->next;
	}
	printf("--------------------------------------\n\n");

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

void		ft_separate(t_seq *b_seq)
{
	t_op *opera;
	int fail;

	fail = 0;
	opera = b_seq->op;
	if (opera->next)
	{
		while (opera)
		{
			// 2 ==> retour de ft_solver si echec
			if (ft_solver(opera) == 2)
			{
				fail = 1;
				//si il y a bien && alors break, execute pas l'autre command;
				if (opera->token == AND_IF)
					break;
			}
			opera = opera->next;
		}
	}
	else
	{
		if (fail == 0)
		{
			ft_solver(opera);
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
			if (!extension(&b_seq))
			{
				//******EXECUTER LES COMMANDES******//
				//si il y a next dans t_seq et que c'est le ;
				if (b_seq->token == SEMI)
				{
					while (b_seq)
					{
						//si il y a encore une separation command ==> &&
						ft_separate(b_seq);
						b_seq = b_seq->next;
					}
				}
				else
				{
					//regarde si il une separation command ==> &&
					ft_separate(b_seq);
				}
				ft_watch_result(line, lex, b_seq);
			}
			if (line)
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
