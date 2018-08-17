/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_hashtable_manage.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/17 06:13:33 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/17 06:16:13 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/hashtable.h"

t_hashtable		*ft_hashtable_create(void)
{
	t_hashtable	*hashtable;
	int			i;

	hashtable = NULL;
	i = -1;
	if (!(hashtable = (t_hashtable *)malloc(sizeof(t_hashtable) * MAX)))
		return (NULL);
	while (++i < MAX)
	{
		hashtable[i].key = 0;
		hashtable[i].hashcase = NULL;
	}
	return (hashtable);
}

t_hashcase		*ft_create_case(const char *cmd)
{
	t_hashcase	*hashcase;

	if (!(hashcase = (t_hashcase *)malloc(sizeof(t_hashcase))))
		return (NULL);
	hashcase->hits = 1;
	hashcase->command = ft_strdup(cmd);
	hashcase->next = NULL;
	return (hashcase);
}

void		ft_save_hash(t_hashtable **hashtable)
{
	static t_hashtable *hashsave = NULL;

	if (!(hashsave))
		hashsave = *hashtable;
	else
		*hashtable = hashsave;
}

void		ft_hash_add(t_hashcase **begin, t_hashcase *hashcase)
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
