/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/15 05:59:21 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/17 02:28:45 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"
#include "../../include/builtins.h"

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
				return (EXIT_FAILURE);
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
	char	curpath[PATH_MAX];
	char	operand[PATH_MAX];
	char	*home;
	char	cwd[PATH_MAX];

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

int			ft_cd(t_op *exec, int flags)
{
	t_cd	*cd;
	char	flag;
	int		j;
	char	*curpath;

	j = 1;
	flag = '\0';
	if (exec->cmd[j])
		if (ft_flags((const char **)exec->cmd, &flag, &j))
			return (EXIT_FAILURE);
	if (exec->cmd[j] && ft_strcmp(exec->cmd[j], "-") == 0)
		curpath = ft_envset_value((const char **)g_env, "OLDPWD");
	else
		curpath = ft_create_curpath(exec->cmd[j], flag);
	if (!(curpath))
		return (EXIT_FAILURE);
	ft_putendl(curpath);
	chdir(curpath);
	ft_strdel(&curpath);
	return (EXIT_SUCCESS);
}
