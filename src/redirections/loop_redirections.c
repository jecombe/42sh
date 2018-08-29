/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop_redirections.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:05:31 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 19:33:00 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int g_fd;

int ft_loop_on_heredoc(t_redirect *redirect, int flag, char *bin_cmd, pid_t cpid)
{
	int buil;
	if (ft_redirect_heredoc(redirect, flag, bin_cmd, cpid, buil) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
			else
				return (EXIT_FAILURE);
}

int				ft_loop_2(t_redirect *redirect, int flag, char *bin_cmd, int flag2, int buil)
{
	pid_t cpid;
	int fd_open;
	int i = 0;
	while (redirect)
	{
		i++;
		flag = ft_return_flag(redirect);
		if (flag == O_RDONLY)
			if (ft_check_source(redirect->file) == -1)
				return (EXIT_FAILURE);
		if (flag == HEREDOC && ft_loop_on_heredoc(redirect, flag, bin_cmd, cpid) == EXIT_FAILURE)
			break;
		g_fd = redirect->fd;
		if (flag != NOTHING && flag != HEREDOC)
		{
			if (flag != O_RDONLY)
				if (ft_check_file_is_directory(redirect->file) == -1)
					return (EXIT_FAILURE);
		}
		if (g_fd != NOTHING)
		{
			if (flag == O_RDONLY)
				flag2 = O_RDONLY;
			else
				flag2 = O_WRONLY;
		}
		if (redirect->redirect != DLESS)
			fd_open = ft_open_redirect(redirect->file, flag, flag2, redirect->fd);
		redirect = redirect->next;
	}
	return (fd_open);
}

int				ft_loop(t_redirect *redirect, int flag, int flag2, int buil, char *bin_cmd)
{
	int i;

	i = 0;
	int fd_open;
	pid_t cpid;
	int fd;

	if (redirect != NULL)
		fd_open  = ft_loop_2(redirect, flag, bin_cmd, flag2, buil);
	if (buil == 1)
		return (fd_open);
	if (redirect == NULL && flag == HEREDOC)
		return (EXIT_SUCCESS);
	if (flag2 == O_RDONLY)
		dup2(fd_open, 0);
	else
		dup2(fd_open, g_fd);
	return(EXIT_SUCCESS);
}


int				ft_loop_redirect(t_redirect *redirect, char *bin_cmd, pid_t cpid, int buil, char **cmd, t_op *op, int fd2)
{
	int fd;
	int flag;
	int flag2;
	int fd_open = 0;
	int i;

	i = 0;
	if (fd2 > 1)
	{
		flag = O_TRUNC;
		flag2 = O_WRONLY;
		fd_open = ft_open_redirect(".tmp_file", flag, flag2, 1);
		fd = 1;
		dup2(fd_open, fd);
	}
	fd_open = ft_loop(redirect, flag, flag2, buil, bin_cmd);
	if (buil == 1)
		return (fd_open);
	return(EXIT_SUCCESS);
}
