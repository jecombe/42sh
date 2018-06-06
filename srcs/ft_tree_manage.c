/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tree_manage.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 23:23:23 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/23 16:11:16 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

t_token			*ft_token_new(void)
{
	t_token		*element;

	if (!(element = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	element->id = NULL;
	element->quote = '\0';
	element->cmdarg = NULL;
	element->next = NULL;
	return (element);
}

void			ft_token_add(t_token **tbegin, t_token *element)
{
	while (*tbegin)
		tbegin = &(*tbegin)->next;
	element->next = *tbegin;
	*tbegin = element;
}

int				ft_token_delone(t_token **element)
{
	ft_strdel(&(*element)->id);
	free(*element);
	return (1);
}

void			ft_token_del(t_token *tokenlst)
{
	t_token		*next;

	while (tokenlst)
	{
		while (tokenlst->cmdarg)
		{
			next = tokenlst->cmdarg->next;
			ft_token_delone(&tokenlst->cmdarg);
			tokenlst->cmdarg = next;
		}
		next = tokenlst->next;
		ft_token_delone(&tokenlst);
		tokenlst = next;
	}
}
