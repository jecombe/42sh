/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/15 05:59:21 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 00:56:27 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	ft_cd_flags(const char **cmd, char *flag, int *idx)
{
	int		i;
	int		j;

	i = 1;
	j = -1;
	if (!cmd[i] || ft_strcmp(cmd[i], "-") == 0)
		return (EXIT_SUCCESS);
	while (cmd[i])
	{
		if (cmd[i][++j] != '-')
			break ;
		while (cmd[i][++j])
		{
			if (cmd[i][j] != 'P' && cmd[i][j] != 'L')
				return (ft_bierrors("cd", &cmd[i][j], BIFLAG));
			if (*flag)
				*flag = (*flag == 'P') ? 'L' : 'P';
			else
				*flag = cmd[i][j];
		}
		i++;
		j = -1;
	}
	*idx = i;
	return (EXIT_SUCCESS);
}

static int	ft_chdir(char **curpath, const char *cmd)
{
	char	*pwd;

	pwd = NULL;
	if (cmd && ft_strcmp(cmd, "-") == 0)
	{
		ft_strdel(curpath);
		if (!(*curpath = ft_envset_value((const char **)g_env, "OLDPWD")))
			return (EXIT_SUCCESS);
		ft_putendl_fd(*curpath, STDOUT_FILENO);
	}
	if (chdir(*curpath) == -1)
	{
		ft_strdel(&(*curpath));
		return (ft_bierrors("cd", cmd, BINOFOUND));
	}
	pwd = ft_envset_value((const char **)g_env, "PWD");
	ft_setenv("PWD", *curpath);
	ft_setenv("OLDPWD", pwd);
	ft_strdel(&pwd);
	return (EXIT_SUCCESS);
}

int			ft_cd(t_op *exec)
{
	int		j;
	char	flag;
	char	*curpath;

	j = 1;
	flag = '\0';
	curpath = NULL;
	if (exec->cmd[j] && ft_cd_flags((const char **)exec->cmd, &flag, &j))
		return (EXIT_FAILURE);
	if (!(curpath = (exec->cmd[j]) ? ft_strdup(exec->cmd[j]) :
				ft_getenv("HOME", g_env)))
		return (EXIT_SUCCESS);
	if (flag != 'P')
	{
		ft_canonical(&curpath);
		//ft_rules(&curpath);
	}
	if (!(curpath))
		return (EXIT_FAILURE);
	if (ft_chdir(&curpath, exec->cmd[j]))
		return (EXIT_FAILURE);
	ft_strdel(&curpath);
	return (EXIT_SUCCESS);
}
