/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 05:00:48 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 11:19:56 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"
#include "../../include/init.h"

int			ft_parcour_tab(char ***cmd)
{
//	int			i;
//	int			j;
	int			dquote;
	t_bquote	*i;

	if (!(i = malloc(sizeof(t_bquote))))
		return (1);
	i->begin = 0;
	dquote = 0;
	i->i = -1;
	if (*cmd)
		while (*cmd && (*cmd)[++i->i])
		{
			i->j = 0;
			while ((*cmd)[i->i][i->j])
			{
				if ((*cmd)[i->i][i->j] == '\\')
					backslash_manager(&(*cmd), i->i, &i->j, dquote);
				else if ((*cmd)[i->i][i->j] == '\'' && !dquote && !i->begin)
					ft_manage_quote(&(*cmd), i->i, &i->j, ft_replace_quote);
				else if ((*cmd)[i->i][i->j] == '"' && !i->begin)
				{
					ft_manage_quote(&(*cmd), i->i, &i->j, ft_replace_dquote);
					dquote = dquote == 1 ? 0 : 1;
				}
				else if ((*cmd)[i->i][i->j] == '`')
				{
					if (i->begin == 0)
					{
						i->begin = i->j == 0 ? -1 : i->j;
						i->j++;
					}
					else
					{
						i->begin = i->begin == -1 ? 0 : i->begin;
						bquote_manager(&(*cmd), &i->j, &i->i, i->begin);
						i->begin = 0;
					}
				}
				else if ((*cmd)[i->i][i->j] == '~' && i->j == 0)
				{
					if (add_tild(&(*cmd)[i->i], &i->j))
						return (1);
				}
				else if ((*cmd)[i->i][i->j] == '$')
					ft_dollar(cmd, &i->i, &i->j);
				else
					i->j++;
				if (!(*cmd) || !(*cmd)[i->i])
					return (0);
			}
		}
	return (0);
}

int			ft_parcour_op(t_op **b_op)
{
	t_op		*n_op;

	n_op = *b_op;
	while (n_op)
	{
		if (n_op->cmd)
			ft_parcour_tab(&n_op->cmd);
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
