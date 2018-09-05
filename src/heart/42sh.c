/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 03:53:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 18:25:22 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

#define cv ft_convert_token_to_string
/*
void				ft_watch_result(char *line, t_lex lex, t_seq *n_seq)
{
	int				i = -1;
	t_op			*n_op;
	t_redirect		*n_redirect;

	printf("\n\n-------------- ANALYSE ---------------\n\n");
	printf("%sLINE :%s\n.%s.\n\n", RED, END, line);
	printf("%sLEXER :%s\n", RED, END);
//	while (lex.name[++i])
//		printf(".%s. .%s.\n", lex.name[i], ft_convert_token_to_string(lex.token[i]));
	printf("\n%sPARSER :%s\n", RED, END);
	while (n_seq)
	{
	//	printf("n_seq->token == %s\n", cv(n_seq->token));
		n_op = n_seq->op;
		while (n_op)
		{
		//	printf("\tn_op->token == %s\n", cv(n_op->token));
			if (n_op->cmd)
			{
				i = -1;
				while (n_op->cmd[++i])
					printf("\t\tCMD[%d] == %s\n", i, n_op->cmd[i]);
			}
			n_redirect = n_op->redirect;
			while (n_redirect)
			{
			//	printf("\t\t\tFD == %d, redirect == %s FILE == %s\n", n_redirect->fd, cv(n_redirect->redirect), n_redirect->file);
				n_redirect = n_redirect->next;
			}
			n_op = n_op->next;
		}
		ft_putchar('\n');
		n_seq = n_seq->next;
	}
	printf("--------------------------------------\n\n");

}

int					heart_of_101sh(char *line, e_prompt *prompt, int fd_base)
{
	t_lex			lex;
	t_seq			*b_seq;
	pid_t pid;

	ft_memset(&lex, 0, sizeof(t_lex));
	if (line)
		lex = ft_lexer(line, prompt);
	if (!(*prompt))
	{
		ft_strdel(&line);
		b_seq = ft_parsing(lex);
		if (b_seq != NULL)
		{
			if (!extension(&b_seq))
			{
				ft_sequence(b_seq, fd_base, pid);
				//ft_watch_result(line, lex, b_seq);
			}
		}
		ft_free_b_seq(&b_seq);
		ft_memset(&lex, 0, sizeof(t_lex));
	}
	ft_lexer_del(&lex);
//	printf("C EST QUI QUI SEGFAULT QUAND IL Y A UN ENVIRONNEMENT VIDE ?\n");
//	printf("ET AUSSI SUR echo 'ls\n");
	return (0);
}

void				ft_101sh(void)
{
	e_prompt		prompt;
	char			*line;
	t_hashtable		*hashtable;

	prompt = PROMPT;
	line = NULL;
	hashtable = NULL;
	if (!(hashtable = ft_hashtable_create()))
		return;
	ft_save_hash(&hashtable);
	while (get_stdin(&line, &prompt))
	{
		heart_of_101sh(line, &prompt, 1);
	}
}
*/
int					main(int ac, const char **av)
{
//	if (!isatty(0))
//		return (0);
	g_env = NULL;
	g_set = NULL;
	if (ft_term_init(ac, av))
		return (EXIT_FAILURE);
/*	ft_signal();
	av = ft_tabdup(argv);
	int i = -1;
	while (g_set[++i])
		ft_putendl(g_set[i]);*/
	int i = -1;
	while (g_env[++i])
		ft_putendl(g_env[i]);
	//ft_101sh();
	return (EXIT_SUCCESS);
}
