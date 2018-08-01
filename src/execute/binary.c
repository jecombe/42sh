/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   binary.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:45:49 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 04:01:06 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

void		ft_get_bin(char **env)
{
	int  i;
	char *bin;
	printf("get bin\n");
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			env[i]++;
			bin = ft_strdup(env[i]);
			bin = ft_avance(bin);
			g_bin = ft_strsplit(bin, ':');
			printf("-%s-\n", g_bin[0]);
		}
		i++;
	}
}
char		*ft_search_bin(char *cmd)
{
	char *tmp;
	int i = 0;
	int u = 0;
	int t = 0;
	struct stat st;
	while (cmd[u])
	{
		if (cmd[u] == '\n')
		{
			cmd[u] = '\0';
			break;
		}
		u++;
	}
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
		printf("=+=+=+=+=+ %s-\n", tmp);
		if (lstat(tmp, &st) == -1)
			;
		else
		{
			printf("yes %s\n" , tmp);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}


