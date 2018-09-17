/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_attrib_parsing.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/30 06:37:15 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 04:40:21 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			ft_attrib_last_seq(t_seq **b_seq, t_seq **n_seq)
{
	if (*b_seq)
	{
		*n_seq = *b_seq;
		while ((*n_seq)->next)
			*n_seq = (*n_seq)->next;
		if ((*n_seq)->token != TOKEN)
		{
			if (!((*n_seq)->next = ft_malloc_seq()))
				return (1);
			(*n_seq)->next->prev = *n_seq;
			(*n_seq) = (*n_seq)->next;
		}
	}
	else
	{
		if (!(*b_seq = ft_malloc_seq()))
			return (1);
		*n_seq = *b_seq;
	}
	return (0);
}
int			ft_attrib_last_op(t_seq **b_seq, t_op **ret_op)
{
	t_seq		*n_seq;
	t_op		*n_op;

	if (ft_attrib_last_seq(&(*b_seq), &n_seq))
		return (1);
	if (!n_seq->op)
		if (!(n_seq->op = ft_malloc_op()))
			return (1);
	n_op = n_seq->op;
	while (n_op->next)
		n_op = n_op->next;
	*ret_op = n_op;
	return (0);
}

int			ft_attrib_next_op(t_op **n_op)
{
	(*n_op)->next = ft_malloc_op();
	(*n_op)->next->prev = *n_op;
	*n_op = (*n_op)->next;
	return (0);
}

int			ft_attrib_last_redirect(t_op **n_op, t_redirect **n_redirect)
{
	if (!(*n_op)->redirect)
		if (!((*n_op)->redirect = ft_malloc_redirect()))
			return (1);
	*n_redirect = (*n_op)->redirect;
	while ((*n_redirect)->next)
		*n_redirect = (*n_redirect)->next;
	return (0);
}

int			ft_attrib_next_redirect(t_redirect **n_redirect)
{
	if (!((*n_redirect)->next = ft_malloc_redirect()))
		return (1);
	(*n_redirect)->next->prev = *n_redirect;
	*n_redirect = (*n_redirect)->next;
	return (0);
}
