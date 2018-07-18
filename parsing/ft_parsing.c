/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 03:53:57 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./parsing.h"

t_seq		*ft_malloc_seq(void)
{
	t_seq	*new;

	if (!(new = malloc(sizeof(t_seq))))
		return (NULL);
	new->token = TOKEN;
	new->op = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cc		*ft_malloc_cc(void)
{
	t_cc		*new;
	t_cc		*now;

	if (!(new = malloc(sizeof(t_cc))))
		return (NULL);
	new->key = TOKEN;
	new->sc = NULL;
	new->open = 0;
	new->close = 0;
	new->next_in = NULL;
	new->next_out = NULL;
	new->prev_in = NULL;
	new->prev_out = NULL;
	return (new);
}

t_op		*ft_malloc_op(void)
{
	t_op	*new;

	if (!(new = malloc(sizeof(t_op))))
		return (NULL);
	new->token = TOKEN;
	new->sc = NULL;
	new->cc = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_sc		*ft_malloc_sc(void)
{
	t_sc		*new;

	if (!(new = malloc(sizeof(t_cc))))
		return (NULL);
	new->arg = NULL;
	new->token = TOKEN;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int			ft_manage_seq(t_seq **b_seq, e_token token)
{
	t_seq			*n_seq;

	if (*b_seq)
	{
		n_seq = *b_seq;
		while (n_seq->next)
			n_seq = n_seq->next;
		if (n_seq->token != TOKEN)
		{
			if (!(n_seq->next = ft_malloc_seq()))
				return (1);
			n_seq->next->prev = n_seq;
			n_seq = n_seq->next;
		}
	}
	else
	{
		if (!(*b_seq = ft_malloc_seq()))
			return (1);
		n_seq = *b_seq;
	}
	n_seq->token = token;
	return (0);
}

int			ft_manage_op(t_seq **b_seq, e_token token)
{
	t_seq			*n_seq;
	t_op			*n_op;

	if (!(*b_seq))
		if (!(*b_seq = ft_malloc_seq()))
			return (1);
	n_seq = *b_seq;
	while (n_seq->next)
		n_seq = n_seq->next;
	if ((!(n_seq->op) && n_seq->token == TOKEN) || n_seq->token != TOKEN)
	{
		if (n_seq->token != TOKEN)
		{
			if (!(n_seq->next = ft_malloc_seq()))
				return (1);
			n_seq->next->prev = n_seq;
			n_seq = n_seq->next;
		}
		if (!(n_seq->op = ft_malloc_op()))
			return (1);
		n_op = n_seq->op;
	}
	else if (n_seq->op)
	{
		n_op = n_seq->op;
		while (n_op->next)
			n_op = n_op->next;
		if (!(n_op->next = ft_malloc_op()))
			return (1);
		n_op->next->prev = n_op;
		n_op = n_op->next;
	}
	else
		printf("BBBBBBBBBBBUUUUUUUUUUUUUUUUUGGGGGGGGGGGGGGG\n");
	n_op->token = token;
	return (0);
}

int			ft_manage_word(t_seq **b_seq, char *name, e_token token)
{
	t_seq			*n_seq;
	t_op			*n_op;
	t_sc			*n_sc;

	if (!(*b_seq))
	{
//		if (ft_manage_op(&(*b_seq), TOKEN))
		*b_seq = ft_malloc_seq();
//			return (1);
	}
	n_seq = *b_seq;
	while (n_seq->next)
	{
		n_seq = n_seq->next;
	}
	if (!n_seq->op || n_seq->token != TOKEN)
	{
		if (n_seq->token != TOKEN)
		{
			n_seq->next = ft_malloc_seq();
			n_seq->next->prev = n_seq;
			n_seq = n_seq->next;
		}
		n_seq->op = ft_malloc_op();
	}
	n_op = n_seq->op;
	while (n_op->next)
		n_op = n_op->next;
	if (n_op->token != TOKEN)
	{
		n_op->next = ft_malloc_op();
		n_op->next->prev = n_op;
		n_op = n_op->next;
		n_op->sc = ft_malloc_sc();
		n_op->sc->arg = ft_strdup(name);
		n_op->sc->token = token;
	}
	else if (n_op->cc)
		;
	else
	{
		if (!n_op->sc)
			n_op->sc = ft_malloc_sc();
		n_sc = n_op->sc;
		while (n_sc->next)
			n_sc = n_sc->next;
		if (n_sc->arg || n_sc->token != TOKEN)
		{
			n_sc->next = ft_malloc_sc();
			n_sc->next->prev = n_sc;
			n_sc = n_sc->next;
		}
		n_sc->arg = ft_strdup(name);
		n_sc->token = token;
	}
	return (0);
}

int			ft_attribute_token(t_seq **b_seq, char *name, e_token token)
{
	if (token == SEMI || token == AND)
	{
		if (ft_manage_seq(&(*b_seq), token))
			return (1);
	}
	else if (token == AND_IF || token == OR_IF || token == NOT)
	{
		if (ft_manage_op(&(*b_seq), token))
			return (1);
	}
	else if (token >= 276 && token <= 284)
	{

	}
	else
	{
		if (ft_manage_word(&(*b_seq), name, token))
			return (1);
	}
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
		if (ft_attribute_token(&b_seq, lex.name[i], lex.token[i]))
			return (NULL);
	}
	return (b_seq);
}
