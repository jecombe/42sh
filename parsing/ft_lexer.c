/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lexer.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 03:29:15 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/28 02:55:37 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parsing.h"

int				ft_isoperator(char *input, char c)
{
	static char	*operator[11] = {"", "&&", "||", ";;", "<<", ">>", "<&", ">&",
		"<>", "<<-", ">|"};
	static char	part[8] = {'\0', '&', '|', ';', '<', '>', '&', '-'};
	int			i;

	i = 0;
	if (input == NULL)
	{
		while (++i < 8)
			if (part[i] == c)
				return (1);
	}
	else
	{
		while (++i < 11)
			if (ft_strcmp(operator[i], input) == 0)
				return (i);
	}
	return (0);
}

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

enum e_token			ft_lexer_token(char *name)
{
	enum e_token		tkn;
	static char	*token[33] = {"\n", "&&", "||", ";;", "<<", ">>", "<&", ">&",
		"<>", "<<-", ">|", "if", "then", "else", "elif", "fi", "do", "done",
		"case", "esac", "while", "until", "for", "{", "}", "!", "in", "|", ";",
		"&", "<", ">"};
	int			i;

	tkn = WORD;
	i = -1;
	while (++i < 32)
		if (ft_strcmp(token[i], name) == 0)
			tkn = i;
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
		lex.token[v] = ft_lexer_token(lex.name[v]);
	printf("OK\n");
	return (lex);
}
