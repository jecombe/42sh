/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   envset_manage.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/10 02:03:32 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:49:03 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

char		*ft_envset_line(const char **envset, const char *name)
{
	int		i;
	char	*tmp;
	char	*s;

	i = -1;
	tmp = NULL;
	s = NULL;
	while (envset[++i])
	{
		tmp = ft_strsub(envset[i], 0, ft_strlen(name));
		if (ft_strcmp(name, tmp) == 0 && envset[i][ft_strlen(name)] == '=')
			s = ft_strdup(envset[i]);
		ft_strdel(&tmp);
		if (s)
			break ;
	}
	return (s);
}

char		*ft_envset_value(const char **envset, const char *name)
{
	int		i;
	char	*tmp;
	char	*s;

	i = -1;
	tmp = NULL;
	s = NULL;
	while (envset[++i])
	{
		tmp = ft_strsub(envset[i], 0, ft_strlen(name));
		if (ft_strcmp(name, tmp) == 0 && envset[i][ft_strlen(name)] == '=')
			s = ft_strdup(ft_strchr(envset[i], '=') + 1);
		ft_strdel(&tmp);
		if (s)
			break ;
	}
	return (s);
}

char		*ft_envset_join(const char *name, const char *value)
{
	char	*tmp;
	char	*s;

	tmp = NULL;
	s = NULL;
	tmp = ft_strjoin(name, "=");
	if (value)
		s = ft_strjoin(tmp, value);
	else
		s = ft_strjoin(tmp, "''");
	ft_strdel(&tmp);
	return (s);
}

void			envset_del(void)
{
	t_hashtable	*hashtable;
	t_history	*history;
	int			i;

	hashtable = NULL;
	history = NULL;
	i = -1;
	ft_save_hash(&hashtable);
	history_save(&history);
	if (g_env)
		ft_tabdel(&g_env);
	if (g_set)
		ft_tabdel(&g_set);
	while (++i < MAX_HASH)
		if (hashtable[i].hashcase)
			while (hashtable[i].hashcase)
			{
				ft_strdel(&hashtable[i].hashcase->command);
				hashtable[i].hashcase = hashtable[i].hashcase->next;
			}
	free(hashtable);
	i = -1;
	while (history->cmd[++i])
		ft_strdel(&(history)->cmd[i]);
	free(history->cmd);
	free(history);

}
