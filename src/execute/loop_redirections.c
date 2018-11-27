/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop_redirections.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/23 20:31:56 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/25 14:02:23 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			ft_redirect_output(t_redirect *redirect, t_loop *loop)
{
	int		flag;

	flag = 0;
	if (redirect->redirect == GREAT || redirect->redirect == DGREAT)
	{
		if (ft_check_file_is_directory(redirect->file) == -1)
		{
			loop->error_redir_nb = -1;
			return (EXIT_FAILURE);
		}
		flag = ft_return_flag(redirect);
		if ((loop->fd_out = ft_open_redirect(redirect->file, flag, O_WRONLY))
				< 0)
			if (ft_check_permission(redirect->file) == -1)
			{
				loop->error_redir_nb = -2;
				return (EXIT_FAILURE);
			}
		dup2(loop->fd_out, redirect->fd);
	}
	return (EXIT_SUCCESS);
}

int			ft_redirect_input(t_redirect *redirect, t_loop *loop)
{
	if (redirect->redirect == LESS)
	{
		if (ft_check_source(redirect->file) == -3)
		{
			loop->error_redir_nb = -3;
			return (EXIT_FAILURE);
		}
		if ((loop->fd_in = ft_open_redirect(redirect->file, O_RDONLY, 0))
				< 0)
			if (ft_check_permission(redirect->file) == -1)
			{
				loop->error_redir_nb = -2;
				return (EXIT_FAILURE);
			}
	}
	return (EXIT_SUCCESS);
}

int			ft_redirections(t_redirect *redirect, t_loop *loop)
{
	if (redirect->redirect == DLESS)
	{
		loop->fd_in = ft_redirect_heredoc(redirect);
		if (g_h == 1)
		{
			g_h = 0;
			return (EXIT_FAILURE);
		}
	}
	if (ft_redirect_output(redirect, loop) == EXIT_FAILURE ||
			ft_redirect_input(redirect, loop) == EXIT_FAILURE)
	{
		ft_print_message(redirect->file, loop->error_redir_nb);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			ft_aggregations(t_redirect *redirect, int fd_one, t_loop *loop)
{
	if (redirect->redirect == GREATAND || redirect->redirect == LESSAND
			|| redirect->redirect == ANDGREAT)
	{
		if (ft_check_file_is_directory(redirect->file) == 0)
		{
			if (ft_strcmp("-", redirect->file) == 0)
				close(redirect->fd);
			else if (ft_strcmp("1", redirect->file) == 0)
				dup2(fd_one, STDERR_FILENO);
			else if (ft_strcmp("2", redirect->file) == 0)
				dup2(STDERR_FILENO, fd_one);
			else
				loop->error_redir_nb = -4;
		}
		else
			loop->error_redir_nb = -1;
	}
	if (loop->error_redir_nb < 0 && loop->error_redir_nb > -5)
	{
		ft_print_message(redirect->file, loop->error_redir_nb);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			ft_loop_redirect(t_redirect *redirect, int fd2, int fd_one,
		t_loop *loop)
{
	if (fd2 > 1)
	{
		loop->fd_out = ft_open_redirect(".tmp_file", O_APPEND, O_WRONLY);
		dup2(loop->fd_out, 1);
	}
	while (redirect)
	{
		loop->error_redir_nb = 0;
		if (ft_redirections(redirect, loop) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ft_aggregations(redirect, fd_one, loop) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		redirect = redirect->next;
	}
	return (EXIT_SUCCESS);
}
