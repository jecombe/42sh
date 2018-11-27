/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh42_exit.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 16:21:36 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/22 01:49:07 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		hash_delete(void)
{
	t_hashtable	*hashtable;
	t_hashcase	*tmp;
	int			i;

	hashtable = NULL;
	tmp = NULL;
	i = -1;
	ft_save_hash(&hashtable);
	while (++i < MAX_HASH)
		if (hashtable[i].hashcase)
			while (hashtable[i].hashcase)
			{
				ft_strdel(&hashtable[i].hashcase->command);
				ft_strdel(&hashtable[i].hashcase->raccmd);
				tmp = hashtable[i].hashcase->next;
				free(hashtable[i].hashcase);
				hashtable[i].hashcase = tmp;
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
	ft_strdel(&g_cmd);
	history_save((char ***)NULL, (char *)NULL, 2, (char *)NULL);
	get_next_line(-101, NULL);
}
