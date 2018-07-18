/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 05:29:28 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 03:55:58 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./parsing.h"

int main(int ac, char **av)
{
	t_lex lex;
	t_seq *b_seq;
	t_sc *sc;
	t_op *op;
	int	i = -1;

	lex = ft_lexer(av[1]);
	b_seq = ft_manage_parsing(lex);
	ft_putstr("\x1b[32m");
	printf("--------------BOUCLE B_SEQ-------------\n");
	i = 0;
	while (b_seq)
	{
		printf("B_SEQ NUMBER %d, TOKEN == %u\n", i, b_seq->token);
		while (b_seq->op)
		{
			printf("b_seq->op->token == %u\n", b_seq->op->token);
			while (b_seq->op->sc)
			{
				printf("sc->arg == %s, sc->token == %u\n", b_seq->op->sc->arg, b_seq->op->sc->token);
				b_seq->op->sc = b_seq->op->sc->next;
			}
			b_seq->op = b_seq->op->next;
		}
		i++;
		b_seq = b_seq->next;
	}
	ft_putstr("\x1b[0m");
	return (0);
}
