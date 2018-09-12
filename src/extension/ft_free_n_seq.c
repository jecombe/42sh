/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_n_seq.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 00:33:33 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 03:49:14 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		ft_free_n_seq(t_seq **n_seq)
{
	if (*n_seq)
	{
		if ((*n_seq)->op)
			ft_free_b_op(&(*n_seq)->op);
		if ((*n_seq)->next && (*n_seq)->prev)
		{
			(*n_seq)->next->prev = (*n_seq)->prev;
			(*n_seq)->prev->next = (*n_seq)->next;
		}
		else if ((*n_seq)->prev)
			(*n_seq)->prev->next = NULL;
		free(*n_seq);
		*n_seq = NULL;
	}
}
