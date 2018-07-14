/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/14 20:22:47 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./parsing.h"

t_seq		*ft_malloc_seq(int version)
{
	static int		i = 0;
	t_seq	*new;

	printf("MALLOC_SEQ NUMBER %d\n", i);
	if (!(new = malloc(sizeof(t_seq))))
		return (NULL);
	new->op = NULL;
	new->close = 0;
	new->next = NULL;
	new->prev = NULL;
	if (version == 1)
		new->close = 1;
	i++;
	return (new);
}

t_cc		*ft_malloc_cc(void)
{
	t_cc		*new;
	t_cc		*now;

	static int		i = 0;
	printf("MALLOC_CC NUMBER %d\n", i);
	i++;
	if (!(new = malloc(sizeof(t_cc))))
		return (NULL);
	new->next_in = NULL;
	new->next_out = NULL;
	new->sc = NULL;
	new->open = 0;
	new->close = 0;
	new->key = NUL;
	new->prev_in = NULL;
	new->prev_out = NULL;
	return (new);
}

t_op		*ft_malloc_op(void)
{
	t_op	*new;

	static int		i = 0;
	printf("MALLOC_OP NUMBER %d\n", i);
	i++;
	if (!(new = malloc(sizeof(t_op))))
		return (NULL);
	new->op = NUL;
	new->close = 0;
	new->sc = NULL;
	new->cc = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->inside = 0;
	return (new);
}

t_sc		*ft_malloc_sc(void)
{
	t_sc		*new;

	static int		i = 0;
	printf("MALLOC_SC NUMBER %d\n", i);
	i++;
	if (!(new = malloc(sizeof(t_cc))))
		return (NULL);
	new->next = NULL;
	new->arg = NULL;
	new->token = NUL;
	new->prev = NULL;
	return (new);
}

int			ft_manage_semi(t_seq **b_seq)
{
	t_seq	*n_seq;

	static int		i = 0;
	printf("MANAGE_SEMI NUMBER %d\n", i);
	i++;
	n_seq = *b_seq;
	if (n_seq)
	{
		int x = 1;
		while (n_seq->next)
		{
			x++;
			n_seq = n_seq->next;
		}
		printf("';' %d MAILLON TROUVE\n", x);
		if (n_seq->op && !n_seq->close)
		{
			x = 1;
			while (n_seq->op->next)
			{
				x++;
				n_seq->op = n_seq->op->next;
			}
			printf("';' %d N_SEQ->OP && !N_SEQ->CLOSE\n", x);
			if (n_seq->op->cc && n_seq->op->op != NUL)
			{
				x = 0;
				if (n_seq->op->cc->next_out)
				{
					x = 1;
					while (n_seq->op->cc->next_out)
					{
						x++;
						n_seq->op->cc = n_seq->op->cc->next_out;
					}
				}
				printf("%d N_SEQ->OP->CC->NEXT_OUT TROUVE\n", x);
				x = 0;
				if (n_seq->op->cc->next_in)
				{
					x = 1;
					while (n_seq->op->cc->next_in)
					{
						printf("NEXT_IN NUMBER %d\n", x++);
						n_seq->op->cc = n_seq->op->cc->next_in;
					}
				}
				printf("%d N_SEQ->OP->CC->NEXT_IN TROUVE\n", x);
					//PB ICI
				if (n_seq->op->cc->sc)
				{
					x = 0;
					if (n_seq->op->cc->sc->next)
					{
						while (n_seq->op->cc->sc->next)
						{
							printf("SC->NEXT NUMBER %d\n", x++);
							n_seq->op->cc->sc = n_seq->op->cc->sc->next;
						}
					}
					printf("%d N_SEQ->OP->CC->SC->ARG TROUVE\n", x);
					printf("N_SEQ->OP->CC->SC->ARG == %s\n", n_seq->op->cc->sc->arg);
					n_seq->op->cc->sc->close++;
				//	if (!(n_seq->op->cc->sc = ft_malloc_sc()))
				//		return (1);
				}
				else if (n_seq->op->cc)
				{
//					while (n_seq->op->cc->next)
//						n_seq->op->cc = n_seq->op->cc->next;
					printf("N_SEQ->OP->CC->SC NON TROUVE\n");
					if (!(n_seq->op->cc->sc = ft_malloc_sc()))
					{
						printf("BUG MALLOC_SC\n");
						return (1);
					}
				}
				else
				{
				}
				n_seq->op->cc->sc->arg = ft_strdup(";");
				n_seq->op->cc->sc->token = SEMI;
			}
			else
			{
				printf("N_SEQ->OP->CC NON TROUVE\n");
				if (!(n_seq->next = ft_malloc_seq(1)))
					return (1);
//				(*n_seq)->close = 1;
			}
		}
		else
		{
			printf("';' !(N_SEQ->OP && !N_SEQ->CLOSE)\n");
			if (!(n_seq->next = ft_malloc_seq(1)))
				return (1);
//			(*n_seq)->close = 1;
		}
	}
	else
	{
		printf("';' PAS DE MAILLON TROUVE\n");
		if (!(*b_seq = ft_malloc_seq(1)))
			return (1);
//		(*n_seq)->close = 1;
	}
	printf("MANAGE_SEMI NUMBER %d FINISH\n", i);
	return (0);
}

