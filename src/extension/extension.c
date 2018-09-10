/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 05:00:48 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/31 11:44:46 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	init_parcour_tab(t_bquote **i)
{
	if (!(*i = malloc(sizeof(t_bquote))))
		return (1);
	(*i)->begin = 0;
	(*i)->i = -1;
	(*i)->dquote = 0;
	return (0);
}

static int	ft_parcour_tab(char ***cmd)
{
	t_bquote	*i;
	int			ret;

	if (init_parcour_tab(&i))
		return (1);
	if (*cmd)
		while (*cmd && (*cmd)[++i->i])
		{
			i->j = 0;
			while ((*cmd)[i->i][i->j])
			{
				if ((ret = backslash_manager(&(*cmd), &i)))
					;
				else if ((ret = ft_manage_quote(cmd, &i)))
					;
				else
					if (manage_tild_and_dollars(cmd, &i))
						return (1);
				if (!(*cmd) || !(*cmd)[i->i] || ret == -1)
					return (ret == -1 ? 1 : 0);
			}
		}
	return (0);
}

static int	ft_parcour_op(t_op **b_op)
{
	t_op		*n_op;

	n_op = *b_op;
	while (n_op)
	{
		if (n_op->cmd)
			if (ft_parcour_tab(&n_op->cmd))
				return (1);
		n_op = n_op->next;
	}
	return (0);
}

int			extension(t_seq **b_seq)
{
	t_seq		*n_seq;
	int i = 0;

	n_seq = *b_seq;
	while (n_seq)
	{
		if (n_seq->op)
			if (ft_parcour_op(&n_seq->op))
				return (1);
		n_seq = n_seq->next;
	}
	return (extension_error(b_seq));
}
