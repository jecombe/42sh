/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   binary.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:45:49 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/09 15:46:51 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

void		ft_get_bin()
{
	int  i;
	char *bin;
	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp("PATH=", g_env[i], 5) == 0)
		{
			g_env[i]++;
			bin = ft_strdup(g_env[i]);
			bin = ft_go_to(bin, 5);
			//printf("=================+< %s\n", bin);
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

	if (ft_check_direct_command(cmd) == 0)
		return (cmd);
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
