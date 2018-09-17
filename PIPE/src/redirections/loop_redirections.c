/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop_redirections.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/17 04:11:44 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/17 04:11:46 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop_redirections.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:05:31 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/14 14:43:33 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

/*int				ft_loop_5(t_loop ***loop, t_redirect *redirect, int buil,
		int before_pipe)
{
	if (before_pipe == 0)
	{
		(***loop).fd = redirect->fd;
		printf("=======> %d\n", redirect->fd);
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

void			ft_aggreg_file(t_redirect *redirect, int buil, int bef_pi)
{
	if (redirect->redirect == GREATAND || redirect->redirect == LESSAND)
	{
		if (ft_strcmp("-", redirect->file) == 0)
		{
			if (buil == 0  || bef_pi == 1)
				close(redirect->fd);
			else
				redirect->fd = -1;
		}
		if (ft_strcmp("1", redirect->file) == 0)
			dup2(1, STDERR_FILENO);
		if (ft_strcmp("2", redirect->file) == 0)
			dup2(STDERR_FILENO, g_fd[1]);
	}
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
		//ft_aggreg_file(redirect, buil, bef_pi);
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
		printf("==========>> %d\n", (*loop)->fd);
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
}*/

/*int		ft_creat_great(t_redirect *redirect)
{
	int fd;

	fd = -1;
	if (redirect->redirect == DGREAT)
	{

	}
	else if (redirect->redirect == GREAT)
	{
		open(redirect->file, O_WRONLY | flag | O_CREAT, S_IRUSR | S_IRGRP
	

	}
	return (fd);
}*/

int				ft_loop_redirect2(t_redirect *redirect,  int fd2, int  ouput, int save, int input, int *fdd)
{
	int fd_input;
	int fd_output;
	int fd_org[3];
	int file;
	int flag;
	int flag2;
	file = -1;
		// fd[4000];

	// ls 2> fedf
	// fd[i] 
	if ((redirect) == NULL)
		{
			g_input = 0;
			g_output = 1;
			return (0);
		}
	while (redirect)
	{
		if (redirect->redirect == DLESS)
		{
			if (g_input <= 0)
			g_input = ft_redirect_heredoc(redirect, 0);
			//dup2(g_input, STDIN_FILENO);
			//close(g_input);
		}
		//printf("%d \n\n\n\n\n", redirect->fd);
		if (redirect->redirect == GREAT || redirect->redirect == DGREAT)
		{
			flag = ft_return_flag(redirect);
			flag2 = O_WRONLY;
			g_output = ft_open_redirect(redirect->file ,flag, flag2);
	//dup2(g_output != 0 ? g_output : g_save, STDIN_FILENO);
			//dup2(file, redirect->fd);
			///fd_dup[1] = dup(file);
			//close(g_input);
			///fd_dup[redirect->fd] = file;
			///dup2(fd_dup[redirect->fd], file);
		}

		if (redirect->redirect == LESS)
		{
			if (ft_check_source(redirect->file) == -1)
			{
					ft_print_message(redirect->file, 2);
					return (EXIT_FAILURE);
			}
			flag = O_RDONLY;
			g_input = ft_open_redirect(redirect->file, flag, 0);
			//dup2(g_input, STDIN_FILENO);
		}
		else
		redirect = redirect->next;
	}
	return (EXIT_SUCCESS);
}

int				ft_loop_redirect(t_redirect *redirect, int buil, int fd2, int before_pipe)
{
	int fd_input;
	int fd_output;
	int fd_org[3];
	int fd_dup[3];
	int file;
	int flag;
	int flag2;
	file = -1;
		// fd[4000];
	fd_org[0] = dup(STDIN_FILENO);
	fd_org[1] = dup(STDOUT_FILENO);
	fd_org[2] = dup(STDERR_FILENO);

	fd_dup[0] = STDIN_FILENO;
	fd_dup[1] = STDOUT_FILENO;
	fd_dup[2] = STDERR_FILENO;

	// ls 2> fedf
	// fd[i] 
	while (redirect)
	{
		/*if (redirect->redirect == DLESS)
		{
			fd_inp = ft_redirect_heredoc(redirect, buil);
		}
		else
			fd_input = 0;*/
		printf("PAS ICI \n\n\n\n\n");
		if (redirect->redirect == GREAT || redirect->redirect == DGREAT)
		{
			flag = ft_return_flag(redirect);
			flag2 = O_WRONLY;
			file = ft_open_redirect(redirect->file ,flag, flag2);
			dup2(file, fd_dup[redirect->fd]);
		}

		if (redirect->redirect == LESS)
		{

		}
		redirect = redirect->next;
	}
	dup2(fd_org[0], fd_dup[0]);
	dup2(fd_org[1], fd_dup[1]);
	dup2(fd_org[2], fd_dup[2]);
	return (EXIT_SUCCESS);
}
