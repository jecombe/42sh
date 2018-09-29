/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_break_words.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 01:40:55 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 01:40:58 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

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

void			ft_lexer_break_quote(char *input, int *idx)
{
	char	c;

	c = 0;
	c = input[*idx];
	if (c == '"' || c == '\'')
	{
		while (input[++(*idx)] != c)
			;
	}
	else if (c == '\\')
	{
		++(*idx);
	}
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

	c = input[*idx];
	d = ((*idx + 1) < (int)ft_strlen(input) - 1) ? input[*idx + 1] : '\0';
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
