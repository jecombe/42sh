/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_free_n_redirect.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 01:55:56 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 02:00:03 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		ft_free_n_redirect(t_redirect **n_redirect)
{
	if (*n_redirect)
	{
		if ((*n_redirect)->file)
			ft_strdel(&(*n_redirect)->file);
		if ((*n_redirect)->next && (*n_redirect)->prev)
		{
			(*n_redirect)->next->prev = (*n_redirect)->prev;
			(*n_redirect)->prev->next = (*n_redirect)->next;
		}
		free(*n_redirect);
		*n_redirect = NULL;
	}
}
