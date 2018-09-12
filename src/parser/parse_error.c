/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension_error.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/09 07:14:01 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 04:40:51 by dzonda      ###    #+. /#+    ###.fr     */
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

static int		error_n_op(t_op **b_op)
{
	t_op		*n_op;

	n_op = *b_op;
	while (n_op)
	{
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

	n_seq = *b_seq;
	while (n_seq)
	{
		if (n_seq->op)
		{
			if (error_n_op(&n_seq->op))
			{
				ft_free_b_seq(&(*b_seq));
				return (1);
			}
		}
		if (n_seq->token != TOKEN && !n_seq->op)
		{
			ft_putendl("bash: syntax error near unexpected token `newline'");
			ft_free_b_seq(b_seq);
			return (1);
		}
		n_seq = n_seq->next;
	}
	return (0);
}
