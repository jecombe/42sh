/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 17:48:00 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./parsing.h"

t_seq		*ft_search_now(t_seq *b_seq)
{
	t_seq	*n_seq;

	n_seq = b_seq;
	if (n_seq)
	{
		while (n_seq->next)
			n_seq = n_seq->next;
		if (n_seq->op)
		{
			while (n_seq->op->next)
				n_seq->op = n_seq->op->next;
			if (n_seq->op->sc)
				while (n_seq->op->sc->next)
					n_seq->op->sc = n_seq->op->sc->next;
			else if (n_seq->op->cc)
			{
				while (n_seq->op->cc->next_out)
					n_seq->op->cc = n_seq->op->cc->next_out;
				while (n_seq->op->cc->next_in)
					n_seq->op->cc = n_seq->op->cc->next_in;
				if (n_seq->op->cc->sc)
					while (n_seq->op->cc->sc->next)
						n_seq->op->cc->sc = n_seq->op->cc->sc->next;
			}
		}
	}
	return (n_seq);
}

int			ft_init_bseq(t_seq **b_seq, t_seq **n_seq)
{
	if (!(*b_seq = malloc(sizeof(t_seq))))
		return (1);
	(*b_seq)->op = NULL;
	(*b_seq)->next = NULL;
	(*b_seq)->prev = NULL;
	*n_seq = *b_seq;
	return (0);
}

int			ft_attribute_token(t_seq **n_seq)
{

	return (0);
}

int			ft_parse(t_seq **b_seq, char *name, enum e_token token)
{
	t_seq	*n_seq;

	if (*b_seq)
		n_seq = ft_search_now(*b_seq);
	else
		if (ft_init_bseq(&(*b_seq), &n_seq))
			return (1);
	ft_attribute_token(&n_seq);
	if (!(*b_seq))
		*b_seq = n_seq;
	return (0);
}

t_seq		*ft_manage_parsing(t_lex lex)
{
	int		i;
	t_seq	*b_seq;

	b_seq = NULL;
	i = -1;
	while (lex.name[++i])
		if (ft_parse(&b_seq, lex.name[i], lex.token[i]))
			return (NULL);
	return (b_seq);
}
