/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension_error.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/09 07:14:01 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/25 17:35:22 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		error_n_redirect(t_redirect **b_redirect)
{
	t_redirect	*n_redirect;

	n_redirect = *b_redirect;
	while (n_redirect)
	{
		if (!n_redirect->file)
			return (ft_parse_exit(NEWLINE));
		n_redirect = n_redirect->next;
	}
	return (0);
}

static int		parse_sub(char **cmd)
{
	int		i;
	int		j;
	int		sub;

	i = -1;
	while (cmd[++i])
	{
		j = -1;
		sub = 0;
		while (cmd[i][++j])
		{
			if (cmd[i][j] == '(' && (j == 0 || cmd[i][j - 1] != '\\'))
				sub++;
			if (cmd[i][j] == ')' && (j == 0 || cmd[i][j - 1] != '\\'))
			{
				if (sub == 0)
					return (1);
				sub--;
			}
		}
		if (sub)
			return (1);
	}
	return (0);
}

static int		error_n_op(t_op **b_op)
{
	t_op		*n_op;

	n_op = *b_op;
	while (n_op)
	{
		if (n_op->cmd)
			if (parse_sub(n_op->cmd))
				return (2);
		if (n_op->redirect)
			if (error_n_redirect(&n_op->redirect))
				return (1);
		n_op = n_op->next;
	}
	return (0);
}

int				parse_error(t_seq **b_seq)
{
	t_seq		*n_seq;
	int			sub;

	n_seq = *b_seq;
	while (n_seq)
	{
		if (n_seq->op)
		{
			if ((sub = error_n_op(&n_seq->op)))
			{
				sub == 2 ?
		ft_putendl_fd("101sh: syntax error near unexpected token `)'", 2) : 0;
				ft_free_b_seq(&(*b_seq));
				return (1);
			}
		}
		if (n_seq->token != TOKEN && !n_seq->op)
		{
			ft_putendl("101sh: syntax error near unexpected token `newline'");
			ft_free_b_seq(b_seq);
			return (1);
		}
		n_seq = n_seq->next;
	}
	return (0);
}
