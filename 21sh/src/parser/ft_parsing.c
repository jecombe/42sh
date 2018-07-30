/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/30 04:51:53 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/parsing.h"

int			ft_tablen(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char		**ft_tabdup(char **tab)
{
	char		**ret;
	int			i;

	i = 0;
	ret = NULL;
	if (tab)
	{
		if (!(ret = malloc(sizeof(char**) * ft_tablen(tab) + 1)))
			return (NULL);
		while (tab[i])
		{
			ret[i] = tab[i];
			i++;
		}
		ret[i] = NULL;
	}
	return (ret);
}

int			ft_malloc_cmd(char ***cmd, char *new_arg)
{
	int		i;
	char	**tab;

	i = 0;
	if (!(*cmd))
	{
		if (!(tab = malloc(sizeof(char**) * 2)))
			return (1);
	}
	else
	{
		if (!(tab = malloc(sizeof(char**) * ft_tablen(*cmd) + 2)))
			return (1);
		while ((*cmd)[i])
		{
		printf("%s\n", ft_strdup((*cmd)[i]));
			tab[i] = ft_strdup((*cmd)[i]);
			i++;
		}
	}
	tab[i] = ft_strdup(new_arg);
	tab[i + 1] = NULL;
	*cmd = ft_tabdup(tab);
	return (0);
}

t_seq		*ft_malloc_seq(void)
{
	t_seq	*new;

	if (!(new = malloc(sizeof(t_seq))))
		return (NULL);
	new->token = TOKEN;
	new->op = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_op		*ft_malloc_op(void)
{
	t_op	*new;

	if (!(new = malloc(sizeof(t_op))))
		return (NULL);
	new->cmd = NULL;
	new->token = TOKEN;
	new->redirect = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_redirect	*ft_malloc_redirect()
{
	t_redirect	*new;

	if (!(new = malloc(sizeof(t_redirect))))
		return (NULL);
	new->fd = NULL;
	new->redirect = TOKEN;
	new->file = NULL;
	new->next = NULL;
	new->prev = NULL;
	return(new);
}

int			ft_attrib_last_nseq(t_seq **b_seq, t_seq **n_seq)
{
	if (*b_seq)
	{
		*n_seq = *b_seq;
		while ((*n_seq)->next)
			*n_seq = (*n_seq)->next;
		if ((*n_seq)->token != TOKEN)
		{
			if (!((*n_seq)->next = ft_malloc_seq()))
				return (1);
			(*n_seq)->next->prev = *n_seq;
			(*n_seq) = (*n_seq)->next;
		}
	}
	else
	{
		if (!(*b_seq = ft_malloc_seq()))
			return (1);
		*n_seq = *b_seq;
	}
	return (0);
}

int			ft_attrib_last_nop(t_seq **b_seq, t_op **ret_op)
{
	t_seq		*n_seq;
	t_op		*n_op;

	if (ft_attrib_last_nseq(&(*b_seq), &n_seq))
		return (1);
	if (!n_seq->op)
		if (!(n_seq->op = ft_malloc_op()))
			return (1);
	n_op = n_seq->op;
	while (n_op->next)
		n_op = n_op->next;
	*ret_op = n_op;
	return (0);
}

int			ft_attrib_next_nop(t_op **n_op)
{
	(*n_op)->next = ft_malloc_op();
	(*n_op)->next->prev = *n_op;
	*n_op = (*n_op)->next;
	return (0);
}

int			ft_manage_seq(t_seq **b_seq, e_token token)
{
	t_seq		*n_seq;

	if (*b_seq)
	{
		n_seq = *b_seq;
		while (n_seq->next)
			n_seq = n_seq->next;
	}
	else
	{
		*b_seq = ft_malloc_seq();
		n_seq = *b_seq;
	}
	if (n_seq->token != TOKEN)
	{
		ft_putstr("bash: syntax error near unexpected token `");
		ft_putstr(token == SEMI ? ";" : "&");
		ft_putendl("'");
		return (1);
	}
	n_seq->token = token;
	return (0);
}

int			ft_manage_logical_and_pipe(t_seq **b_seq, e_token token)
{
	t_op			*n_op;
	t_seq			*n_seq;

	if (ft_attrib_last_nop(&(*b_seq), &n_op))
		return (1);
	if (n_op->token != TOKEN || !n_op->cmd)
	{
		ft_putstr("bash: syntax error near unexpected token `&&");
		ft_putendl("'");
		return (1);
	}
	n_op->token = token;
	return (0);
}

int			ft_attrib_last_nredirect(t_op **n_op, t_redirect **n_redirect)
{
	if (!(*n_op)->redirect)
		if (!((*n_op)->redirect = ft_malloc_redirect()))
			return (1);
	*n_redirect = (*n_op)->redirect;
	while ((*n_redirect)->next)
		*n_redirect = (*n_redirect)->next;
	return (0);
}

int			ft_attrib_next_nredirect(t_redirect **n_redirect)
{
	if (!((*n_redirect)->next = ft_malloc_redirect()))
		return (1);
	(*n_redirect)->next->prev = *n_redirect;
	*n_redirect = (*n_redirect)->next;
	return (0);
}

int			ft_manage_redirection(t_seq **b_seq, e_token token, char *name)
{
	t_op			*n_op;
	t_seq			*n_seq;
	t_redirect		*n_redirect;

	if (ft_attrib_last_nop(&(*b_seq), &n_op))
		return (1);
	if (n_op->token != TOKEN)
		if (ft_attrib_next_nop(&n_op))
			return (1);
	if (ft_attrib_last_nredirect(&n_op, &n_redirect))
		return (1);
	while (n_redirect->next)
		n_redirect = n_redirect->next;
	if (n_redirect->redirect != TOKEN && !n_redirect->file)
	{
		ft_putendl("bash: syntax error near unexpected token `&&'111");
		return (1);
	}
	else if (n_redirect->file)
		if (ft_attrib_next_nredirect(&n_redirect))
			return (1);
	n_redirect->redirect = token;
	return (0);
}

int			ft_manage_word(t_seq **b_seq, char *name)
{
	t_op			*n_op;
	t_redirect		*n_redirect;

	if (ft_attrib_last_nop(&(*b_seq), &n_op))
		return (1);
	if (n_op->token != TOKEN || !n_op->redirect)
	{
		if (n_op->token != TOKEN)
			if (ft_attrib_next_nop(&n_op))
				return (1);
		ft_malloc_cmd(&n_op->cmd, name);
	}
	else if (n_op->redirect)
	{
		if (ft_attrib_last_nredirect(&n_op, &n_redirect))
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

	if (ft_attrib_last_nop(&(*b_seq), &n_op))
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
	n_redirect->fd = ft_strdup(name);
	return (0);
}

int			ft_attribute_token(t_seq **b_seq, char *name, e_token token)
{
	if (token == SEMI || token == AND)
	{
		if (ft_manage_seq(&(*b_seq), token))
			return (1);
	}
	else if (token >= AND_IF && token <= PIPE_AND)
	{
		if (ft_manage_logical_and_pipe(&(*b_seq), token))
			return (1);
	}
	else if (token >= LESS && token <= DLESSDASH)
	{
		if (ft_manage_redirection(&(*b_seq), token, name))
			return (1);
	}
	else if (token == IO_NUMBER)
	{
		if (ft_manage_io_number(&*(b_seq), name))
			return (1);
	}
	else
		if (ft_manage_word(&(*b_seq), name))
			return (1);
	return (0);
}

t_seq		*ft_manage_parsing(t_lex lex)
{
	int				i;
	static t_seq	*b_seq = NULL;
	t_op			*t_op;

	i = -1;
	while (lex.name[++i])
	{
		if (ft_attribute_token(&b_seq, lex.name[i], lex.token[i]))
		{
			printf("AALERTTT GEEENEEERALLLL\n");
			return (NULL);
		}
	}
	return (b_seq);
}
