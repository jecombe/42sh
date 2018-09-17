/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/15 05:59:21 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/13 14:59:44 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	ft_cd_error(const char *cmd, const int stat)
{
	ft_putstr_fd("101sh: cd: ", STDERR_FILENO);
	if (stat == 1)
	{
		ft_putchar_fd('-', STDERR_FILENO);
		ft_putchar_fd(*cmd, STDERR_FILENO);
		ft_putendl_fd(": invalid option", STDERR_FILENO);
		ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", STDERR_FILENO);
	}
	if (stat == 2)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	return (EXIT_FAILURE);
}

static int	ft_cd_flags(const char **cmd, char *flag, int *idx, int fd_open)
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
				return (ft_bierrors("cd", &cmd[i][j], BIFLAG, fd_open));
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

static int	ft_chdir(char **curpath, const char *cmd, int fd_open)
{
	char	*pwd;

	pwd = NULL;
	if (cmd && ft_strcmp(cmd, "-") == 0)
	{
		ft_strdel(curpath);
		if (!(*curpath = ft_envset_value((const char **)g_env, "OLDPWD")))
			return (EXIT_SUCCESS);
	}
	if (chdir(*curpath) == -1)
	{
		ft_strdel(&(*curpath));
		return (ft_bierrors("cd", cmd, BINOFOUND, fd_open));
	}
	pwd = ft_envset_value((const char **)g_env, "PWD");
	ft_setenv("PWD", *curpath, fd_open);
	ft_setenv("OLDPWD", pwd, fd_open);
	ft_strdel(&pwd);
	return (EXIT_SUCCESS);
}

int			ft_cd(t_op *exec, int flags, int fd, int p)
{
	int		j;
	char	flag;
	char	*curpath;
	int fd_open;
	char *pwd;

	j = 1;
	flag = '\0';
	curpath = NULL;
	if ((fd_open = ft_prelim_loop(exec, fd, 0)) == EXIT_FAILURE)
	  return (EXIT_FAILURE);
	if (exec->cmd[j] && ft_cd_flags((const char **)exec->cmd, &flag, &j, fd_open))
		return (EXIT_FAILURE);
	if (!(curpath = (exec->cmd[j]) ? ft_strdup(exec->cmd[j]) :
				ft_getenv("HOME", g_env)))
		return (EXIT_SUCCESS);

	if (flag != 'P')
	{
		ft_canonical(&curpath);
		ft_rules(&curpath);
	}
	if (exec->cmd[1] == NULL && p == 1)
	{
		chdir(curpath);
		return (EXIT_SUCCESS);
	}
	if (!(curpath))
		return (EXIT_FAILURE);
	if (ft_chdir(&curpath, exec->cmd[j], fd_open))
		return (EXIT_FAILURE);
	ft_strdel(&curpath);
	return (EXIT_SUCCESS);
}
