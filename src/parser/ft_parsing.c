/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 00:40:27 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			ft_parse_exit(t_token token)
{
	char		*name;

	name = NULL;
	ft_convert_token(&name, token);
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("'", 2);
	if (name)
		ft_strdel(&name);
	return (2);
}

int			ft_attribute_token(t_seq **b_seq, char *name, t_token token)
{
	if (token == SEMI || token == AND)
		return(ft_manage_seq(&(*b_seq), token));
	else if (token >= AND_IF && token <= PIPE_AND)
		return (ft_manage_logical_and_pipe(&(*b_seq), token));
	else if (token >= LESS && token <= DLESSDASH)
		return (ft_manage_redirection(&(*b_seq), token));
	else if (token == IO_NUMBER)
		return (ft_manage_io_number(&*(b_seq), name));
	else
		return (ft_manage_word(&(*b_seq), name));
}

t_seq		*ft_parsing(t_lex lex)
{
	int				i;
	t_seq			*b_seq;
	int				error;

	error = 0;
	i = 0;
	b_seq = NULL;
	if ((i = ft_search_assignement_word(i, lex.name)) == -1)
	{
		while (lex.name[++i])
			ft_add_assign(&lex.name[i]);
		i = 0;
	}
	while (lex.name[i])
	{
		if ((error = ft_attribute_token(&b_seq, lex.name[i], lex.token[i])))
		{
			if (error == 1)
				ft_putendl("MALLOC ERROR");
			return (NULL);
		}
		i++;
	}
	parse_error(&b_seq);
	return (b_seq);
}
