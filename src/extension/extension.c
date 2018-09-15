/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 05:00:48 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/15 05:09:46 by gmadec      ###    #+. /#+    ###.fr     */
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

static int	return_parcour_tab(char **cmd, int ret)
{
	if (!cmd)
		return (2);
	return (ret == -1 ? 1 : 0);
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
					return (return_parcour_tab(*cmd, ret));
			}
		}
	return (0);
}

static int	ft_parcour_op(t_op **b_op)
{
	t_op		*n_op;
	int			ret;

	n_op = *b_op;
	while (n_op)
	{
		if (n_op->cmd)
		{
			if ((ret = ft_parcour_tab(&n_op->cmd)) != 0 && ret != 2)
				return (1);
			else if (ret == 2)
			{
				if (!n_op->redirect)
					return (2);
			}
		}
		n_op = n_op->next;
	}
	return (0);
}

int			extension(t_seq **b_seq)
{
	t_seq		*n_seq;
	int			ret;

	n_seq = *b_seq;
	while (n_seq)
	{
	printf("OKOK\n");
		if (n_seq->op)
			if ((ret = ft_parcour_op(&n_seq->op)) != 0 && ret != 2)
				return (1);
		if (ret == 2)
		{
			if (ft_free_n_seq(&n_seq, b_seq) == 1)
				return (1);
		}
		else
			n_seq = n_seq->next;
	}
	ret = 0;
	return (extension_error(b_seq, ret));
}
