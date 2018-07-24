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

t_op		*ft_malloc_op(void)
{
	t_op	*new;

	if (!(new = malloc(sizeof(t_op))))
		return (NULL);
	new->token[0] = TOKEN;
	new->token[1] = TOKEN;
	new->sc = NULL;
	new->cc = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cc		*ft_malloc_cc(void)
{
	t_cc		*new;

	if (!(new = malloc(sizeof(t_cc))))
		return (NULL);
	new->key = TOKEN;
	new->not_operator = TOKEN;
	new->arg = NULL;
	new->open_key = 0;
	new->close_key = 0;
	new->next_in = NULL;
	new->next_out = NULL;
	new->parent = NULL;
	return (new);
}

t_arg		*ft_malloc_arg(void)
{
	t_arg		*new;

	if (!(new = malloc(sizeof(t_arg))))
		return (NULL);
	new->cmd = NULL;
	new->not_operator = TOKEN;
	new->token[0] = TOKEN;
	new->token[1] = TOKEN;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_sc		*ft_malloc_sc(void)
{
	t_sc		*new;

	if (!(new = malloc(sizeof(t_sc))))
		return (NULL);
	new->cmd = NULL;
	new->not_operator = TOKEN;
	return (new);
}

int			ft_attrib_last_nseq(t_seq **b_seq, t_seq **n_seq)
{
//n_seq est egale au dernier maillon t_seq et si le token n'est pas NULL alors un nouveau maillon sera creer
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

int			ft_parcour_n_op(t_seq **b_seq, t_op **n_op)
{
	if (!(*b_seq))
		return (1);
	else if (!(*b_seq)->op)
		return (2);
	*n_op = (*b_seq)->op;
	while ((*n_op)->next)
		*n_op = (*n_op)->next;
	return (0);
}

int			ft_attrib_last_nop(t_seq **b_seq, t_op **n_op)
{
//n_op est egale au dernier maillon t_op et si le token n'est pas NULL alors un nouveau maillon sera creer
	t_seq			*n_seq;
	int				ret;

	ret = 0;
	if ((ret = ft_parcour_n_op(&(*b_seq), &(*n_op))))
	{
		if (ret == 1)
			if (!((*b_seq) = ft_malloc_seq()))
				return (1);
		n_seq = *b_seq;
		if (!(n_seq->op = ft_malloc_op()))
			return (1);
		*n_op = n_seq->op;
	}
	return (0);
}


int			ft_parcour_cc(t_cc **n_cc)
{
//ATTRIBUT A n_cc le dernier maillon mais ne le creer pas si il existe pas
	if ((*n_cc)->next_out)
	{
		if (ft_parcour_cc(&(*n_cc)->next_out))
			return (1);
	}
	else if ((*n_cc)->next_in)
	{
		if (ft_parcour_cc(&(*n_cc)->next_in))
			return (1);
	}
	return (0);
}

void		ft_attrib_last_arg(t_arg **n_arg)
{
	while ((*n_arg)->next)
		*n_arg = (*n_arg)->next;
}

int			ft_manage_seq(t_seq **b_seq, e_token token)
{
//Attribut le token de fin de sequence au dernier maillon dont le token  est egale a NULL
	t_seq			*n_seq;
	t_op			*n_op;
	t_cc			*n_cc;
	t_arg			*n_arg;

	if (ft_attrib_last_nseq(&(*b_seq), &n_seq))
		return (1);
	if (n_seq->token != TOKEN || !n_seq->op)
	{
		printf("bash: syntax error near unexpected token `;'\n");
		return (1);
	}
	if (ft_attrib_last_nop(&(*b_seq), &n_op))
		return (1);
	if (n_op->token[0] != TOKEN)
	{
		printf("bash: syntax error near unexpected token `;'\n");
		return (1);
	}
	else if (n_op->sc)
	{
		n_seq->token = token;
	}
	else if (n_op->cc)
	{
		n_cc = n_op->cc;
		if (ft_parcour_cc(&n_cc))
			return (1);
		if (!n_cc->arg)
		{
			printf("bash: syntax error near unexpected token `;'\n");
			return (1);
		}
		if (!n_cc->close_key)
		{
			ft_attrib_last_arg(&n_arg);
			if (!n_arg->cmd || n_arg->token[0] != TOKEN)
			{
				printf("bash: syntax error near unexpected token `;'\n");
				return (1);
			}
			else
				n_arg->token[0] = token;
		}
		else
			n_seq->token = token;
	}
	else
	{
		printf("PROBLEME IMPROBABLE DANS FT_MANAGE_SEQ\n");
		exit (1);
	}
	return (0);
}

int			ft_manage_logical_and_pipe(t_seq **b_seq, e_token token)
{
//Attribut le token de logical/pipe au dernier maillon
	t_op			*n_op;
	t_cc			*n_cc;
	t_arg			*n_arg;

	if (ft_attrib_last_nop(&(*b_seq), &n_op))
		return (1);
	if (n_op->token[0] == TOKEN && n_op->sc)
	{
		n_op->token[0] = token;
	}
	else if (n_op->token[0] == TOKEN && n_op->cc)
	{
		n_cc = n_op->cc;
		ft_parcour_cc(&n_cc);
		if (n_cc->close_key > 0)
		{
			n_op->token[0] = token;
		}
		else if (n_cc->arg)
		{
			n_arg = n_cc->arg;
			ft_attrib_last_arg(&n_arg);
			if (n_arg->cmd && n_arg->token[0] == TOKEN)
			{
				n_arg->token[0] = token;
			}
			else
			{
				printf("bash: syntax error near unexpected token `&'\n");
				return (1);
			}
		}
		else
		{
			printf("bash: syntax error near unexpected token `&'\n");
			return (1);
		}
	}
	else
	{
		printf("bash: syntax error near unexpected token `&'\n");
		return (1);
	}
	return (0);
}

int			ft_manage_redirection(t_seq **b_seq, e_token token)
{
	return (0);
}

int			ft_attrib_last_arg_in_cc(t_cc **n_cc)
{
//ATTRIBUT A n_cc le dernier maillon pour une simple commande, en creer un si la commande est open et retourne une erreur de syntaxe si close_key est actif
	if ((*n_cc)->next_out)
	{
		if (ft_attrib_last_arg_in_cc(&(*n_cc)->next_out))
			return (1);
	}
	else if ((*n_cc)->next_in)
	{
		if (ft_attrib_last_arg_in_cc(&(*n_cc)->next_in))
			return (1);
	}
	else if ((*n_cc)->close_key)
	{
		printf("101SH: syntax error near unexpected token `SC IN CC'\n");
		return (1);
	}
	else if (!(*n_cc)->arg)
	{
		if (!((*n_cc)->arg = ft_malloc_arg()))
		{
			return (1);
		}
	}
	else if ((*n_cc)->arg->token[0] != TOKEN)
	{
	// A definir selon Jecombe
		printf("Jecombe apparait STP\n");
	}
	return (0);
}

int			ft_manage_word(t_seq **b_seq, char *name)
{
	t_op			*n_op;
	t_cc			*n_cc;
	t_sc			*n_sc;

	if (ft_attrib_last_nop(&(*b_seq), &n_op))
		return (1);
	if (n_op->cc)
	{
		printf("CC == %s\n", name);
		n_cc = n_op->cc;
		if (ft_attrib_last_arg_in_cc(&n_cc))
			return (1);
		if (ft_malloc_cmd(&n_cc->arg->cmd, name))
			return (1);
		printf("(*b_seq)->op->cc->arg->cmd[0] == %s\n", (*b_seq)->op->cc->arg->cmd[0]);
	}
	else
	{
	printf("SC == %s\n", name);
		if (!n_op->sc)
			if (!(n_op->sc = ft_malloc_sc()))
				return (1);
		if (ft_malloc_cmd(&n_op->sc->cmd, name))
			return (1);
	}
	return (0);
}

int			ft_attrib_last_key_in_cc(t_seq **b_seq, t_cc **n_cc)
{
	t_op			*n_op;

	if (ft_attrib_last_nop(&(*b_seq), &n_op))
		return (1);
	if (!(n_op->cc))
		if (!(n_op->cc = ft_malloc_cc()))
			return (1);
	*n_cc = n_op->cc;
	if ((*n_cc)->next_out)
	{
		if (!(ft_attrib_last_key_in_cc(&(*b_seq), &(*n_cc)->next_out)))
			return (1);
	}
	else if ((*n_cc)->next_in)
	{
		if (!(ft_attrib_last_key_in_cc(&(*b_seq), &(*n_cc)->next_in)))
			return (1);
	}
	return (0);
}

int			ft_create_cc(t_seq **b_seq, char *name, e_token token)
{
	t_seq			*n_seq;
	t_op			*n_op;
	t_cc			*n_cc;

	if (ft_attrib_last_nop(&(*b_seq), &n_op))
		return (1);
	if (n_op->sc)
	{
		printf("VU COMME UN ARGUMENT DE LA SIMPLE COMMANDE\n");
		if (ft_malloc_cmd(&n_op->sc->cmd, name))
			return (1);
	}
	else
	{
		printf("CREATION/CONTINUITE DE LA COMPOSED COMMANDE\n");
		if (ft_attrib_last_key_in_cc(&(*b_seq), &n_cc))
			return (1);
		if (n_cc->key != TOKEN && !n_cc->arg)
		{
			printf("bash: syntax error near unexpected token `;'\n");
			return (1);
		}
		else if (n_cc->open_key && !n_cc->close_key)
		{
			if (!(n_cc->next_in = ft_malloc_cc()))
				return (1);
			n_cc->next_in->parent = n_cc;
			n_cc = n_cc->next_in;
		}
		else if (n_cc->close_key)
		{
			if (n_op->token[0] != TOKEN)
			{
				printf("creer nouvelle OP + CC + TOKEN\n");
				n_op->next = ft_malloc_op();
				n_op->next->prev = n_op;
				n_op = n_op->next;
				n_op->cc = ft_malloc_cc();
				n_cc = n_op->cc;
			}
			else
			{
				printf("bash: syntax error near unexpected token `if'\n");
				return (1);
			}
		}
		if (n_cc->key != TOKEN && n_cc->arg)
		{
			printf("ARGUMENT DU TOKEN DANS SC, TOKEN = SC\n");
			ft_malloc_cmd(&n_cc->arg->cmd, name);
		}
		else
		{
			printf("NEW RESERVED ENTRY\n");
			n_cc->key = token;
		}
	}
	return (0);
}

int			ft_open_cc(t_seq **b_seq, char *name, e_token token)
{
	t_seq			*n_seq;
	t_op			*n_op;
	t_cc			*n_cc;

	if (ft_attrib_last_nop(&(*b_seq), &n_op))
		return (1);
	if (n_op->sc)
	{
		printf("VU COMME UN ARGUMENT DE LA SIMPLE COMMANDE\n");
		if (ft_malloc_cmd(&n_op->sc->cmd, name))
			return (1);
	}
	else
	{
		printf("CREATION/CONTINUITE DE LA COMPOSED COMMANDE\n");
		if (ft_attrib_last_key_in_cc(&(*b_seq), &n_cc))
			return (1);
		if (token == THEN || token == DO)
		{
			
		}
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
	else if (token >= AND_IF && token <= PIPE_AND)
	{
		printf("LOGICAL OPERATOR\n");
		if (ft_manage_logical_and_pipe(&(*b_seq), token))
			return (1);
	}
	else if (token >= LESS && token <= DLESSDASH)
	{
		printf("LOGICAL OPERATOR\n");
		if (ft_manage_redirection(&(*b_seq), token))
			return (1);
	}
	else if (token >= IF && token <= CASE)
	{
		printf("CREATE CC\n");
		if (ft_create_cc(&(*b_seq), name, token))
			return (1);
	}
	else if (token == THEN || token == IN || token == DO)
	{
		printf("OPEN CC\n");
		if (ft_open_cc(&(*b_seq), name, token))
			return (1);
	}
	else if (token >= ESAC && token <= DONE)
	{
		printf("OPEN_KEY RESERVED\n");
	}
	else if (token == ELIF && token == ELSE)
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
		if (ft_manage_word(&(*b_seq), name))
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
