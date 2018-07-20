/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lexer.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 03:29:15 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 06:59:48 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lexer.h"

char			*ft_lexer_break_input(char *input, int *idx)
{
	int			i;
	char		*s;

	i = *idx;
	while (input[*idx])
	{
		if (ft_lexer_break_operator(input, *idx, i))
			break ;
		ft_lexer_break_quote(input, idx);
		ft_lexer_break_expansion(input, idx);
		if ((ft_lexer_break_blank(input, idx, &i)))
			break ;
		if (ft_lexer_break_comment(input, idx))
			break ;
		(*idx < ft_strlen(input)) ? (*idx)++ : 0;
	}
	if (input[*idx] == '\0' && (*idx == i))
		return (NULL);
	s = ft_strsub(input, i, (*idx - i));
	return (s);
}

e_token			ft_lexer_token(char *name, char c)
{
	e_token		tkn;
	int			i;

	tkn = TOKEN;
	i = -1;
	if ((tkn = ft_isoperator(name)) == TOKEN)
	{
		while (name[++i])
			if (!ft_isdigit(name[i]))
				break ;
		if ((i == ft_strlen(name)) && (c == '>' || c == '<'))
			tkn = IO_NUMBER;
	}
	return (tkn);
}

t_lex			ft_lexer(char *input)
{
	t_lex		lex;
	int			idx;
	int			v;

	idx = 0;
	v = -1;
	while ((lex.name[++v] = ft_lexer_break_input(input, &idx)))
	{
		//if (ft_isalias(lex.name[v]))
		//		replace(lex.name[v]);
		lex.token[v] = ft_lexer_token(lex.name[v], input[idx]);
	}
	ft_lexer_token_rules(&lex);
	return (lex);
}

