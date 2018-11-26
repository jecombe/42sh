/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   return_command.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 05:41:48 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 11:38:56 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int			ft_waiting(t_loop *loop)
{
	int		status;

	status = 0;
	waitpid(loop->pid, &status, 0);
	while (wait(NULL) > 0)
		;
	if (loop->result == -1)
	{
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
		{
			binary_signal(status, loop->pid, loop->bin);
			return (WTERMSIG(status));
		}
	}
	return (loop->result);
}

int					ft_return_command(t_loop *loop)
{
	if (ft_waiting(loop) == EXIT_SUCCESS)
	{
		if (loop->bin == NULL && loop->result == -1)
		{
			add_to_set("?", "1");
			return (EXIT_FAILURE);
		}
		add_to_set("?", "0");
		ft_strdel(&loop->bin);
		return (EXIT_SUCCESS);
	}
	add_to_set("?", "1");
	ft_strdel(&loop->bin);
	return (EXIT_FAILURE);
}
