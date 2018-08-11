/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/11 07:29:55 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/parsing.h"

int			ft_parse_exit(e_token token)
{
	char		*name;
	t_lex		clear_b_seq;

	ft_convert_token(&name, token);
	ft_putstr("bash: syntax error near unexpected token `");
	ft_putstr(name);
	ft_putendl("'");
	if (name)
		ft_strdel(&name);
	return (1);
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

t_seq		*ft_parsing(t_lex lex)
{
	int				i;
	t_seq			*b_seq;
	t_op			*t_op;

	i = -1;
	b_seq = NULL;
	while (lex.name[++i])
	{
		if (ft_attribute_token(&b_seq, lex.name[i], lex.token[i]))
		{
			ft_putendl("MALLOC ERROR");
			return (NULL);
		}
	}
	parse_error(&b_seq);
	return (b_seq);
}
