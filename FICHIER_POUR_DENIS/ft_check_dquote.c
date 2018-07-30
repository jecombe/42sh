/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_check_dquote.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/05 06:35:34 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/24 20:47:47 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/minishell.h"

static void		ft_print_quote(char quote)
{
	if (quote == '`')
		ft_putstr("bquote> ");
	else if (quote == '"')
		ft_putstr("dquote> ");
	else if (quote == '\'')
		ft_putstr("quote> ");
}

static char		*ft_manage_dquote(char **line, char *quote, char **str)
{
	int			i;
	char		*tmp;

	i = -1;
	while ((*line)[++i])
	{
		if (((*line)[i] == '"' || (*line)[i] == '\'' || (*line)[i] == '`') &&
		(*quote) == 0)
			(*quote) = (*line)[i];
		else if ((*quote) == (*line)[i] && (*quote) != 0)
			(*quote) = 0;
	}
	tmp = ft_strjoin((*str), (*line));
	if (*line)
		ft_strdel(&(*line));
	if (*str)
		ft_strdel(&(*str));
	return (tmp);
}

char			*ft_check_dquote(char *str)
{
	char		*dquote;
	char		quot;
	int			i;
	char		*line;

	line = NULL;
	i = -1;
	quot = 0;
	dquote = NULL;
	if (str)
		while (str[++i])
		{
			if ((str[i] == '"' || str[i] == '\'' || str[i] == '`') && quot == 0)
				quot = str[i];
			else if (quot == str[i] && quot != 0)
				quot = 0;
		}
	while (quot != 0)
	{
		ft_print_quote(quot);
		get_next_line(0, &line);
		str = ft_manage_dquote(&line, &quot, &str);
		ft_strdel(&line);
	}
	return (str);
}
