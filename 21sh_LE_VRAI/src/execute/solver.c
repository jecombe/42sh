/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solver.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:18:16 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 18:32:22 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

void		ft_skip_n(char *line)
{
	int i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
}
void	ft_read_line(int fd, char *s)
{
	char	line[100];
	char	*list[100];
	int		i;
	ssize_t	retval;

	ft_memset(line, 0, 100);
	ft_memset(list, 0, 100 * sizeof(*list));
	i = 0;
	while ((retval = read(1, line, 4096)) > 0)
	{
		ft_skip_n(line);
		if (ft_strcmp(line, s) == 0)
			break ;
		else
			list[i++] = ft_strdup(line);
		ft_memset(line, 0, 100);
	}
	i = -1;
	while (list[++i])
		write(fd, list[i], ft_strlen(list[i]));
}

int		ft_heredoc(t_op *t_exec, char *bin, int flag)
{
	printf("HEREDOC-%s-\n", t_exec->redirect->file);
	int fd[2];
	pipe(fd);
	ft_read_line(fd[1], t_exec->redirect->file);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_exec(t_exec, g_env, bin, flag);
	return (0);
}
int		ft_solver(t_op *t_exec, char **env)
{
	ft_get_bin(env);
	char *tmp_bin;
	int ok = 0;
	int flag;

	flag = ft_return_flag(t_exec);
	if (flag == 10)
	{
		tmp_bin = ft_search_bin(t_exec->cmd[0]);
		if (ft_heredoc(t_exec, tmp_bin, flag ) == 0)
			return (0);
		else
			return (2);
	}
	if ((ok = ft_check_command(t_exec->cmd[0])) != 0)
	{
		if (ft_builtins(t_exec, ok, flag) == 0)
			return (0);
		else
			return (2);
	}
	else
	{
		tmp_bin = ft_search_bin(t_exec->cmd[0]);
		if (ft_exec(t_exec, env, tmp_bin, flag) == 0)
			return (0);
		else
			return (2);
	}
	return (0);
}
