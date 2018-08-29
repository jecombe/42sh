/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_n_op.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 00:42:35 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 11:24:59 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"

void		ft_free_n_op(t_op **n_op)
{
	if (*n_op)
	{
		if ((*n_op)->cmd)
			ft_tabdel(&(*n_op)->cmd);
		if ((*n_op)->cmd)
			ft_free_b_redirect(&(*n_op)->redirect);
		if ((*n_op)->next && (*n_op)->prev)
		{
			(*n_op)->prev->next = (*n_op)->next;
			(*n_op)->next->prev = (*n_op)->prev;
		}
		free(*n_op);
		*n_op = NULL;
	}
}

int			del_nop_empty(t_op **n_op, t_op **tmp, t_op **b_op)
{
	if ((*n_op)->next || (*n_op)->prev)
	{
		*tmp = (*n_op)->next ? (*n_op)->next : NULL;
		if (!(*n_op)->prev)
		{
			*b_op = (*b_op)->next;
			(*b_op)->prev = NULL;
		}
		else if (!(*n_op)->next)
		{
			(*n_op)->prev->token = TOKEN;
			(*n_op)->prev->next = NULL;
		}
		else if ((*n_op)->prev && (*n_op)->next)
		{
			(*n_op)->prev->next = *tmp;
			(*tmp)->prev = (*n_op)->prev;
			(*n_op)->prev->token = (*n_op)->token;
		}
		ft_free_n_op(&(*n_op));
	}
	else
		return (1);
	return (0);
}
