/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   binary.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:45:49 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/18 02:21:34 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		ft_check_direct_bin(const char *cmd)
{
	if (access(cmd, F_OK) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char		*ft_check_path_bin(const char *cmd)
{
	char		*path;
	char		**grid;
	int			i;
	char		buff[4096];

	path = NULL;
	grid = NULL;
	i = -1;
	ft_strclr(buff);
	if (!(path = ft_getenv("PATH", g_env)))
		return (NULL);
	if (!(grid = ft_strsplit(path, ':')))
		return (NULL);
	ft_strdel(&path);
	while (grid[++i])
	{
		ft_strcpy(buff, grid[i]);
		(buff[ft_strlen(buff) - 1] != '/') ? ft_strcat(buff, "/") : 0;
		if (access(ft_strcat(buff, cmd), F_OK) == 0)
			path = ft_strdup(buff);
		ft_strclr(buff);
		ft_strdel(&grid[i]);
	}
	free(grid);
	return (path);
}

int				ft_check_hash_bin(const char *cmd, char **buff)
{
	t_hashtable	*hashtable;
	t_hashcase	*hashcase;
	int			hash;

	hashtable = NULL;
	hashcase = NULL;
	hash = 0;
	ft_save_hash(&hashtable);
	hash = ft_hash(cmd);
	if (hashtable[hash].hashcase)
	{
		hashcase = hashtable[hash].hashcase;
		while (hashcase)
		{
			if (ft_strcmp(cmd, hashcase->raccmd) == 0)
			{
				*buff = ft_strdup(hashcase->command);
				return (EXIT_SUCCESS);
			}
			hashcase = hashcase->next;
		}
	}
	return (EXIT_FAILURE);
}

char		*ft_search_bin(char *cmd)
{
	char	*buff;

	buff = NULL;
	if (!(ft_check_direct_bin(cmd)))
		return (cmd);
	if (!(ft_check_hash_bin(cmd, &buff)))
		return (buff);
	if (!(buff = ft_check_path_bin(cmd)))
		return (NULL);
	return (buff);
}
