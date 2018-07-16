/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lexer.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 03:29:15 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/15 05:44:25 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./lexer.h"

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

e_token			ft_lexer_token(char *name[MAX_TAB_SIZE], int v, int *cmd)
{
	e_token		tkn;
	int			i;

	tkn = TOKEN;
	i = -1;
	if ((tkn = ft_isoperator(name[v])) == TOKEN)
	{
		while (ft_isdigit(name[v][++i]))
			;
		if (i == (ft_strlen(name[v]) - 1))
			if (name[v][i] == '>' || name[v][i] == '<')
				tkn = IO_NUMBER;
	}
	if (tkn == TOKEN)
		tkn = ft_lexer_token_rules(name, v, cmd);
	return (tkn);
}

t_lex			ft_lexer(char *input)
{
	t_lex		lex;
	int			idx;
	int			v;
	int			cmd;

	idx = 0;
	v = -1;
	cmd = 0;
	while ((lex.name[++v] = ft_lexer_break_input(input, &idx)))
	{
		//if (ft_isalias(lex.name[v]))
		//		replace(lex.name[v]);
		lex.token[v] = ft_lexer_token(lex.name, v, &cmd);
	}
	return (lex);
}


int main(int ac, char *argv[])
{
	t_lex lex;
	
	lex = ft_lexer(argv[1]);
	int i = -1;
	while (lex.name[++i])
	{
		printf(".%s. .%s.\n", lex.name[i], ft_convert_token_to_string(lex.token[i]));
		ft_strdel(&lex.name[i]);
	}
	return (0);
}
