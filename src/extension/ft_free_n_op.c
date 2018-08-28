/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_n_op.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 00:42:35 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 00:49:55 by gmadec      ###    #+. /#+    ###.fr     */
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
