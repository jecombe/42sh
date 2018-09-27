/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   42sh_exit.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/16 06:36:43 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 00:24:23 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		hash_delete(void)
{
	t_hashtable	*hashtable;
	int			i;

	hashtable = NULL;
	i = -1;
	ft_save_hash(&hashtable);
	while (++i < MAX_HASH)
		if (hashtable[i].hashcase)
			while (hashtable[i].hashcase)
			{
				ft_strdel(&hashtable[i].hashcase->command);
				hashtable[i].hashcase = hashtable[i].hashcase->next;
			}
	free(hashtable);
}

void		exit_shell(void)
{
	if (g_env)
		ft_tabdel(&g_env);
	if (g_set)
		ft_tabdel(&g_set);
	hash_delete();
	history_save((char ***)NULL, (char *)NULL, 2, (char *)NULL);
}
