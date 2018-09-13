/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop_redirections.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:05:31 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/13 16:45:53 by jecombe     ###    #+. /#+    ###.fr     */
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
			if ((***loop).flag != O_RDONLY)
				if ((ft_check_file_is_directory(redirect->file) == -1))
				{
					(***loop).error = 1;
					if (redirect->next == NULL)
					{
						ft_print_message(redirect->file, 1);
						return (101);
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
		if ((***loop).flag == O_RDONLY)
			if (ft_check_source(redirect->file) == -1)
			{
				(***loop).error = 2;
				if (redirect->next == NULL)
				{
					ft_print_message(redirect->file, 2);
					return (101);
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
		if ((ft_redirect_heredoc(redirect, buil) == EXIT_SUCCESS))
		{
			if ((**loop).error > 0)
			{
				ft_print_message(redirect->file, (**loop).error);
				exit(EXIT_FAILURE);
			}
			return (101);
		}
	ret = ft_loop_5((&loop), redirect, buil, before_pipe);
	if (ret == 101)
		exit(EXIT_FAILURE);
	else if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void			ft_aggreg_file(t_redirect *redirect)
{
	if (redirect->redirect == LESSGREAT)
		printf("1\n");
	if (redirect->redirect == CLOBBER)
		printf("2\n");
	if (redirect->redirect == GREATAND)
	{
		printf("3\n");
		close(redirect->fd);
	}
	if (redirect->redirect == LESSAND)
		printf("4\n");
	if (redirect->redirect == DLESSDASH)
		printf("5\n");
	close(redirect->fd);
}

int				ft_loop_2(t_redirect *redirect, t_loop **loop, int buil,
		int bef_pi)
{
	int			fd_open;
	int			ret;

	fd_open = 0;
	while (redirect)
	{
		(*loop)->i++;
		(*loop)->flag = ft_return_flag(redirect);
		//ft_aggreg_file(redirect);
		if ((ret = ft_loop_3(&(*loop), redirect, buil, bef_pi)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (redirect->redirect != DLESS && bef_pi == 0 && (*loop)->error == 0 && ret != 101)
			fd_open = ft_open_redirect(redirect->file, (*loop)->flag, (*loop)->flag2);
		if ((*loop)->flag == O_RDONLY && buil == 0)
			break;
		redirect = redirect->next;
	}
	if (bef_pi == 0 && (*loop)->error == 0)
	{
		if (buil == 1 || (*loop)->flag == O_RDONLY)
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
		if ((buil == 1) || (loop->flag == O_RDONLY))
			return (fd_open);
	}
	return (EXIT_SUCCESS);
}

int			ft_fd_bquote(t_loop *loop, int fd2, int buil, int fd_open)
{
	if (fd2 > 1)
	{
		loop->flag = O_TRUNC;
		loop->flag2 = O_WRONLY;
		fd_open = ft_open_redirect(".tmp_file", loop->flag, loop->flag2);
		if (buil == 0)
		{
			dup2(fd_open, 1);
			close(fd_open);
			return (42);
		}
		return (fd_open);
	}
	return (0);
}

int				ft_loop_redirect(t_redirect *redirect,  int buil, int fd2,
		int before_pipe)
{
	int			fd;
	int			fd_open;
	t_loop		loop;
	int			flag2;

	loop = ft_init_loop();
	if ((fd_open = ft_fd_bquote(&loop, fd2, buil, fd_open)) == 42)
		return (EXIT_SUCCESS);
	if (buil == 1 && redirect == NULL && fd2 > 1)
		return (fd_open);
	fd_open = ft_loop(redirect, &loop, buil, before_pipe);
	if (fd_open == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (buil == 0 && loop.flag == O_RDONLY && redirect != NULL)
	{
		dup2(fd_open, STDIN_FILENO);
		if (redirect->next)
			return (ft_loop_redirect(redirect->next, 0, fd2, 0));
	}
	if (buil == 1 && loop.flag != HEREDOC)
		return (fd_open);
	return (EXIT_SUCCESS);
}
