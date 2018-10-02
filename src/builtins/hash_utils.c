/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_hash_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 22:44:53 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 04:25:32 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void				hash_clear(void)
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
				ft_strdel(&hashtable[i].hashcase->raccmd);
				free(hashtable[i].hashcase);
				hashtable[i].hashcase = hashtable[i].hashcase->next;
			}
	ft_save_hash(&hashtable);
}

t_hashtable			*ft_hashtable_create(void)
{
	t_hashtable	*hashtable;
	int			i;

	hashtable = NULL;
	i = -1;
	if (!(hashtable = (t_hashtable *)malloc(sizeof(t_hashtable) * MAX_HASH)))
		return (NULL);
	while (++i < MAX_HASH)
	{
		hashtable[i].key = 0;
		hashtable[i].hashcase = NULL;
	}
	return (hashtable);
}

t_hashcase			*ft_create_case(const char *cmd, const char *raccmd)
{
	t_hashcase	*hashcase;

	if (!(hashcase = (t_hashcase *)malloc(sizeof(t_hashcase))))
		return (NULL);
	hashcase->hits = 1;
	hashcase->command = ft_strdup(cmd);
	hashcase->raccmd = ft_strdup(raccmd);
	hashcase->next = NULL;
	return (hashcase);
}

void				ft_save_hash(t_hashtable **hashtable)
{
	static t_hashtable	*hashsave = NULL;

	if (!(hashsave))
		hashsave = *hashtable;
	else
		*hashtable = hashsave;
}

void				ft_hash_add(t_hashcase **begin, t_hashcase *hashcase)
{
	while (*begin)
	{
		if (ft_strcmp((*begin)->command, hashcase->command) == 0)
		{
			(*begin)->hits += 1;
			return ;
		}
		begin = &(*begin)->next;
	}
	hashcase->next = *begin;
	*begin = hashcase;
}
