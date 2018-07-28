/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 03:53:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/28 17:59:27 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parsing.h"

#define cv ft_convert_token_to_string

void		ft_parcour_op(t_op *n_op)
{
	int		i;

	while (n_op)
	{
		i = 0;
		if (n_op->cmd)
			while (n_op->cmd[i])
			{
				printf("CMD[%d] == %s\n", i, n_op->cmd[i]);
				i++;
			}
		printf("TOKEN[0] == %s TOKEN[1] == %s\n", cv(n_op->token[0]), cv(n_op->token[1]));
		n_op = n_op->next;
	}
}

int			 main(int ac, char *argv[])
{
	t_lex	lex;
	t_seq	*b_seq;
	int		i = -1;
	extern char **environ;
	char buff[2048];

	(void)ac;
	while (101)
	{
		if (!(read(0, buff, 2048)))
			break;
		lex = ft_lexer(buff);
		while (lex.name[++i])
			printf(".%s. .%s.\n", lex.name[i], ft_convert_token_to_string(lex.token[i]));
		b_seq = ft_manage_parsing(lex);
		ft_putstr("\x1b[32m");
		printf("-------------- PARSING -------------\n");
		i = 0;
		while (b_seq)
		{
			printf("SEQUENCE NUMBER %d, LIST TERMINATOR == %s\n", i, ft_convert_token_to_string(b_seq->token));
			if (b_seq->op)
				ft_parcour_op(b_seq->op);
			i++;
			if (b_seq->next)
			printf("\n");
			b_seq = b_seq->next;
		}
		ft_putstr("\x1b[0m");
	}
	return (0);
}
