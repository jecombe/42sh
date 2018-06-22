/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 09:40:07 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/22 14:25:15 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/22 09:37:56 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./parsing.h"

int			ft_malloc_seq(t_seq **b_seq, t_seq **n_seq, char *name)
{
	t_seq	*a_seq;
	static int	i = 0;

		a_seq = malloc(sizeof(t_seq));
		if (!(*b_seq))
		{
			printf("PREMIERE FOIS == %d\n", i);
			*b_seq = a_seq;
			a_seq->prev = NULL;
		}
		else
		{
			printf("FOIS D'APRES == %d\n", i);
			(*n_seq)->next = a_seq;
			a_seq->prev = *n_seq;
		}
		a_seq->next = NULL;
		*n_seq = a_seq;
		(*n_seq)->cmd = malloc(sizeof(t_cmd));
		(*n_seq)->cmd->next = NULL;
		(*n_seq)->cmd->prev = NULL;
		(*n_seq)->cmd->arg = malloc(sizeof(t_arg));
		(*n_seq)->cmd->arg->name = NULL;
		(*n_seq)->cmd->arg->token = NUL;
		(*n_seq)->cmd->arg->prev = NULL;
		(*n_seq)->cmd->arg->next = NULL;
		i++;
		return (0);
	return (1);
}

int			ft_malloc_cmd(t_cmd **b_cmd, char *name, e_token token)
{
	t_cmd	*a_cmd;
	t_cmd	*n_cmd;

	n_cmd = *b_cmd;
	if (n_cmd->arg->name)
	{
		while (n_cmd->next)
			n_cmd = n_cmd->next;
		a_cmd = malloc(sizeof(t_cmd));
		a_cmd->prev = n_cmd;
		n_cmd->next = a_cmd;
		a_cmd->next = NULL;
		n_cmd = a_cmd;
	}
	n_cmd->arg = malloc(sizeof(t_arg));
	n_cmd->arg->name = ft_strdup(name);
	n_cmd->arg->token = token;
	return (0);
}

int			ft_parse(t_seq **b_seq, t_seq **n_seq, e_token token, char *name)
{
	static int	new_cmd = 0;

	if (new_cmd == 0)
		ft_malloc_seq(&(*b_seq), &(*n_seq), name);
	if (token == SEMI || token == OR_IF || token == AND_IF)
	{
		if (new_cmd == 1)
			ft_malloc_seq(&(*b_seq), &(*n_seq), name);
		(*n_seq)->cmd->arg->name = ft_strdup(name);
		(*n_seq)->cmd->arg->token = token;
		new_cmd = 0;
		return (0);
	}
	else if (token == DLESS || token == DGREAT || token == LESSAND || token == GREATAND || token == SLESS || token == SGREAT || token == DLESSDASH || token == CLOBBER)
	{
		printf("ENTRER\n");
//		if (new_cmd == 1)
		ft_malloc_cmd(&(*n_seq)->cmd, name, token);
	}
	else if (token == IF || token == THEN || token == ELSE)
	{
	}
	new_cmd = 1;
	return (0);
}

void		ft_parsing(t_lex lex)
{
	int		i;
	t_seq	*b_seq;
	t_seq	*n_seq;

	b_seq = NULL;
	n_seq = NULL;
	i = -1;
	printf("--------LEXING----------\n");
	while (lex.name[++i])
	{
		printf("NAME == %s\n", lex.name[i]);
		printf("TOKEN == %u\n", lex.token[i]);
	}
	printf("--------PARSING----------\n");
	i = -1;
	while (lex.name[++i])
	{
		printf("ok\n");
		if ((ft_parse(&b_seq, &n_seq, lex.token[i], lex.name[i])) == -1)
		{
			printf("KO\n");
			break;
		}
	}
	printf("--------------BOUCLE B_SEQ-------------\n");
	while (b_seq)
	{
		i = 0;
		while (b_seq->cmd)
		{
			printf("B_SEQ->NAME == %s\n", b_seq->cmd->arg->name);
			printf("B_SEQ->TOKEN == %u\n", b_seq->cmd->arg->token);
			printf("I == %d\n", i);
			b_seq->cmd = b_seq->cmd->next;
			i++;
		}
		b_seq = b_seq->next;
	}
}
