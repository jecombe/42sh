/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_parse.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/30 05:32:17 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 04:43:41 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		ft_free_b_redirect(t_redirect **b_redirect)
{
	t_redirect	*n_redirect;

	n_redirect = *b_redirect;
	while (n_redirect)
	{
		*b_redirect = n_redirect;
		ft_strdel(&n_redirect->file);
		n_redirect = (*b_redirect)->next;
		free(*b_redirect);
		*b_redirect = NULL;
	}
}

void		ft_free_b_op(t_op **b_op)
{
	t_op		*n_op;

	n_op = *b_op;
	while (n_op)
	{
		*b_op = n_op;
		ft_tabdel(&n_op->cmd);
		ft_free_b_redirect(&(*b_op)->redirect);
		n_op = (*b_op)->next;
		free(*b_op);
		*b_op = NULL;
	}
}

int			ft_free_b_seq(t_seq **b_seq)
{
	t_seq		*n_seq;

	n_seq = *b_seq;
	while (n_seq)
	{
		*b_seq = n_seq;
		ft_free_b_op(&(*b_seq)->op);
		n_seq = (*b_seq)->next;
		free(*b_seq);
		*b_seq = NULL;
	}
	return (0);
}
