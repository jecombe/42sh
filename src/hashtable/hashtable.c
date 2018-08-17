/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hashtable.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/17 04:38:30 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/17 06:17:43 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/hashtable.h"

int		ft_hash(const char *cmd)
{
	int i;
	int hash;

	hash = 0;
	i = -1;
	while (cmd[++i])
		hash += (unsigned char)cmd[i];
	hash %= 100;
	return (hash);
}

void		ft_hash_print(t_hashtable *hashtable)
{
	int		i;
	t_hashcase	*hashcase;
	int		blank;

	i = -1;
	hashcase = NULL;
	blank = 0;
	ft_putendl("hits\tcommand");
	while (++i < MAX)
	{
		if (hashtable[i].hashcase)
		{
			hashcase = hashtable[i].hashcase;
			while (hashcase)
			{
				blank = 4 - ft_nbrlen(hashcase->hits);
				while (blank--)
					ft_putchar(' ');
				ft_putnbr(hashcase->hits);
				ft_putchar('\t');
				ft_putendl(hashcase->command);
				hashcase = hashcase->next;
			}
		}
	}
}

void				ft_hashtable(char *cmd)
{
	t_hashtable		*hashtable;
	t_hashcase		*hashcase;
	int				hash;

	hashtable = NULL;
	hashcase = NULL;
	hash = 0;
	ft_save_hash(&hashtable);
	hash = ft_hash(cmd);
	hashcase = ft_create_case(cmd);
	hashtable[hash].key = hash;
	ft_hash_add(&(hashtable[hash].hashcase), hashcase);
	ft_save_hash(&hashtable);
}
