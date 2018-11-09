/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 17:06:30 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/08 17:35:58 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void				add_last_param(char **cmd)
{
	if (cmd)
		add_to_set("_", cmd[ft_tablen(cmd) - 1]);
}

static int				ft_check_is_binary_execute(t_op *opera, t_loop
		*loop)
{
	if (ft_check_file_is_regular(opera->cmd[0]) == -4)
	{
		if (ft_check_file_is_regular2(opera->cmd[0]) == -5)
		{
			if (opera->cmd[0][0] != '.' && opera->cmd[0][1] != '/' && opera->cmd[0][0] != '/')
				return (3);
		}
		else
		{
			if (opera->cmd[0][0] != '.' && opera->cmd[0][1] != '/' && opera->cmd[0][0] != '/')
				return (3);
			else
			{
				ft_print_message(opera->cmd[0], -2);
				loop->result = -1;
				return (-1);
			}
		}
	}
	return (0);
}

static void				ft_exec_next(t_op *opera, pid_t pid, int pfd[2], t_loop
		*loop)
{
	if (loop->ok != 3)
	{
		loop->ok == 0 ? loop->bin = ft_search_bin(opera->cmd[0]) : 0;
		if (isbuiltin(opera->cmd[0], 2) == EXIT_SUCCESS)
		{
			loop->result = ft_builtins(opera, loop);
			loop->ok = 2;
		}
	}
	ft_solve(opera, loop, &pid, pfd);
	add_last_param(opera->cmd);
}

int						ft_exec(t_op *opera, t_loop *loop, int *pfd)
{
	pid_t	pid;

	pid = -1;
	loop->ok = 0;
	if (!opera->cmd)
		return (0);
	if ((loop->ok = ft_check_is_binary_execute(opera, loop)) == -1)
		return (EXIT_FAILURE);
	if (isbuiltin(opera->cmd[0], 0) == EXIT_SUCCESS)
	{
		loop->bin = ft_strdup("isbuiltin");
		loop->result = ft_builtins(opera, loop);
		if (loop->exit == 1)
			return (1);
		loop->ok = 1;
	}
	ft_exec_next(opera, pid, pfd, loop);
	return (0);
}
