/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 05:00:48 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/14 14:46:37 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"
#include "../../include/init.h"

int			ft_add_tild(char **str, int *index)
{
	char		*var;
	char		*tmp;
	int			i;
	int			j;

	j = 1;
	i = -1;
	if ((var = ft_getenv("HOME", g_env)) && (!(*str)[*index + 1] || (*str)[*index + 1] == '/'))
	{
		tmp = malloc(sizeof(char*) * (ft_strlen(*str) + ft_strlen(var)));
		while (var[++i])
			tmp[i] = var[i];
		while ((*str)[j])
			tmp[i++] = (*str)[j++];
		tmp[i] = '\0';
		*index = i;
		*str = ft_strdup(tmp);
	}
	return (0);
}

int			ft_parcour_tab(char ***cmd)
{
	int			i;
	int			j;
	int			k;
	int			dquote;
	int			begin_bquote;

	begin_bquote = 0;
	dquote = 0;
	i = -1;
	if (*cmd)
		while (*cmd && (*cmd)[++i])
		{
			j = 0;
			while ((*cmd)[i][j])
			{
				if ((*cmd)[i][j] == '\\')
				{
					backslash_manager(&(*cmd), i, &j, dquote);
				}
				else if ((*cmd)[i][j] == '\'' && !dquote && !begin_bquote)
				{
					ft_manage_quote(&(*cmd), i, &j, ft_replace_quote);
				}
				else if ((*cmd)[i][j] == '"' && !begin_bquote)
				{
					ft_manage_quote(&(*cmd), i, &j, ft_replace_dquote);
					dquote = dquote == 1 ? 0 : 1;
				}
				else if ((*cmd)[i][j] == '~' && j == 0)
				{
					if (ft_add_tild(&(*cmd)[i], &j))
						return (1);
				}
				else if ((*cmd)[i][j] == '`')
				{
					if (begin_bquote == 0)
					{
						begin_bquote = j == 0 ? -1 : j;
						j++;
					}
					else
					{
//						printf("BEGIN == %d, J == %d\n", begin_bquote, j);
						begin_bquote = begin_bquote == -1 ? 0 : begin_bquote;
						bquote_manager(&(*cmd), &j, &i, begin_bquote);
						begin_bquote = 0;
					}
			//		j++;
				}
				else
					j++;
				if (!(*cmd) || !(*cmd)[i])//RESOUT LE SEGSEG
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
	while ((*b_seq)->op->cmd[i])
	{
		i++;
	}
	extension_error(b_seq);
	return (0);
}
