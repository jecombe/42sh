/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/26 07:08:53 by gmadec      ###    #+. /#+    ###.fr     */
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
	new->token[0] = TOKEN;
	new->token[1] = TOKEN;
	new->next = NULL;
	new->prev = NULL;
	return (new);
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

	if (ft_attrib_last_nseq(&(*b_seq), &n_seq))
		return (1);
	if (!n_seq->op)
		n_seq->op = ft_malloc_op();
	n_op = n_seq->op;
	while (n_op->next)
		n_op = n_op->next;
	if (n_op->token[0] != TOKEN || !n_op->cmd)
	{
		ft_putstr("bash: syntax error near unexpected token `&&");
		ft_putendl("'");
		return (1);
	}
	n_op->token[0] = token;
	return (0);
}

int			ft_manage_redirection(t_seq **b_seq, e_token token)
{
	t_op			*n_op;
	t_seq			*n_seq;

	if (ft_attrib_last_nseq(&(*b_seq), &n_seq))
		return (1);
	if (!n_seq->op)
		n_seq->op = ft_malloc_op();
	n_op = n_seq->op;
	while (n_op->next)
		n_op = n_op->next;
	if (n_op->token[0] >= AND_IF && n_op->token[0] <= PIPE_AND && n_op->token[1] == TOKEN)
	{
		n_op->token[1] = token;
	}
	else if (n_op->token[0] == TOKEN)
	{
		n_op->token[0] = token;
	}
	else
	{
		ft_putendl("bash: syntax error near unexpected token `&&'");
		return (1);
	}
	return (0);
}

int			ft_manage_word(t_seq **b_seq, char *name)
{
	t_op			*n_op;
	t_seq			*n_seq;

	if (ft_attrib_last_nseq(&(*b_seq), &n_seq))
		return (1);
	if (!n_seq->op)
		n_seq->op = ft_malloc_op();
	n_op = n_seq->op;
		printf("BBBUUUGGG\n");
	while (n_op->next)
		n_op = n_op->next;
	if (n_op->token[0] != TOKEN)
	{
		n_op->next = ft_malloc_op();
		n_op->next->prev = n_op;
		n_op = n_op->next;
	}
	ft_malloc_cmd(&n_op->cmd, name);
	return (0);
}


int			ft_attribute_token(t_seq **b_seq, char *name, e_token token)
{
	if (token == SEMI || token == AND)
	{
		printf("NEW/END SEQUENCE\n");
		if (ft_manage_seq(&(*b_seq), token))
			return (1);
	}
	else if (token >= AND_IF && token <= PIPE_AND)
	{
		printf("LOGICAL OPERATOR\n");
		if (ft_manage_logical_and_pipe(&(*b_seq), token))
			return (1);
	}
	else if (token >= LESS && token <= DLESSDASH)
	{
		printf("REDIRECTION OPERATOR\n");
		if (ft_manage_redirection(&(*b_seq), token))
			return (1);
	}
	else
	{
		printf("TOKEN\n");
		if (ft_manage_word(&(*b_seq), name))
			return (1);
	}
	return (0);
}

t_seq		*ft_manage_parsing(t_lex lex)
{
	int				i;
	t_seq			*b_seq;
	t_op			*t_op;

	b_seq = NULL;
	i = -1;
	while (lex.name[++i])
	{
		printf("------------- I == %d ------------\n", i);
		if (ft_attribute_token(&b_seq, lex.name[i], lex.token[i]))
		{
			printf("AALERTTT GEEENEEERALLLL\n");
			return (NULL);
		}
//			printf("b_seq->op->cc->key == %u\n", b_seq->op->cc->key);
	}
	return (b_seq);
}
