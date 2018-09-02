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

typedef struct s_loop
{
	int fd;
	int i;
	int flag;
	int flag2;
}				t_loop;

int				ft_loop_3(t_loop **loop, pid_t cpid, t_redirect *redirect, char *bin_cmd, int buil)
{
	if ((**loop).flag == O_RDONLY)
	{
		if (ft_check_source(redirect->file) == -1)
			return (EXIT_FAILURE);
	}
	if ((**loop).flag == HEREDOC)
	{
		if ((ft_redirect_heredoc(redirect, (**loop).flag, bin_cmd, cpid, buil) == EXIT_SUCCESS))
			return (101);
			else
				return (EXIT_FAILURE);
	}
		(**loop).fd = redirect->fd;
	if ((**loop).flag != NOTHING && (**loop).flag != HEREDOC)
	{
		if ((**loop).flag != O_RDONLY)
		{
			if ((ft_check_file_is_directory(redirect->file) == -1))
				return (EXIT_FAILURE);
		}
	}
	if ((**loop).fd != NOTHING)
	{
		if ((**loop).flag == O_RDONLY)
			(**loop).flag2 = O_RDONLY;
		else
			(**loop).flag2 = O_WRONLY;
	}
	return (EXIT_SUCCESS);
}

int				ft_loop_2(t_redirect *redirect, t_loop **loop, char *bin_cmd, int flag2, int buil)
{
	pid_t cpid;
	int fd_open;
	int ret;
	while (redirect)
	{
		(*loop)->i++;
		(*loop)->flag = ft_return_flag(redirect);
		ret = ft_loop_3(&(*loop), cpid, redirect, bin_cmd, buil);
		if (ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ret == 101)
			break;
		if (ret == 42)
			return (EXIT_FAILURE);
		if (redirect->redirect != DLESS)
			fd_open = ft_open_redirect(redirect->file, (*loop)->flag, (*loop)->flag2, redirect->fd);
		redirect = redirect->next;
	}
	if (buil == 1)
		return (fd_open);
	if ((*loop)->flag2 == O_RDONLY)
	{
		dup2(fd_open, 0);
		return (EXIT_SUCCESS);
	}
		dup2(fd_open, (*loop)->fd);
	return (EXIT_SUCCESS);
}

int				ft_loop(t_redirect *redirect, t_loop *loop, int flag2, int buil, char *bin_cmd)
{
	int i;

	i = 0;
	int fd_open;
	pid_t cpid;
	int fd;

	if (redirect != NULL)
		fd_open  = ft_loop_2(redirect, &loop, bin_cmd, flag2, buil);
	if (fd_open == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (buil == 1)
		return (fd_open);
	return(EXIT_SUCCESS);
}


int				ft_loop_redirect(t_redirect *redirect, char *bin_cmd, pid_t cpid, int buil, char **cmd, t_op *op, int fd2)
{
	int fd;
	int fd_open;
	t_loop loop;
	int flag;
	int flag2;

	loop.fd = 0;
	loop.i = 0;
	loop.flag = 0;
	loop.flag2 = 0;
	if (fd2 > 1)
	{
		flag = O_TRUNC;
		flag2 = O_WRONLY;
		fd_open = ft_open_redirect(".tmp_file", flag, flag2, 1);
		fd = 1;
		dup2(fd_open, fd);
	}
	fd_open = ft_loop(redirect, &loop, flag2, buil, bin_cmd);
	if (fd_open == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (buil == 1)
		return (fd_open);
	return(EXIT_SUCCESS);
}
/*
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
   }
//Gestion des multiples redirections
if (redirect != NULL)
{
//printf("REDIRECT NO NULL\n");
while (redirect)
{
i++;
flag = ft_return_flag(redirect);
if (flag == O_RDONLY)
if (ft_check_source(redirect->file) == -1)
return (EXIT_FAILURE);
if (flag == HEREDOC)
{
//HEREDOC
if (ft_redirect_heredoc(redirect, flag, bin_cmd, cpid, buil) == EXIT_SUCCESS)
;
else
break;
}
fd = redirect->fd;
if (flag != NOTHING && flag != HEREDOC)
{
//Si il y a des redirections, alors va checker si le fichier ne soit pas une directory
if (flag != O_RDONLY)
if (ft_check_file_is_directory(redirect->file) == -1)
return (EXIT_FAILURE);
}
if (fd != NOTHING)
{
// Si il y a pas << et qu'il y a des redirections, alors flag2 prend une valeur selon flag
if (flag == O_RDONLY)
flag2 = O_RDONLY;
else
flag2 = O_WRONLY;
}
//Pour l'instant si ce n'est pas des command builtins
if (redirect->redirect != DLESS)
fd_open = ft_open_redirect(redirect->file, flag, flag2, fd);
redirect = redirect->next;
}
if (buil == 1)
return (fd_open);
}
if (redirect == NULL && flag == HEREDOC && i == 1)
{
printf("YEAAAAAA\n");
return (EXIT_SUCCESS);
}
if (flag2 == O_RDONLY)
dup2(fd_open, 0);
else
dup2(fd_open, fd);
return(EXIT_SUCCESS);
}*/
