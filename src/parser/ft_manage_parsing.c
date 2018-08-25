/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_manage_parsing.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/30 06:46:25 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/25 10:59:05 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/parsing.h"

int			ft_manage_seq(t_seq **b_seq, t_token token)
{
	t_seq		*n_seq;

	if (*b_seq)
	{
		n_seq = *b_seq;
		while (n_seq->next)
			n_seq = n_seq->next;
	}
	else
		return (2);
	if (n_seq->token != TOKEN)
		return (ft_parse_exit(token));
	n_seq->token = token;
	return (0);
}

int			ft_manage_logical_and_pipe(t_seq **b_seq, t_token token)
{
	t_op			*n_op;
	t_seq			*n_seq;

	if (ft_attrib_last_op(&(*b_seq), &n_op))
		return (1);
	if (n_op->token != TOKEN || (!n_op->cmd && !n_op->redirect))
		return (ft_parse_exit(token));
	n_op->token = token;
	return (0);
}

int			ft_manage_redirection(t_seq **b_seq, t_token token, char *name)
{
	t_op			*n_op;
	t_seq			*n_seq;
	t_redirect		*n_redirect;

	if (ft_attrib_last_op(&(*b_seq), &n_op))
		return (1);
	if (n_op->token != TOKEN)
		if (ft_attrib_next_op(&n_op))
			return (1);
	if (ft_attrib_last_redirect(&n_op, &n_redirect))
		return (1);
	while (n_redirect->next)
		n_redirect = n_redirect->next;
	if (n_redirect->redirect != TOKEN && !n_redirect->file)
		return (ft_parse_exit(token));
	else if (n_redirect->file)
		if (ft_attrib_next_redirect(&n_redirect))
			return (1);
	n_redirect->redirect = token;
	return (0);
}

int			ft_manage_word(t_seq **b_seq, char *name)
{
	t_op			*n_op;
	t_redirect		*n_redirect;

	if (ft_attrib_last_op(&(*b_seq), &n_op))
		return (1);
	if (n_op->token != TOKEN || !n_op->redirect)
	{
		if (n_op->token != TOKEN)
			if (ft_attrib_next_op(&n_op))
				return (1);
		ft_malloc_cmd(&n_op->cmd, name);
	}
	else if (n_op->redirect)
	{
		if (ft_attrib_last_redirect(&n_op, &n_redirect))
			return (1);
		if (n_redirect->file)
			ft_malloc_cmd(&n_op->cmd, name);
		else
			n_redirect->file = ft_strdup(name);
	}
	return (0);
}

int			ft_manage_io_number(t_seq **b_seq, char *name)
{
	t_op			*n_op;
	t_seq			*n_seq;
	t_redirect		*n_redirect;

	if (ft_attrib_last_op(&(*b_seq), &n_op))
		return (1);
	while (n_op->next)
		n_op = n_op->next;
	if (!n_op->redirect)
		n_op->redirect = ft_malloc_redirect();
	n_redirect = n_op->redirect;
	while (n_redirect->next)
		n_redirect = n_redirect->next;
	if (n_redirect->redirect != TOKEN)
	{
		n_redirect->next = ft_malloc_redirect();
		n_redirect->next->prev = n_redirect;
		n_redirect = n_redirect->next;
	}
	n_redirect->fd = ft_atoi(name);
	return (0);
}
