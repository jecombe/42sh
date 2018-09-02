/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop_redirections.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:05:31 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/02 19:23:29 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int				ft_loop_4(t_loop ***loop, t_redirect *redirect, int buil, int before_pipe)
{	if (before_pipe == 0)
	{
		if ((***loop).flag == O_RDONLY)
		{
			if (ft_check_source(redirect->file) == -1)
			{
				(***loop).error = 1;
				if (redirect->next == NULL)
					exit(EXIT_FAILURE);
			}
			else
				(***loop).error = 0;
		}
	}
	return (0);
}

int				ft_loop_3(t_loop **loop, t_redirect *redirect, int buil, int before_pipe)
{
	/*if (ft_loop_4((&loop), redirect, buil, before_pipe))
	  ;*/
	if (before_pipe == 0)
	{
		if ((**loop).flag == O_RDONLY)
		{
			if (ft_check_source(redirect->file) == -1)
			{
				(**loop).error = 1;
				if (redirect->next == NULL)
					exit(EXIT_FAILURE);
			}
			else
				(**loop).error = 0;
		}
	}
	if ((**loop).flag == HEREDOC)
	{
		if ((ft_redirect_heredoc(redirect, buil) == EXIT_SUCCESS))
		{
			if (g_last == 1 && redirect->next == NULL)
			{
				if ((**loop).error == 0)
					return (101);
			}
			if ((**loop).error > 0)
				exit(EXIT_FAILURE);
		}
	}
	if (before_pipe == 0)
	{
		(**loop).fd = redirect->fd;
		if ((**loop).flag != NOTHING && (**loop).flag != HEREDOC)
		{
			if ((**loop).flag != O_RDONLY)
			{
				if ((ft_check_file_is_directory(redirect->file) == -1))
				{
					(**loop).error = 2;
					if (redirect->next == NULL)
						exit(EXIT_FAILURE);
				}
				else
					(**loop).error = 0;
			}
		}
		if ((**loop).fd != NOTHING)
		{
			if ((**loop).flag == O_RDONLY)
				(**loop).flag2 = O_RDONLY;
			else
				(**loop).flag2 = O_WRONLY;
		}
	}
	return (EXIT_SUCCESS);
}

int				ft_loop_2(t_redirect *redirect, t_loop **loop, int buil, int before_pipe)
{
	int fd_open;
	int ret;
	while (redirect)
	{
		(*loop)->i++;
		(*loop)->flag = ft_return_flag(redirect);
		ret = ft_loop_3(&(*loop), redirect, buil, before_pipe);
		if (ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ret == 101)
			break;
		if (redirect->redirect != DLESS && before_pipe == 0)
			fd_open = ft_open_redirect(redirect->file, (*loop)->flag, (*loop)->flag2, redirect->fd);
		redirect = redirect->next;
	}
	if (before_pipe == 0)
	{
		if (buil == 1)
			return (fd_open);
		if ((*loop)->flag2 == O_RDONLY)
		{
			dup2(fd_open, 0);
			return (EXIT_SUCCESS);
		}
		dup2(fd_open, (*loop)->fd);
	}
	return (EXIT_SUCCESS);
}

int				ft_loop(t_redirect *redirect, t_loop *loop, int buil, int before_pipe)
{
	int fd_open;
	int fd;

	if (redirect != NULL)
		fd_open  = ft_loop_2(redirect, &loop, buil, before_pipe);
	if (fd_open == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (buil == 1)
		return (fd_open);
	return(EXIT_SUCCESS);
}


int				ft_loop_redirect(t_redirect *redirect,  int buil, int fd2, int before_pipe)
{
	int fd;
	int fd_open;
	t_loop loop;
	int flag2;

	loop.fd = 0;
	loop.i = 0;
	loop.flag = 0;
	loop.flag2 = 0;
	loop.error = 0;
	if (fd2 > 1)
	{
		loop.flag = O_TRUNC;
		loop.flag2 = O_WRONLY;
		fd_open = ft_open_redirect(".tmp_file", loop.flag, loop.flag2, 1);
		fd = 1;
		dup2(fd_open, fd);
	}
	fd_open = ft_loop(redirect, &loop, buil, before_pipe);
	if (fd_open == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (buil == 1)
		return (fd_open);
	return(EXIT_SUCCESS);
}

