/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lexer.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 03:29:15 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 03:46:36 by dzonda      ###    #+. /#+    ###.fr     */
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
		if ((s = ft_lexer_break_quote(input, idx)))
			return (s);
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
		if (tkn == TOKEN)
			tkn = ft_isreserved(name);
	}
	return (tkn);
}

int				ft_isalias(char **name)
{
	int			fd;
	char		*line;
	char		**tab;

	fd = -1;
	line = NULL;
	if ((fd = open("./.101sh_aliases", O_CREAT | O_RDONLY, 0666)) == -1)
		return (1);
	while (get_next_line(fd, &line))
	{
		if (!(tab = ft_strsplit(line, '=')))
			return (1);
		if (ft_strcmp(*name, tab[0]) == 0)
		{
			ft_strdel(name);
			*name = ft_strdup(tab[1]);
		}
		ft_strdel(&tab[0]);
		ft_strdel(&tab[1]);
		ft_strdel(&line);
	}
	if (close(fd) == -1)
		return (1);
	return (0);
}

char			ft_lexer_check(char *name)
{
	if (ft_strcmp(name, "\"") == 0 || ft_strcmp(name, "\'") == 0 ||
			ft_strcmp(name, "\\") == 0)
		return (name[0]);
	return ('\0');
}

t_lex			ft_lexer(char *input)
{
	t_lex		lex;
	int			idx;
	int			v;

	lex.error = '\0';
	idx = 0;
	v = -1;
	while ((lex.name[++v] = ft_lexer_break_input(input, &idx)))
	{
		if ((lex.error = ft_lexer_check(lex.name[v])))
			break ;
		if (v == 0 || lex.token[v - 1] == SEMI || lex.token[v - 1] == AND ||
				lex.token[v - 1] == PIPE)
			if (ft_isalias(&lex.name[v]))
				break ;
		lex.token[v] = ft_lexer_token(lex.name[v], input[idx]);
	}
	return (lex);
}
