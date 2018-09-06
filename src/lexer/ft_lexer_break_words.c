/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lexer_break_words.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/22 02:52:57 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/17 03:00:34 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lexer.h"

int				ft_lexer_break_operator(char *input, int idx, int i)
{
	char		*s;
	int			ret;

	s = NULL;
	ret = 0;
	if (idx == i)
		return (0);
	if ((s = ft_strsub(input, i, (idx - i))))
	{
		if (ft_isoperator(s) > TOKEN)
		{
			ft_strdel(&s);
			if ((s = ft_strsub(input, i, ((idx - i) + 1))))
				if (ft_isoperator(s) == TOKEN)
					ret = 1;
		}
		else if (input[idx] == ';' || input[idx] == '&' || input[idx] == '|' ||
			input[idx] == '(' || input[idx] == ')' || input[idx] == '<' ||
			input[idx] == '>' || input[idx] == '-')
		{
			ret = 1;
		}
		ft_strdel(&s);
	}
	return (ret);
}

e_prompt		ft_lexer_break_quote(char *input, int *idx)
{
	char		c;
	e_prompt	prompt;

	c = input[*idx];
	prompt = PROMPT;
	if (c == '"' || c == '\'')
	{
		while (input[++(*idx)] != c)
			if (!(input[*idx]))
			{
				if (c == '"')
					prompt = D_QUOTE;
				else if (c == '\'')
					prompt = S_QUOTE;
				break ;
			}
	}
	else if (c == '\\')
	{
		++(*idx);
	}
	return (prompt);
}

int				ft_lexer_break_blank(char *input, int *idx, int *i)
{
	int			ret;

	ret = 0;
	if (ft_isblank(input[*idx]))
	{
		if (*idx == *i)
			(*i)++;
		else
			ret = 1;
	}
	return (ret);
}

void			ft_lexer_break_expansion(char *input, int *idx)
{
	char		c;
	char		d;
	char		e;

	c = input[*idx];
	d = ((*idx + 1) < ft_strlen(input) - 1) ? input[*idx + 1] : '\0';
	e = ((*idx + 2) < ft_strlen(input) - 1) ? input[*idx + 2] : '\0';
	if (c == '$' && d == '{')
		while (input[++(*idx)] != '}' && input[*idx])
			;
	if (c == '$' && d == '(')
		while (input[++(*idx)] != ')' && input[*idx])
			;
	if (c == '`')
		while (input[++(*idx)] != '`' && input[*idx])
			;
}

int				ft_lexer_break_comment(char *input, int *idx)
{
	int			ret;

	ret = 0;
	if (input[*idx] == '#')
	{
		while (input[++(*idx)])
			;
		ret = 1;
	}
	return (ret);
}
