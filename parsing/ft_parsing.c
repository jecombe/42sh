/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 04:41:51 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./parsing.h"

t_seq		*ft_malloc_seq(void)
{
	static int		i = 0;
	t_seq	*new;

	printf("MALLOC_SEQ NUMBER %d\n", i);
	if (!(new = malloc(sizeof(t_seq))))
		return (NULL);
	new->token = TOKEN;
	new->op = NULL;
	new->next = NULL;
	new->prev = NULL;
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

	static int		i = 0;
	printf("MALLOC_OP NUMBER %d\n", i);
	i++;
	if (!(new = malloc(sizeof(t_op))))
		return (NULL);
	new->sc = NULL;
	new->token = TOKEN;
	new->cc = NULL;
	new->next = NULL;
	new->prev = NULL;
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
	new->arg = NULL;
	new->close = 0;
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
			if (!(n_seq->next = ft_malloc_seq()))
				return (1);
	}
	else
	{
		if (!(n_seq = ft_malloc_seq()))
			return (1);
		*b_seq = n_seq;
	}
	n_seq->token = token;
	return (0);
}

int			ft_manage_op(t_seq **b_seq, e_token token)
{
	t_seq			*n_seq;

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
	}
	else if (n_seq->op)
	{
		while (n_seq->op->next)
			n_seq->op = n_seq->op->next;
		if (!(n_seq->op->next = ft_malloc_op()))
			return (1);
		n_seq->op->next->prev = n_seq->op;
		n_seq->op = n_seq->op->next;
	}
	n_seq->op->token = token;
	return (0);
}

int			ft_manage_word(t_seq **b_seq, e_token token)
{
	t_seq			*n_seq;

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
	}
	else if (n_seq->op)
	{
		while (n_seq->op->next)
			n_seq->op = n_seq->op->next;
		if (!(n_seq->op->next = ft_malloc_op()))
			return (1);
		n_seq->op->next->prev = n_seq->op;
		n_seq->op = n_seq->op->next;
	}
	if ((n_seq->op->token || !n_seq->op->sc) && !n_seq->op->cc)
	{
		if (n_seq->op->token)
		{
			n_seq->op->next = ft_malloc_op();
			n_seq->op->next->prev = n_seq->op;
			n_seq->op = n_seq->op->next;
		}
		while (n_seq->op->sc->next)
			n_seq->op->sc = n_seq->op->sc->next;
	}
	else if (n_seq->op->cc)
		;
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
	else
	{
		if (!(ft_manage_word(&(*b_seq), token)))
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
		printf("---------------------------------------------\n");
		printf("BOUCLE LEX NUMBER %d NAME == [%s]\n", i, lex.name[i]);
		if (ft_attribute_token(&b_seq, lex.name[i], lex.token[i]))
			return (NULL);
	}
	return (b_seq);
}
