/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_tild.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 10:56:19 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 11:20:48 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"
#include "../../include/init.h"

int			add_tild(char **str, int *index)
{
	char		*var;
	char		*tmp;
	int			i;
	int			j;

	j = 1;
	i = -1;
	if ((var = ft_getenv("HOME", g_env)) && (!(*str)[*index + 1] || (*str)[*index + 1] == '/'))
	{
		tmp = malloc(sizeof(char*) * (ft_strlen(*str) + ft_strlen(var)));
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

int			manage_tilde_and_dollars()
{
	return (0);
}
