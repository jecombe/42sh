/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_env.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/10 06:20:38 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/12 18:17:01 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void	ft_print_env(int fd_open)
{
	int		i;

	i = -1;
	if (g_env)
		while (g_env[++i])
			ft_putendl_fd(g_env[i], fd_open);
}

static int	ft_env_flags(const char **cmd, char *flag, int *idx, int fd_open)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (cmd[++i])
	{
		if (cmd[i][++j] != '-')
			break ;
		while (cmd[i][++j])
		{
			if (cmd[i][j] != 'i')
				return (ft_bierrors("env", &cmd[i][j], BIFLAG, fd_open));
			*flag = 'i';
		}
	}
	*idx = i;
	return (EXIT_SUCCESS);
}

static int	ft_assign_env(const char **cmd, char flag, int *idx, int fd_open)
{
	char	**grid;

	grid = NULL;
	if (flag == 'i')
		ft_tabdel(&g_env);
	while (cmd[*idx])
	{
		if (!(ft_strchr(cmd[*idx], '=')))
			break ;
		if (!(grid = ft_strsplit(cmd[*idx], '=')))
			return (EXIT_FAILURE);
		ft_setenv(grid[0], grid[1], fd_open);
		ft_tabdel(&grid);
		(*idx)++;
	}
	return (EXIT_SUCCESS);
}

static int	ft_exec_env(const char **cmd, int i)
{
	pid_t	cpid;
	int		status;
	char	**args;
	char	*utility;

	cpid = -1;
	status = 1;
	args = NULL;
	utility = NULL;
	while (cmd[i])
		ft_malloc_cmd(&args, (char *)cmd[i++]);
	if (args != NULL)
	{
		utility = ft_search_bin(args[0]);
		if ((cpid = fork()) == 0)
			if ((execve(utility, args, g_env)) == -1)
				return (EXIT_FAILURE);
		if (cpid > 0)
			wait(&status);
		ft_tabdel(&args);
		ft_strdel(&utility);
		return ((WEXITSTATUS(status) == 1) ? EXIT_FAILURE : EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int			ft_env(t_op *exec, int fd, int p)
{
	int		i;
	char	flag;
	char	**env;
	int fd_open;

	i = 0;
	flag = '\0';
	env = NULL;
	if (fd > 2)
		if ((fd_open = ft_loop_redirect(exec->redirect, 1, fd, 0)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		fd = 1;
		if ((fd_open = ft_loop_redirect(exec->redirect, 1, fd, 0)) == EXIT_FAILURE)
			return(EXIT_FAILURE);
		if (fd_open < 1)
			fd_open = 1;
		if (exec->redirect)
		{
			if (exec->redirect->fd > 1)
				fd_open = exec->redirect->fd;
		}
		if (exec->redirect == NULL && p == 1)
			fd_open = 5;
	if (!exec || exec->cmd[1] == NULL)
		ft_print_env(fd_open);
	else
	{
		if (!(env = ft_tabdup(g_env)))
			return (EXIT_FAILURE);
		if (ft_env_flags((const char **)exec->cmd, &flag, &i, fd_open))
			return (EXIT_FAILURE);
		if (ft_assign_env((const char **)exec->cmd, flag, &i, fd_open))
			return (EXIT_FAILURE);
		ft_exec_env((const char **)exec->cmd, i);
		ft_tabdel(&g_env);
		g_env = ft_tabdup(env);
		ft_tabdel(&env);
	}
	return (EXIT_SUCCESS);
}
