/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lexer.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/19 00:57:33 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/08 14:50:02 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

static char			*ft_lexer_quote(char *cmd, int *idx)
{
	char			*s;
	int				max;

	s = NULL;
	max = *idx + 1;
	while (cmd[max] && !ft_isquote(cmd[max]))
		max++;
	if (ft_isquote(cmd[max]) && cmd[max])
		max++;
	s = ft_strsub(cmd, *idx, max - *idx);
	*idx = max;
	return (s);
}

static char			*ft_lexer_nquote(char *cmd, int *idx)
{
	char			*s;
	int				max;

	s = NULL;
	max = *idx;
	while (cmd[max] && (!(ft_isspace(cmd[max]))))
	{
		if (ft_isbashop(cmd[max]))
			break ;
		max++;
	}
	s = ft_strsub(cmd, *idx, max - *idx);
	*idx = max;
	return (s);
}

static char			*ft_lexer_bashop(char *cmd, int *idx)
{
	char			*s;

	s = ft_strsub(cmd, *idx, 1);
	(*idx)++;
	return (s);
}

void				ft_lexer(char *cmd, char *array[100])
{
	int j;
	int v;

	j = 0;
	v = 0;
	while (cmd[j] && (v < 100))
	{
		if (ft_isbashop(cmd[j]))
		{
			array[v++] = ft_lexer_bashop(cmd, &j);

		}
		else if (ft_isquote(cmd[j]))
		{
			array[v++] = ft_lexer_quote(cmd, &j);
		}
		else if (!ft_isspace(cmd[j]))
		{
			array[v++] = ft_lexer_nquote(cmd, &j);
		}
		else
			j++;
	}
	array[v] = NULL;
}

void				ft_lexer_del(char *array[100])
{
	int i;

	i = -1;
	while (array[++i] && (i < 100))
		ft_strdel(&array[i]);
}
