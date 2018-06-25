/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 05:29:28 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/25 05:50:46 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./parsing.h"

int main(int ac, char **av)
{
	t_lex lex;
	t_seq *b_seq;
	t_sc *sc;
	t_cc *cc_in;
	t_cc *cc_out;
	t_op *op;
	int	i;
	int	j;
	int	k;
	int	l;

	lex = ft_lexer(av[1]);
	printf("--------LEXING----------\n");
	while (lex.name[++i])
	{
		printf("NAME == %s\n", lex.name[i]);
		printf("TOKEN == %u\n", lex.token[i]);
	}
	printf("--------PARSING----------\n");
	b_seq = ft_parsing(lex);
	printf("--------------BOUCLE B_SEQ-------------\n");
	i = 0;
	while (b_seq)
	{
		printf("%dB_SEQ\n", i);
		j = 0;
		op = b_seq->op;
		while (op)
		{
			printf("%dB_SEQ->OP->OP == %u\n", j, op->op);
			if (op->sc)
				while (op->sc)
				{
					printf("OP->SC->ARG == %s\n", op->sc->arg);
					printf("OP->SC->TOKEN == %u\n", op->sc->token);
					op->sc = op->sc->next;
				}
			else if (op->cc)
			{
				k = 0;
				cc_out = op->cc;
				while (cc_out)
				{
					cc_in = cc_out;
					sc = cc_out->sc;
					printf("%dCC_OUT->NEXT_IN == %u\n", k, cc_out->key);
					while (sc)
					{
						printf("SC->ARG == %s\n", sc->arg);
						sc = sc->next;
					}
					l = 0;
					while (cc_in)
					{
						sc = cc_in->sc;
						while (sc)
						{
							printf("SC->ARG == %s\n", sc->arg);
							sc = sc->next;
						}
						printf("%dCC_IN->NEXT_IN == %u\n", l, cc_in->key);
						cc_in = cc_in->next_in;
						l++;
					}
					k++;
					cc_out = cc_out->next_out;
				}
			}
			else
				printf("ERROR: NI SIMPLE NI COMPOSE CMD !\n");
			op = op->next;
			j++;
		}
		i++;
		b_seq = b_seq->next;
	}
	return (0);
}
