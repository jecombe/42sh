/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 17:06:30 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 11:38:11 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void				add_last_param(char **cmd)
{
	if (cmd)
		add_to_set("_", cmd[ft_tablen(cmd) - 1]);
}

static void				ft_delete_file(void)
{
	if (access(".tmp_file", 0) != -1)
		unlink(".tmp_file");
}

static void				ft_exec_next(t_op *opera, int pfd[2], t_loop *loop,
		int fd2)
{
	int		no_pipe_built;
	int		ret_isbuilt;

	no_pipe_built = 0;
	ret_isbuilt = isbuiltin(opera->cmd[0]);
	if (ret_isbuilt == EXIT_FAILURE && ft_strcmp(opera->cmd[0], "..") != 0 &&
			ft_strcmp(opera->cmd[0], ".") != 0)
	{
		loop->bin = ft_search_bin(opera->cmd[0]);
		loop->bin != NULL ? ft_hashtable(loop->bin, opera->cmd[0]) : 0;
	}
	if (ret_isbuilt == EXIT_SUCCESS)
		if ((loop->bin = ft_strdup("isbuiltin")) && opera->token != PIPE)
		{
			loop->result = ft_builtins(opera, loop);
			no_pipe_built = 1;
		}
	if (loop->bin == NULL && opera->token != PIPE)
	{
		fd2 > 1 ? g_error_bquote = 1 : 0;
		ft_command_not_found(opera, loop);
	}
	else if (no_pipe_built == 0)
		ft_solve(opera, loop, pfd);
	add_last_param(opera->cmd);
}

int						ft_exec(t_op *opera, t_loop *loop, int *pfd, int fd2)
{
	g_error_bquote = 0;
	if (!opera->cmd)
		return (0);
	ft_exec_next(opera, pfd, loop, fd2);
	if (loop->bin == NULL)
		ft_delete_file();
	return (0);
}
