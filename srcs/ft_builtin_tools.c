/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_builtin_tools.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/12 23:33:38 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/04/21 19:42:18 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_builtin_join(const char *name, const char *value)
{
	char	*tmp;
	char	*s;

	tmp = NULL;
	s = NULL;
	if (name == NULL)
		return (NULL);
	tmp = ft_strjoin(name, "=");
	if (value != NULL)
		s = ft_strjoin(tmp, value);
	else
		s = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (s);
}
