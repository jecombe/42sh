/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lexer_utils.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/15 02:37:36 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/15 02:55:02 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./lexer.h"

int				ft_isoperator(char *input)
{
	static char	*operator[] = {";", "&", "&&", "||", "!", "|", "|&", ";;",
		"(", ")", "<", "<>", ">", ">|", ">>", ">&", "<<", "<&", "<<-"};
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
	static char	*reserved[] = {"if", "then", "else", "elif", "fi", "do", "done",
		"case", "esac", "while", "until", "for"};
	int			value;
	int			i;

	value = 284;
	i = -1;
	while (++value < 297)
		if (ft_strcmp(reserved[++i], input) == 0)
			return (value);
	return (WORD);
}

char			*ft_convert_token_to_string(e_token token)
{
	static char	*tkname[] = {";", "&", "&&", "||", "!", "|", "|&", ";;",
		"(", ")", "<", "<>", ">", ">|", ">>", ">&", "<<", "<&", "<<-",
		"if", "then", "else", "elif", "fi", "do", "done", "case", "esac",
		"while", "until", "for"};
	int			value;
	int			i;
	char		*s;

	value = 265;
	i = -1;
	while (++value < 297)
	{
		++i;
		if (value == token)
			break ;
	}
	if (value == 297)
	{
		if (token == 261) s = "WORD";
		else if (token == 262) s = "ASSIGNEMENT_WORD";
		else if (token == 263) s = "NAME";
		else if (token == 264) s = "NEWLINE";
		else if (token == 265) s = "IO_NUMBER";
		else s = "TOKEN";
	}
	return (value == 297 ? s : tkname[i]);
}


