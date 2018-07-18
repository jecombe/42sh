/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 03:53:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 08:46:26 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parsing.h"

int main(int ac, char *argv[])
{
	t_lex lex;
	t_seq *b_seq;
	int i = -1;
	int j = 0;

	(void)ac;
	lex = ft_lexer(argv[1]);
	while (lex.name[++i])
		printf(".%s. .%s.\n", lex.name[i], ft_convert_token_to_string(lex.token[i]));
	b_seq = ft_manage_parsing(lex);
	ft_putstr("\x1b[32m");
	printf("-------------- PARSING -------------\n");
	i = 0;
	while (b_seq)
	{
		printf("SEQUENCE NUMBER %d, LIST TERMINATOR == %s\n", i, ft_convert_token_to_string(b_seq->token));
		while (b_seq->op)
		{
			printf("\t|--> OPERATEUR == %s\n", ft_convert_token_to_string(b_seq->op->token));
			if (b_seq->op->sc)
			{
				if (b_seq->op->sc->cmd)
				{
					j = 0;
					while (b_seq->op->sc->cmd[j])
					{
						printf("\t\tARG == %s\n", b_seq->op->sc->cmd[j]);
						j++;
					}
				}
			}
			printf("\n");
			b_seq->op = b_seq->op->next;
		}
		i++;
		printf("\n\n");
		b_seq = b_seq->next;
	}
	ft_putstr("\x1b[0m");
	return (0);
}
