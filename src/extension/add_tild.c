/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_tild.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 10:56:19 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/16 02:00:36 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	add_tild(char **str, int *index)
{
	char		*var;
	char		*tmp;
	int			i;
	int			j;

	j = 1;
	i = -1;
	if ((var = ft_getenv("HOME", g_env)) && (!(*str)[*index + 1] ||
	(*str)[*index + 1] == '/'))
	{
		if (!(tmp = malloc(sizeof(char*) * (ft_strlen(*str) + ft_strlen(var)))))
			return (1);
		while (var[++i])
			tmp[i] = var[i];
		ft_strdel(&var);
		while ((*str)[j])
			tmp[i++] = (*str)[j++];
		tmp[i] = '\0';
		*index = i;
		*str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else
		*index = *index + 1;
	return (0);
}

int			manage_tild_and_dollars(char ***cmd, t_bquote **i)
{
	if ((*cmd)[(*i)->i][(*i)->j] == '~' && (*i)->j == 0)
	{
		if (add_tild(&(*cmd)[(*i)->i], &(*i)->j))
			return (-1);
	}
	else if ((*cmd)[(*i)->i][(*i)->j] == '$')
		ft_dollar(cmd, &(*i)->i, &(*i)->j);
	else
		(*i)->j++;
	return (0);
}
