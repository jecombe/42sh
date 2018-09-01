/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lexer_utils.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/15 02:37:36 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 15:56:01 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/lexer.h"

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

int				ft_isalias(char **name)
{
	int			fd;
	char		*line;
	char		**grid;

	fd = -1;
	line = NULL;
	if ((fd = open("./.101sh_aliases", O_CREAT | O_RDONLY, 0644)) == -1)
		return (EXIT_FAILURE);
	while (get_next_line(fd, &line))
	{
		if (!(grid = ft_strsplit(line, '=')))
			return (EXIT_FAILURE);
		if (ft_strcmp(*name, grid[0]) == 0)
		{
			ft_strdel(name);
			*name = ft_strdup(grid[1]);
		}
		ft_strdel(&grid[0]);
		ft_strdel(&grid[1]);
		ft_strdel(&line);
	}
	if (close(fd) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void			ft_lexer_del(t_lex *lex)
{
	int			i;

	i = -1;
	ft_memset(lex->token, 0, sizeof(t_token) * MAX_LEXER_SIZE);
	while (lex->name[++i])
		ft_strdel(&(lex)->name[i]);
}

/*
**
char			*ft_convert_token_to_string(t_token token)
{
	static char	*tkname[] = {";", "&", ";;", "(", ")", "!", "&&", "||",
		"|", "|&", "<", "<>", ">", ">|", ">>", ">&", "<<", "<&", "<<-",
		"if", "while", "for", "until", "case", "then", "do", "esac", "fi",
		"done", "elif", "else"};
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

**
*/
