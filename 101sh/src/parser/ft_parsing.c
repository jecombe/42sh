/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 08:56:55 by gmadec      ###    #+. /#+    ###.fr     */
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
		i = 0;
		while (ret[i])
		{
			printf("RET[i] == %s\n", ret[i]);
			i++;
		}
		i = 0;
		while (tab[i])
		{
			printf("TAB[i] == %s\n", tab[i]);
			i++;
		}
	}
//	printf("dfgdfgdfgdf\n");
	return (ret);
}

int			ft_malloc_cmd(char ***cmd, char *new_arg)
{
	int		i;
	char	**tab;
	int		len;

	i = 0;
	if (!*cmd)
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
			tab[i] = ft_strdup((*cmd)[i]);
		printf("IIIIIIIIIIIIICCCCCCCCCCCCCIIIIIIIIIII\n");
			i++;
		}
	}
	tab[i] = ft_strdup(new_arg);
	tab[++i] = NULL;
	i = 0;
	while (tab[i])
	{
		printf("0CMD[i] == %s\n", tab[i]);
		i++;
	}
	printf("PPPPPPPPP\n");
	*cmd = ft_tabdup(tab);
	i = 0;
	while ((*cmd)[i])
	{
		printf("1CMD[i] == %s\n", (*cmd)[i]);
		i++;
	}
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

t_cc		*ft_malloc_cc(void)
{
	t_cc		*new;
	t_cc		*now;

	if (!(new = malloc(sizeof(t_cc))))
		return (NULL);
	new->key = TOKEN;
	new->sc = NULL;
	new->open = 0;
	new->close = 0;
	new->next_in = NULL;
	new->next_out = NULL;
	new->prev_in = NULL;
	new->prev_out = NULL;
	return (new);
}

t_op		*ft_malloc_op(void)
{
	t_op	*new;

	if (!(new = malloc(sizeof(t_op))))
		return (NULL);
	new->token = TOKEN;
	new->sc = NULL;
	new->cc = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_sc		*ft_malloc_sc(void)
{
	t_sc		*new;

	if (!(new = malloc(sizeof(t_cc))))
		return (NULL);
	new->cmd = NULL;
	new->token = TOKEN;
	return (new);
}

int			ft_manage_seq(t_seq **b_seq, e_token token)
{
	t_seq			*n_seq;

	if (*b_seq)
	{
		n_seq = *b_seq;
		while (n_seq->next)
			n_seq = n_seq->next;
		if (n_seq->token != TOKEN)
		{
			if (!(n_seq->next = ft_malloc_seq()))
				return (1);
			n_seq->next->prev = n_seq;
			n_seq = n_seq->next;
		}
	}
	else
	{
		if (!(*b_seq = ft_malloc_seq()))
			return (1);
		n_seq = *b_seq;
	}
	n_seq->token = token;
	return (0);
}

int			ft_manage_op(t_seq **b_seq, e_token token)
{
	t_seq			*n_seq;
	t_op			*n_op;

	if (!(*b_seq))
		if (!(*b_seq = ft_malloc_seq()))
			return (1);
	n_seq = *b_seq;
	while (n_seq->next)
		n_seq = n_seq->next;
	if ((!(n_seq->op) && n_seq->token == TOKEN) || n_seq->token != TOKEN)
	{
		if (n_seq->token != TOKEN)
		{
			if (!(n_seq->next = ft_malloc_seq()))
				return (1);
			n_seq->next->prev = n_seq;
			n_seq = n_seq->next;
		}
		if (!(n_seq->op = ft_malloc_op()))
			return (1);
		n_op = n_seq->op;
	}
	else if (n_seq->op)
	{
		n_op = n_seq->op;
		while (n_op->next)
			n_op = n_op->next;
		if (!(n_op->next = ft_malloc_op()))
			return (1);
		n_op->next->prev = n_op;
		n_op = n_op->next;
	}
	else
		printf("BBBBBBBBBBBUUUUUUUUUUUUUUUUUGGGGGGGGGGGGGGG\n");
	n_op->token = token;
	return (0);
}

int			ft_manage_word(t_seq **b_seq, char *name, e_token token)
{
	t_seq			*n_seq;
	t_op			*n_op;
	t_sc			*n_sc;

	if (!(*b_seq))
	{
//		if (ft_manage_op(&(*b_seq), TOKEN))
		*b_seq = ft_malloc_seq();
//			return (1);
	}
	n_seq = *b_seq;
	while (n_seq->next)
		n_seq = n_seq->next;
	if (!n_seq->op || n_seq->token != TOKEN)
	{
		if (n_seq->token != TOKEN)
		{
			n_seq->next = ft_malloc_seq();
			n_seq->next->prev = n_seq;
			n_seq = n_seq->next;
		}
		n_seq->op = ft_malloc_op();
	}
	n_op = n_seq->op;
	while (n_op->next)
	{
		printf("N_OP->NEXT\n");
		n_op = n_op->next;
	}
	if (n_op->token != TOKEN)
	{
	printf("0NAME == %s\n", name);
		//PLUS D'ACTUALITE
		n_op->next = ft_malloc_op();
		n_op->next->prev = n_op;
		n_op = n_op->next;
		n_op->sc = ft_malloc_sc();
		if (token >= 276 && token <= 284)
			n_op->sc->token = token;
		else
			if (ft_malloc_cmd(&n_op->sc->cmd, name))
				return (1);
	}
	else if (n_op->cc)
	printf("1NAME == %s\n", name);
	else
	{
	printf("2NAME == %s\n", name);
		if (!n_op->sc)
			n_op->sc = ft_malloc_sc();
/*		if (n_sc->cmd || n_sc->token != TOKEN)
		{
			n_sc->next = ft_malloc_sc();
			n_sc->next->prev = n_sc;
			n_sc = n_sc->next;
		}*/
		if (ft_malloc_cmd(&n_op->sc->cmd, name))
			return (1);
	printf("2NAME == %s\n", name);
	}
	return (0);
}

int			ft_attribute_token(t_seq **b_seq, char *name, e_token token)
{
	if (token == SEMI || token == AND)
	{
		if (ft_manage_seq(&(*b_seq), token))
			return (1);
	}
	else if (token >= 266 && token <= 284)
	{
		if (ft_manage_op(&(*b_seq), token))
			return (1);
	}
	else if (token >= 285 && token <= 300)
	{
		printf("RESERVED WORD IS NOT ENABLE\n");
	}
	else
	{
		if (ft_manage_word(&(*b_seq), name, token))
			return (1);
	}
	return (0);
}

t_seq		*ft_manage_parsing(t_lex lex)
{
	int				i;
	t_seq			*b_seq;

	b_seq = NULL;
	i = -1;
	while (lex.name[++i])
	{
		printf("I == %d\n", i);
		if (ft_attribute_token(&b_seq, lex.name[i], lex.token[i]))
			return (NULL);
	}
	return (b_seq);
}