int			ft_manage_if(t_seq **b_seq)
{
	t_seq		*n_seq;
	t_seq		*test;

	static int		i = 0;
	printf("MANAGE_IF NUMBER %d\n", i);
	i++;
	n_seq = *b_seq;
	test = n_seq;
	if (n_seq)
	{
		printf("'IF' MAILLON TROUVE\n");
		while (n_seq->next)
			n_seq = n_seq->next;
		if (n_seq->close == 1)
		{
			printf("N_SEQ->CLOSE == 1\n");
			n_seq->next = ft_malloc_seq(0);
			n_seq->next->op = ft_malloc_op();
			n_seq->next->op->cc = ft_malloc_cc();
			n_seq->next->op->cc->key = IF;
		}
		else if (n_seq->op)
		{
			printf("N_SEQ->OP TROUVE[[ EN COURS ]]\n");
		}
		else
		{
			printf("LE ELSE[[ EN COURS ]]\n");
		}
	}
	else
	{
		printf("'IF' PAS DE MAILLON TROUVE\n");
		*b_seq = ft_malloc_seq(0);
		(*b_seq)->op = ft_malloc_op();
		(*b_seq)->op->cc = ft_malloc_cc();
		(*b_seq)->op->cc->key = IF;
	}
	return (0);
}

int			ft_attribute_token(t_seq **b_seq, char *name, enum e_token token)
{
	t_seq		*n_seq;
	int			ret;
	t_sc		old_token;

	static int		i = 0;
	printf("ATTRIBUTE_TOKEN NUMBER %d\n", i);
	printf("RECHERCHE ");
	i++;

	n_seq = NULL;
	if (token == SEMI)
	{
		printf("TOKEN == SEMI\n");
		if (ft_manage_semi(&(*b_seq)))
			return (1);
	}
	else if (token == IF)
	{
		printf("TOKEN == IF\n");
		if (ft_manage_if(&(*b_seq)))
			return (1);
	}
	else if (token == THEN)
	{
		printf("TOKEN == THEN\n");
	}
	else if (token == ELIF)
	{
		printf("TOKEN == ELIF\n");
	}
	else if (token == ELSE)
	{
		printf("TOKEN == ELSE\n");
	}
	else if (token == FI)
	{
		printf("TOKEN == FI\n");
	}
	else if (token == DO)
	{
		printf("TOKEN == DO\n");
	}
	else if (token == DONE)
	{
		printf("TOKEN == DONE\n");
	}
	else if (token == CASE)
	{
		printf("TOKEN == CASE\n");
	}
	else if (token == ESAC)
	{
		printf("TOKEN == ESAC\n");
	}
	else if (token == WHILE)
	{
		printf("TOKEN == WHILE\n");
	}
	else if (token == UNTIL)
	{
		printf("TOKEN == UNTIL\n");
	}
	else if (token == FOR)
	{
		printf("TOKEN == FOR\n");
	}
	return (0);
}

int			ft_parse(t_seq **b_seq, char *name, enum e_token token)
{
	ft_attribute_token(&(*b_seq), name, token);
	return (0);
}

t_seq		*ft_manage_parsing(t_lex lex)
{
	int				i;
	t_seq			*b_seq;

	b_seq = NULL;
	i = -1;
	while (lex.name[++i])
	{
		printf("---------------------------------------------\n");
		printf("BOUCLE LEX NUMBER %d NAME == [%s]\n", i, lex.name[i]);
		if (ft_parse(&b_seq, lex.name[i], lex.token[i]))
			return (NULL);
	}
	return (b_seq);
}
