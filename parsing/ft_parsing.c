/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/11 21:01:40 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./parsing.h"

t_seq		*ft_malloc_seq(int version)
{
	static int		i = 0;
	t_seq	*new;

	if (!(new = malloc(sizeof(t_seq))))
		return (NULL);
	new->op = NULL;
	new->close = 0;
	new->next = NULL;
	new->prev = NULL;
	if (version == 1)
		new->close = 1;
	printf("SEQUENCE NUMBER %d\n", i);
	i++;
	return (new);
}

t_cc		*ft_malloc_cc(void)
{
	t_cc		*new;
	t_cc		*now;

	if (!(new = malloc(sizeof(t_cc))))
		return (NULL);
	new->next_in = NULL;
	new->next_out = NULL;
	new->sc = NULL;
	new->close = 0;
	new->key = NUL;
	new->prev_in = NULL;
	new->prev_out = NULL;
	return (new);
}

t_op		*ft_malloc_op(void)
{
	t_op	*new;

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

	n_seq = *b_seq;
	if (n_seq)
		printf("';' MAILLON TROUVE\n");
	else
		printf("';' PAS DE MAILLON TROUVE\n");
	if (n_seq)
	{
		while (n_seq->next)
			n_seq = n_seq->next;
		if (n_seq->op && !n_seq->close)
		{
			while (n_seq->op->next)
				n_seq->op = n_seq->op->next;
			if (n_seq->op->cc)
			{
			printf("CC TROUVE\n");
				while (n_seq->op->cc->next_out)
				{
					printf("NEXT_OUT\n");
					n_seq->op->cc = n_seq->op->cc->next_out;
				}
				while (n_seq->op->cc->next_in)
				{
					printf("NEXT_IN\n");
					n_seq->op->cc = n_seq->op->cc->next_in;
				}
					//PB ICI
				printf("55555555555555555555555\n");
				if (n_seq->op->cc->sc)
				{
					printf("00000000000000\n");
					printf("TEST TOKEN == %s\n", n_seq->op->cc->sc->arg);
					int i = 0;
					while (n_seq->op->cc->sc->next)
					{
						printf("SC->NEXT NUMBER %d\n", i++);
						n_seq->op->cc->sc = n_seq->op->cc->sc->next;
					}
					if (!(n_seq->op->cc->sc = ft_malloc_sc()))
						return (1);
				}
				else
				{
					printf("1111111111111111\n");
					if (!(n_seq->op->cc->sc = ft_malloc_sc()))
					{
						printf("BUG MALLOC_SC\n");
						return (1);
					}
				}
				n_seq->op->cc->sc->arg = ft_strdup(";");
				n_seq->op->cc->sc->token = SEMI;
			}
			else
			{
				if (!(n_seq->next = ft_malloc_seq(1)))
					return (1);
//				(*n_seq)->close = 1;
			}
		}
		else
		{
			if (!(n_seq->next = ft_malloc_seq(1)))
				return (1);
//			(*n_seq)->close = 1;
		}
	}
	else
	{
		if (!(*b_seq = ft_malloc_seq(1)))
			return (1);
//		(*n_seq)->close = 1;
	}
	return (0);
}

int			ft_manage_if(t_seq **b_seq)
{
	t_seq		*n_seq;
	t_seq		*test;

	printf("00000000000000000000000000000000000000000000000000000000000000000\n");
	n_seq = *b_seq;
	test = n_seq;
	if (test)
		printf("TEST TROUVE\n");
	else
		printf("BUG\n");
	if (n_seq)
	{
		while (n_seq->next)
			n_seq = n_seq->next;
		if (n_seq->close == 1)
		{
			printf("NOUVEAU MAILLON\n");
			n_seq->next = ft_malloc_seq(0);
			n_seq->next->op = ft_malloc_op();
			n_seq->next->op->cc = ft_malloc_cc();
			n_seq->next->op->cc->key = IF;
		}
		else if (n_seq->op)
		{
			printf("NOUVELLE CC\n");
			if (n_seq->op)
				;
		}
		else
		{
			printf("LE ELSE\n");
		}
	}
	else
	{
		printf("INITIALISATION\n");
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


	n_seq = NULL;
	if (token == SEMI)
	{
		if (ft_manage_semi(&(*b_seq)))
			return (1);
	}
	else if (token == IF)
	{
		printf("IF TROUVE\n");
		if (ft_manage_if(&(*b_seq)))
			return (1);
	}
	else if (token == THEN)
	{
	}
	else if (token == ELIF)
	{
	}
	else if (token == ELSE)
	{
	}
	else if (token == FI)
	{
	}
	else if (token == DO)
	{
	}
	else if (token == DONE)
	{
	}
	else if (token == CASE)
	{
	}
	else if (token == ESAC)
	{
	}
	else if (token == WHILE)
	{
	}
	else if (token == UNTIL)
	{
	}
	else if (token == FOR)
	{
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
		printf("NAME == %s\n", lex.name[i]);
		if (ft_parse(&b_seq, lex.name[i], lex.token[i]))
			return (NULL);
	}
	return (b_seq);
}
