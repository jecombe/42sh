/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_n_seq.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 00:33:33 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 08:57:54 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void	ft_free_n_seq_annex(t_seq **n_seq, t_seq **b_seq, int *ret)
{
	if ((*n_seq)->next && (*n_seq)->prev)
	{
		(*n_seq)->next->prev = (*n_seq)->prev;
		(*n_seq)->prev->next = (*n_seq)->next;
	}
	else if ((*n_seq)->prev)
		(*n_seq)->prev->next = NULL;
	else if ((*n_seq)->next)
	{
		*b_seq = (*n_seq)->next;
		(*b_seq)->prev = NULL;
	}
	else
		*ret = 1;
}

int			ft_free_n_seq(t_seq **n_seq, t_seq **b_seq)
{
	int		ret;

	ret = 0;
	if (*n_seq)
	{
		if ((*n_seq)->op)
			ft_free_b_op(&(*n_seq)->op);
		ft_free_n_seq_annex(n_seq, b_seq, &ret);
		if (ret != 1)
		{
			free(*n_seq);
			*n_seq = NULL;
		}
	}
	if (ret == 1)
		ft_free_b_seq(b_seq);
	return (ret);
}
