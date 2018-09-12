/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_to_set.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/25 04:40:33 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:01:40 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void			sort_set(void)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;
	char	*tmp2;

	k = -1;
	if (g_set)
	{
		while (g_set[++k])
		{
			i = -1;
			while (g_set[++i])
			{
				j = i;
				while (g_set[++j] && ft_strcmp(g_set[i], g_set[j]) > 0)
				{
					tmp = ft_strdup(g_set[i]);
					tmp2 = ft_strdup(g_set[j]);
					ft_strdel(&g_set[i]);
					ft_strdel(&g_set[j]);
					g_set[i] = ft_strdup(tmp2);
					g_set[j] = ft_strdup(tmp);
					ft_strdel(&tmp);
					ft_strdel(&tmp2);
				}
			}
		}
	}
}

static int			not_found(char *to_add)
{
	if (to_add)
		ft_malloc_cmd(&g_set, to_add);
	sort_set();
	return (0);
}

int					add_to_set(char *name, char *value)
{
	char	*s;
	int		i;

	s = NULL;
	i = -1;
	if (name == NULL)
		return (EXIT_FAILURE);
	if (ft_strchr(name, '='))
		return (EXIT_FAILURE);
	if (!(s = ft_envset_line((const char **)g_set, name)))
		not_found((s = ft_envset_join(name, value)));
	else
	{
		while (g_set[++i])
			if ((ft_strcmp(g_set[i], s)) == 0)
				break ;
		ft_strdel(&g_set[i]);
		g_set[i] = ft_envset_join(name, value);
	}
	ft_strdel(&s);
	return (EXIT_SUCCESS);
	/*int			i;
	int			j;
	int			find;
	char		*to_add;

	find = 0;
	i = 0;
	to_add = concat_name_value(name, value);
	if (g_set && to_add)
		while (g_set[i] && find == 0)
		{
			j = 0;
			while (g_set[i][j] == name[j] && g_set[i][j] && name[j])
				j++;
			g_set[i][j] == '=' && j != 0 ? find = 1 : i++;
		}
	if (find == 1)
	{
		ft_strdel(&g_set[i]);
		g_set[i] = ft_strdup(to_add);
	}
	else
		not_found(to_add);
	to_add ? ft_strdel(&to_add) : 0;*/
	return (0);
}
