/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_setenv.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/11 04:13:47 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/09 06:40:12 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			ft_setenv(const char *name, const char *value)
{
	char	*s;
	int		i;

	s = NULL;
	i = -1;
	if (name == NULL)
		return (ft_env((t_op *)0));
	if (ft_strchr(name, '='))
		return (ft_bierrors("setenv", NULL, BIEQUAL));
	if (!g_env || !(s = ft_envset_line((const char **)g_env, name)))
		ft_malloc_cmd(&g_env, (s = ft_envset_join(name, value)));
	else if (g_env)
	{
		while (g_env[++i])
			if ((ft_strcmp(g_env[i], s)) == 0)
			{
				ft_strdel(&g_env[i]);
				g_env[i] = ft_envset_join(name, value);
			}
	}
	add_to_set((char*)name, (char*)value);
	ft_strdel(&s);
	return (EXIT_SUCCESS);
}
