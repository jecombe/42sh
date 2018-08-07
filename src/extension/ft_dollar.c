/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_dollar.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/05 00:32:29 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/07 04:04:19 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"
#include "../../include/builtins.h"
int			ft_dollar(char **cmd, int *j)
{
	char	*tmp;
	char	*tmpnext;
	char	*s;

	tmp = ft_strsub(*cmd, 0, *j);
	printf("tmp = %s\n", tmp);
	tmpnext = ft_strsub(*cmd, *j + 1, ft_strlen(*cmd) - *j);
	printf("tmpnext = .%s.\n", tmpnext);
	ft_strdel(cmd);
//	if ((s = ft_envset_value((const char **)g_set, tmpnext)))
//		*cmd = ft_strjoin(tmp, s);
	if ((s = ft_envset_value((const char **)g_env, tmpnext)))
		*cmd = ft_strjoin(tmp, s);
	else
		*cmd = ft_strdup(tmp);
	ft_strdel(&s);
	*j = ft_strlen(*cmd);
//	ft_env();
	return (0);
}
