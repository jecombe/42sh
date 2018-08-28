/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/15 05:59:21 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/28 19:34:45 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/builtins.h"

static int	ft_cd_error(const char *cmd, const int stat)
{
	ft_putstr_fd("101sh: cd: ", 2);
	if (stat == 1)
	{
		ft_putchar_fd('-', 2);
		ft_putchar_fd(*cmd, 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", 2);
	}
	if (stat == 2)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	return (EXIT_FAILURE);
}

int		ft_flags(const char **cmd, char *flag, int *idx)
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

char		*ft_create_curpath(char *cmd, char flag)
{
	char	curpath[BI_MAX];
	char	operand[BI_MAX];
	char	*home;
	char	cwd[BI_MAX];

	ft_strclr(curpath);
	ft_strclr(operand);
	ft_strclr(cwd);
	if (!cmd && !(home = ft_getenv("HOME", g_env)))
		return (EXIT_SUCCESS);
	else if (!cmd && home)
		ft_strcpy(operand, home);
	else
		ft_strcpy(operand, cmd);
	ft_strcpy(curpath, operand);
	if (flag != 'P' && curpath[0] != '/')
	{
		ft_strclr(curpath);
		if (!getcwd(cwd, sizeof(cwd)))
			return (NULL);
		ft_strcpy(curpath, cwd);
		curpath[ft_strlen(curpath) - 1 ] != '/' ? ft_strcat(curpath, "/") : 0;
		ft_strcat(curpath, operand);
	}
	return (ft_strdup(curpath));
}

static int	ft_chdir(char **curpath, const char *cmd, int fd_open, int redirection)
{
	char	*pwd;

	pwd = NULL;
	if (chdir(*curpath) == -1)
	{
		ft_strdel(&(*curpath));
		return (ft_bierrors("cd", cmd, BINOFOUND));
	}
	if (cmd && ft_strcmp(cmd, "-") == 0)
	{
		if (redirection == 0)
		{
			fd_open = 1;
		}
			ft_putstr_fd(*curpath, fd_open);
			ft_putchar_fd('\n', fd_open);
	}
	/*else
		ft_putendl(*curpath);*/
	pwd = ft_envset_value((const char **)g_env, "PWD");
	ft_setenv("PWD", *curpath);
	ft_setenv("OLDPWD", pwd);
	ft_strdel(&pwd);
	return (EXIT_SUCCESS);
}

int			ft_cd(t_op *exec, int flags)
{
	char	flag;
	int		j;
	char	*curpath;
	int		fd_open;
	t_op *op = NULL;
	int redirection;
int i = 0;
	j = 1;
	flag = '\0';
	if (exec->cmd[j])
		if (ft_flags((const char **)exec->cmd, &flag, &j))
			return (EXIT_FAILURE);
		if (exec->redirect)
	{
		//***********Gestion des mutliples redirections*********//
		pid_t pid;
		if ((fd_open = ft_loop_redirect(exec->redirect, NULL, pid, 1, exec->cmd + i, op, -1)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else
		{
			redirection = 1;
			if (exec->redirect->fd > 1)
				fd_open = exec->redirect->fd;
		}
		/////**********************************************************////
	}
	else
		redirection = 0;
	if (exec->cmd[j] && ft_strcmp(exec->cmd[j], "-") == 0)
		curpath = ft_envset_value((const char **)g_env, "OLDPWD");
	else
		curpath = ft_create_curpath(exec->cmd[j], flag);
	if (!(curpath))
		return (EXIT_FAILURE);
	if (ft_chdir(&curpath, exec->cmd[j], fd_open, redirection))
		return (EXIT_FAILURE);
	ft_strdel(&curpath);
	return (EXIT_SUCCESS);
}
