/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   binary.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:45:49 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 04:41:37 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

void		ft_get_bin(char **env)
{
	int  i;
	char *bin;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			env[i]++;
			bin = ft_strdup(env[i]);
			bin = ft_avance(bin);
			g_bin = ft_strsplit(bin, ':');
		}
		i++;
	}
}

char		*ft_search_bin(char *cmd)
{
	char *tmp;
	int i;
	int t;
	struct stat st;

	i = 0;
	t = 0;
	while (g_bin[i])
	{
		tmp = ft_strdup(g_bin[i]);
		while (tmp[t])
		{
			t++;
		}
		tmp[t] = '\0';
		t = 0;
		tmp = ft_strcat(tmp, "/");
		tmp = ft_strcat(tmp, cmd);
		if (lstat(tmp, &st) == -1)
			;
		else
			return (tmp);
		i++;
	}
	return (NULL);
}
