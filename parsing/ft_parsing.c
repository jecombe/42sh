/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/28 04:41:07 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./parsing.h"

int			ft_malloc_seq(t_seq **now)
{
	t_seq	*new;

	if (!(new = malloc(sizeof(t_seq))))
		return (1);
	new->op = NULL;
	new->close = 0;
	new->next = NULL;
	if (!(*now))
	{
		new->next = NULL;
	}
	else
	{
		new->prev = *now;
		(*now)->next = new;
	}
	*now = new;
	return (0);
}

int			ft_malloc_cc(t_cc **now, int v)
{
	t_cc		*new;

	if (!(new = malloc(sizeof(t_cc))))
		return (1);
	new->next_in = NULL;
	new->next_out = NULL;
	if (v == 0)
	{
		new->prev_in = NULL;
		new->prev_out = NULL;
	}
	else if (v == 1)
	{
		new->prev_in = *now;
		new->prev_out = NULL;
		(*now)->next_in = new;
	}
	else if (v == 2)
	{
		new->prev_out = *now;
		new->prev_in = NULL;
		(*now)->next_out = new;
	}
	*now = new;
	return (0);
}

int			ft_malloc_op(t_op **now)
{
	t_op	*new;

	if (!(new = malloc(sizeof(t_op))))
		return (1);
	new->op = NUL;
	new->close = 0;
	new->sc = NULL;
	new->cc = NULL;
	new->next = NULL;
	if (!(*now))
	{
		new->prev = NULL;
	}
	else
	{
		new->prev = *now;
		(*now)->next = new;
	}
	*now = new;
	return (0);
}

int			ft_malloc_sc(t_sc **now)
{
	t_sc		*new;

	if (!(new = malloc(sizeof(t_cc))))
		return (1);
	new->next = NULL;
	new->arg = NULL;
	new->token = NUL;
	if (!(*now))
	{
		new->prev = NULL;
	}
	else
	{
		(*now)->next = new;
		new->prev = (*now);
	}
	(*now) = new;
	return (0);
}

int			ft_manage_semi(t_seq **b_seq, t_seq **n_seq)
{
	*n_seq = *b_seq;
	if (*n_seq)
	{
		while ((*n_seq)->next)
			*n_seq = (*n_seq)->next;
		if ((*n_seq)->op && !(*n_seq)->close)
		{
			while ((*n_seq)->op->next)
				(*n_seq)->op = (*n_seq)->op->next;
			if ((*n_seq)->op->cc)
			{
				while ((*n_seq)->op->cc->next_out)
					(*n_seq)->op->cc = (*n_seq)->op->cc->next_out;
				while ((*n_seq)->op->cc->next_in)
					(*n_seq)->op->cc = (*n_seq)->op->cc->next_in;
				if ((*n_seq)->op->cc->sc)
				{
					printf("00000000000000\n");
					while ((*n_seq)->op->cc->sc->next)
						(*n_seq)->op->cc->sc = (*n_seq)->op->cc->sc->next;
					if (ft_malloc_sc(&(*n_seq)->op->cc->sc))
						return (1);
				}
				else
				{
					printf("1111111111111111\n");
					if (ft_malloc_sc(&(*n_seq)->op->cc->sc))
						return (1);
				}
				(*n_seq)->op->cc->sc->arg = ft_strdup(";");
				(*n_seq)->op->cc->sc->token = SEMI;
			}
			else
			{
				if (ft_malloc_seq(&(*b_seq)))
					return (1);
				(*n_seq)->close = 1;
			}
		}
		else
		{
			if (ft_malloc_seq(&(*b_seq)))
				return (1);
			(*b_seq)->close = 1;
		}
	}
	else
	{
		if (ft_malloc_seq(&(*b_seq)))
			return (1);
		(*b_seq)->close = 1;
	}
	return (0);
}

int			ft_manage_if(t_seq **b_seq, t_seq **n_seq)
{
	*n_seq = *b_seq;
	if (*n_seq)
	{
		if ((*n_seq)->close == 1)
			printf("NOUVEAU MAILLON\n");
		else
			printf("NOUVELLE CC\n");
	}
	else
	{
		ft_malloc_seq(&(*b_seq));
		ft_malloc_op(&(*b_seq)->op);
		ft_malloc_cc(&(*b_seq)->op->cc, 0);
		(*b_seq)->op->cc->key = IF;
	}
	return (0);
}

int			ft_attribute_token(t_seq **b_seq, char *name, enum e_token token)
{
	t_seq		*n_seq;
	int			ret;


	n_seq = NULL;
	if (token == SEMI)
	{
		if (ft_manage_semi(&(*b_seq), &n_seq))
			return (1);
	}
	else if (token == IF)
	{
		printf("IF TROUVE\n");
		if (ft_manage_if(&(*b_seq), &n_seq))
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

int			ft_parse(t_seq **b_seq, char *name, enum e_token token, enum e_token old_token)
{
	ft_attribute_token(&(*b_seq), name, token);
	return (0);
}

t_seq		*ft_manage_parsing(t_lex lex)
{
	int				i;
	t_seq			*b_seq;
	enum e_token	old_token;

	b_seq = NULL;
	i = -1;
	old_token = NUL;
		printf("NAME\n");
	while (lex.name[++i])
	{
		printf("NAME == %s\n", lex.name[i]);
		if (ft_parse(&b_seq, lex.name[i], lex.token[i], old_token))
			return (NULL);
		old_token = lex.token[i];
	}
	return (b_seq);
}
