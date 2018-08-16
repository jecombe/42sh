/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstdel.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:10:26 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 11:37:53 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*after;
	t_list	*tmp;

	tmp = *alst;
	while (tmp)
	{
		after = tmp->next;
		del(tmp->content, tmp->content_size);
		free(tmp);
		tmp = after;
	}
	*alst = (NULL);
}
