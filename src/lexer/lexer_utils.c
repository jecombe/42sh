/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 01:41:01 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 08:19:51 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int				ft_isoperator(char *input)
{
	static char	*operator[] = {";", "&", ";;", "(", ")", "!", "&&", "||",
		"|", "|&", "<", "<>", ">", ">|", ">>", ">&", "<<", "<&", "<<-"};
	int			value;
	int			i;

	value = 265;
	i = -1;
	while (++value < 285)
		if (ft_strcmp(operator[++i], input) == 0)
			return (value);
	return (260);
}

int				ft_isreserved(char *input)
{
	static char	*reserved[] = {"if", "while", "for", "until", "case", "then",
		"do", "esac", "fi", "done", "elif", "else"};
	int			value;
	int			i;

	value = 284;
	i = -1;
	while (++value < 297)
		if (ft_strcmp(reserved[++i], input) == 0)
			return (value);
	return (WORD);
}

void			ft_lexer_del(t_lex *lex)
{
	int		i;

	i = -1;
	ft_memset(lex->token, 0, sizeof(t_token) * MAX_LEXER_SIZE);
	while (lex->name[++i])
		ft_strdel(&(lex)->name[i]);
}
