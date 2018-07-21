/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 11:36:54 by gmadec      ###    #+. /#+    ###.fr     */
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

t_cc		*ft_malloc_cc(void)
{
	t_cc		*new;
	t_cc		*now;

	if (!(new = malloc(sizeof(t_cc))))
		return (NULL);
	new->key = TOKEN;
	new->not_operator = TOKEN;
	new->sc = NULL;
	new->open_key = 0;
	new->close_key = 0;
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
	new->not_operator = TOKEN;
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
		if (n_op->token != TOKEN)
		{
			if (!(n_op->next = ft_malloc_op()))
				return (1);
			n_op->next->prev = n_op;
			n_op = n_op->next;
		}
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

	//RESTE A INCLURE LE NOT OPERATOR !
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
		n_op = n_op->next;
	if (n_op->token != TOKEN || n_op->token == NOT)
	{
		printf("0NAME == %s\n", name);
		//PLUS D'ACTUALITE
		n_op->next = ft_malloc_op();
		n_op->next->prev = n_op;
		n_op = n_op->next;
		n_op->sc = ft_malloc_sc();
//		if (token >= LESS && token <= DLESSDASH)
//			n_op->sc->token = token;
//		else
			if (ft_malloc_cmd(&n_op->sc->cmd, name))
				return (1);
	}
	else if (n_op->cc)
		printf("1NAME == %s CC NOT ENABLE\n", name);
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
	}
	return (0);
}

int			ft_entry_reserved(t_seq **b_seq, char *name, e_token token)
{
	t_seq			*n_seq;
	t_op			*n_op;
	t_cc			*n_cc;

	if (!(*b_seq))
		*b_seq = ft_malloc_seq();
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
		n_op = n_op->next;
	if (n_op->token != TOKEN)
	{
		printf("NOUVELLE OP\n");
		n_op->next = ft_malloc_op();
		n_op->next->prev = n_op;
		n_op = n_op->next;
		n_op->cc = ft_malloc_cc();
		n_op->cc->key = token;
	}
	else if (n_op->sc)
	{
		printf("VU COMME UN ARGUMENT DE LA SIMPLE COMMANDE\n");
		token = TOKEN;
		if (ft_manage_word(&(*b_seq), name, token))
			return (1);
	}
	else
	{
		printf("CREATION/CONTINUITE DE LA COMPOSED COMMANDE\n");
		if (!n_op->cc)
			n_op->cc = ft_malloc_cc();
		n_cc = n_op->cc;
		while (n_cc->next_out)
			n_cc = n_cc->next_out;
		while (n_cc->next_in && !n_cc->close_key)
			n_cc = n_cc->next_in;
		if (n_cc->key == TOKEN && !n_cc->sc)
		{
			printf("NOUVELLE PREMIERE CC\n");
			n_cc->key = token;
		}
		else if (n_cc->close_key)
		{
			printf("NOUVELLE CC->OUT\n");
		}
		else if (n_cc->open_key)
		{
			printf("NOUVELLE CC->IN\n");
		}
		else if (n_cc->key != TOKEN && n_cc->sc)
		{
			printf("ARGUMENT DU TOKEN DANS SC, TOKEN = SC JE PENSE\n");
		}
		else
			printf("\n");
	}
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
	else if (token >= AND_IF && token <= DLESSDASH && token != NOT)
	{
		printf("CONTROL OPERATOR\n");
		if (ft_manage_op(&(*b_seq), token))
			return (1);
	}
	else if (token >= IF && token <= CASE)
	{
		printf("ENTRY RESERVED\n");
		if (ft_entry_reserved(&(*b_seq), name, token))
			return (1);
	}
	else if (token == THEN || token == IN || token == DO)
	{
		printf("COMPLETMENT ENTRY RESERVED\n");
	}
	else if (token >= ESAC && token <= DONE)
	{
		printf("OPEN_KEY RESERVED\n");
	}
	else if (token == ESAC && token == DONE)
	{
		printf("CLOSE_KEY RESERVED\n");
	}
	else if (token == NOT)
	{
		printf("NOT_OPERATOR\n");
	}
	else
	{
		printf("TOKEN\n");
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
