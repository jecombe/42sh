/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop_redirections.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:05:31 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 04:41:38 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int				ft_loop_5(t_loop ***loop, t_redirect *redirect, int buil,
		int before_pipe)
{
	if (before_pipe == 0)
	{
		(***loop).fd = redirect->fd;
		if ((***loop).flag != NOTHING && (***loop).flag != HEREDOC)
		{
			if ((***loop).flag != O_RDONLY)
			{
				if ((ft_check_file_is_directory(redirect->file) == -1))
				{
					(***loop).error = 1;
					if (redirect->next == NULL)
					{
						ft_print_message(redirect->file, 1);
						return (101);
					}
				}
			}
		}
		if ((***loop).fd != NOTHING)
		{
			if ((***loop).flag == O_RDONLY)
				(***loop).flag2 = O_RDONLY;
			else
				(***loop).flag2 = O_WRONLY;
		}
	}
	return (EXIT_SUCCESS);
}

int				ft_loop_4(t_loop ***loop, t_redirect *redirect, int buil,
		int before_pipe)
{
	if (before_pipe == 0)
	{
		if ((***loop).flag == O_RDONLY)
		{
			if (ft_check_source(redirect->file) == -1)
			{
				(***loop).error = 2;
				if (redirect->next == NULL)
				{
					ft_print_message(redirect->file, 2);
					return (101);
				}
			}
		}
	}
	return (EXIT_SUCCESS);
}

int				ft_loop_3(t_loop **loop, t_redirect *redirect, int buil,
		int before_pipe)
{
	int			ret;

	ret = ft_loop_4((&loop), redirect, buil, before_pipe);
	if (ret == 101)
	{
		if (buil == 0)
		exit(EXIT_FAILURE);
		else
			return (EXIT_FAILURE);
	}
	if ((**loop).flag == HEREDOC)
	{
		if ((ft_redirect_heredoc(redirect, buil) == EXIT_SUCCESS))
		{
			if ((**loop).error > 0)
			{
				ft_print_message(redirect->file, (**loop).error);
				exit(EXIT_FAILURE);
			}
			return (101);
		}
	}
	ret = ft_loop_5((&loop), redirect, buil, before_pipe);
	if (ret == 101)
		exit(EXIT_FAILURE);
	else if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				ft_loop_2(t_redirect *redirect, t_loop **loop, int buil,
		int before_pipe)
{
	int			fd_open;
	int			ret;

	fd_open = 0;
	while (redirect)
	{
		(*loop)->i++;
		(*loop)->flag = ft_return_flag(redirect);
		ret = ft_loop_3(&(*loop), redirect, buil, before_pipe);
		if (ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (redirect->redirect != DLESS && before_pipe == 0
				&& (*loop)->error == 0 && (*loop)->flag2 != O_RDONLY && ret != 101)
			fd_open = ft_open_redirect(redirect->file, (*loop)->flag, (*loop)->flag2);
		redirect = redirect->next;
	}
	if (before_pipe == 0 && (*loop)->error == 0)
	{
		if (buil == 1)
			return (fd_open);
		dup2(fd_open, (*loop)->fd);
	}
	if ((*loop)->error > 0)
	{
		ft_print_message(NULL, (*loop)->error);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int				ft_loop(t_redirect *redirect, t_loop *loop, int buil,
		int before_pipe)
{
	int			fd_open;
	int			fd;

	if (redirect != NULL)
	{
		fd_open = ft_loop_2(redirect, &loop, buil, before_pipe);
		if (fd_open == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (buil == 1)
			return (fd_open);
	}
	return (EXIT_SUCCESS);
}

int				ft_loop_redirect(t_redirect *redirect,  int buil, int fd2,
		int before_pipe)
{
	int			fd;
	int			fd_open;
	t_loop		loop;
	int			flag2;

	loop.fd = 0;
	loop.i = 0;
	loop.flag = 0;
	loop.flag2 = 0;
	loop.error = 0;
	fd_open = 0;
	if (fd2 > 1)
	{
		loop.flag = O_TRUNC;
		loop.flag2 = O_WRONLY;
		fd_open = ft_open_redirect(".tmp_file", loop.flag, loop.flag2);
		fd = 1;
		if (buil == 0)
		{
			dup2(fd_open, fd);
			close(fd_open);
			return (EXIT_SUCCESS);
		}
	}
	if (buil == 1 && redirect == NULL && fd2 > 1)
		return (fd_open);
	fd_open = ft_loop(redirect, &loop, buil, before_pipe);
	if (buil == 1)
		return (fd_open);
	if (fd_open == EXIT_FAILURE)
		return (EXIT_FAILURE);
	/*if (fd2 > 1)
		exit(EXIT_SUCCESS);*/
	return (EXIT_SUCCESS);
}
