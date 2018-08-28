/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   manage_assignement_word.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 10:34:46 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/26 15:58:06 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

static int	is_assig(char *cmd)
{
	int		i;
	int		egale;

	egale = 0;
	i = 0;
	while (cmd[i])
	{
		if (ft_isalnum(cmd[i]) || cmd[i] == '=')
		{
			if (cmd[i] == '=')
				egale++;
			i++;
		}
		else
			return (1);
	}
	return (egale ? 0 : 1);
}

int			manage_assignement_word(t_lex lex, int *i)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	while (lex.name[*i])
	{
		if (lex.token[*i] == ASSIGNEMENT_WORD || !is_assig(lex.name[*i]))
			*i = *i + 1;
		else
			return (0);
	}
	*i = 0;
	while (lex.name[*i])
	{
		name = ft_get_var(lex.name[*i]);
		value = ft_get_value(lex.name[*i]);
		add_to_set(name, value);
		ft_strdel(&name);
		ft_strdel(&value);
		*i = *i + 1;
	}
	return (0);
}
