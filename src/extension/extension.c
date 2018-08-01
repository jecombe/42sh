/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 05:00:48 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 05:16:59 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"

void		ft_braquet_quote(char *str, int *j)
{
	while (str[*j] == '\'')
		*j = *j + 1;
}

int			ft_add_tild(char **str, int *j)
{
	return (0);
}

int			ft_echap(char *str, int *j)
{
	return (0);
}

int			ft_parcour_tab(char ***cmd)
{
	int			i;
	int			j;
	int			k;

	i = -1;
	while ((*cmd)[++i])
	{
		j = -1;
		while ((*cmd)[++j])
		{
			if ((*cmd)[i][j] == '\\')
				ft_echap((*cmd)[i], &j);
			if ((*cmd)[i][j] == '\'')
				ft_braquet_quote((*cmd)[i] + j, &i);
			if ((*cmd)[i][j] == '\\')
				ft_echap((*cmd)[i], &j);
			if ((*cmd)[i][j] == '~')
				if (ft_add_tild(&(*cmd)[i], &j))
					return (1);
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

	n_seq = *b_seq;
	while (n_seq)
	{
		if (n_seq->op)
			if (ft_parcour_op(&n_seq->op))
				return (1);
		n_seq = n_seq->next;
	}
	return (0);
}
