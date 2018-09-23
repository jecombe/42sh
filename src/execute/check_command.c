/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_command.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 04:29:26 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/23 20:13:46 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			ft_check_command(char *cmd)
{
	if (ft_strcmp("echo", cmd) == 0)
		return (1);
	if (ft_strcmp("cd", cmd) == 0)
		return (2);
	else if (ft_strcmp("exit", cmd) == 0)
		return (3);
	else if (ft_strcmp("env", cmd) == 0)
		return (4);
	else if (ft_strcmp("setenv", cmd) == 0)
		return (5);
	else if (ft_strcmp("unsetenv", cmd) == 0)
		return (6);
	else if (ft_strcmp("hash", cmd) == 0)
		return (7);
	else if (ft_strcmp("set", cmd) == 0)
		return (8);
	else if (ft_strcmp("unset", cmd) == 0)
		return (9);
	else if (ft_strcmp("export", cmd) == 0)
		return (10);
	else if (ft_strcmp("ft_assign", cmd) == 0)
		return (11);
	else
		return (0);
}
/*
char **g_bin;
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

char		*ft_search_bin2(char *cmd)
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
}*/

char			*ft_check_command2(char *cmd)
{
	//ft_get_bin();
	if (ft_strcmp("echo", cmd) == 0)
		return ("good");
	if (ft_strcmp("cd", cmd) == 0)
		return ("good");
	else if (ft_strcmp("exit", cmd) == 0)
		return ("good");
	else if (ft_strcmp("env", cmd) == 0)
		return ("good");
	else if (ft_strcmp("setenv", cmd) == 0)
		return ("good");
	else if (ft_strcmp("unsetenv", cmd) == 0)
		return ("good");
	else if (ft_strcmp("hash", cmd) == 0)
		return ("good");
	else if (ft_strcmp("set", cmd) == 0)
		return ("good");
	else if (ft_strcmp("unset", cmd) == 0)
		return ("good");
	else if (ft_strcmp("export", cmd) == 0)
		return ("good");
	else if (ft_strcmp("ft_assign", cmd) == 0)
		return ("good");
	else
		return (ft_search_bin(cmd));
}
