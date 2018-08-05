/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 05:00:48 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/05 04:42:22 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"

void		ft_braquet_quote(char *str, int *j)
{
	while (str[*j] == '\'')
		*j = *j + 1;
}

int			ft_add_tild(char **str, int *index)
{
	char		*var;
	char		*tmp;
	int			i;
	int			j;

	j = 1;
	i = -1;
	if ((var = ft_getenv("HOME")) && (!(*str)[*index + 1] || (*str)[*index + 1] == '/'))
	{
		tmp = malloc(sizeof(char*) * (ft_strlen(*str) + ft_strlen(var)));
		while (var[++i])
			tmp[i] = var[i];
		while ((*str)[j])
			tmp[i++] = (*str)[j++];
		tmp[i] = '\0';
		printf("TMP == %s\n", tmp);
//		ft_strdel(&(*str));
		*index = i;
		*str = ft_strdup(tmp);
	}
	return (0);
}

int			ft_bquote(char ***cmd, int *i)
{
	return (0);
}

int			ft_parcour_tab(char ***cmd)
{
	int			i;
	int			j;
	int			k;

	i = -1;
	if (*cmd)
		while ((*cmd)[++i])
		{
			j = 0;
			while ((*cmd)[i][j])
			{
				if ((*cmd)[i][j] == '\\')
					j += 2;
				else if ((*cmd)[i][j] == '\'')
					ft_braquet_quote((*cmd)[i] + j, &j);
				else if ((*cmd)[i][j] == '~' && j == 0)
				{
					if (ft_add_tild(&(*cmd)[i], &j))
						return (1);
				}
				else if ((*cmd)[i][j] == '`')
				{
					ft_bquote(&(*cmd), &j);
				}
				else
					j++;
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
