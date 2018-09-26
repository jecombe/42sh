/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/13 21:04:37 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		ft_search_assignement_word(int i, char **name)
{
	int j;
	int eq;

	while (name[i])
	{
		j = 0;
		if (ft_isalpha(name[i][0]))
		{
			eq = 0;
			while (name[i][j] && !eq)
			{
				if (name[i][j] == '=' || ft_isalnum(name[i][j]))
					eq = name[i][j++] == '=' ? 1 : 0;
				else
					return (i);
			}
			i += eq == 1 ? 1 : 0;
			if (!(eq == 1))
				return (i);
		}
		else
			return (i);
	}
	return (name[0] ? -1 : 0);
}

static void	add_assign_annex(char **tmp, char *str)
{
	int i;
	int j;
	int eq;

	i = 0;
	j = 0;
	eq = 0;
	while (str[i])
	{
		if (eq == 1)
		{
			(*tmp)[j] = '"';
			eq = 2;
		}
		else
		{
			if (str[i] == '=' && eq == 0)
				eq = 1;
			(*tmp)[j] = str[i];
			i++;
		}
		j++;
	}
	(*tmp)[j++] = '"';
	(*tmp)[j] = '\0';
}

int		ft_add_assign(char **str)
{
	char *tmp;

	if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(*str) + 3))))
		return (1);
	add_assign_annex(&tmp, *str);
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (0);
}
