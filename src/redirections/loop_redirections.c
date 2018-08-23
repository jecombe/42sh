/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop_redirections.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:05:31 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/14 16:06:52 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int				ft_loop_redirect(t_redirect *redirect, char *bin_cmd, pid_t cpid, int buil, char **cmd, t_op *op, int fd2)
{
	int fd;
	int flag;
	int flag2;
	int fd_open = 0;

	if (fd2 > 1)
	{
		flag = O_TRUNC;
		flag2 = O_WRONLY;
		ft_open_redirect(".tmp_file", flag, flag2, 1);
	}
	//Gestion des multiples redirections
	if (redirect != NULL)
	{
		while (redirect)
		{
			flag = ft_return_flag(redirect);
			//************** SI < ****************
			if (flag == O_RDONLY)
				if (ft_check_source(redirect->file) == -1)
					return (EXIT_FAILURE);
			//*************************************

			//*********** SI << ******************
			if (flag == HEREDOC)
			{
				//HEREDOC
				if (ft_redirect_heredoc(redirect, flag, bin_cmd, cpid, buil) == EXIT_SUCCESS)
					;
				else
					break;
			}
			//*******************************************************
			fd = redirect->fd;
			if (flag != NOTHING && flag != HEREDOC)
			{
				//Si il y a des redirections, alors va checker si le fichier ne soit pas une directory
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
			if (buil == 0 && redirect->redirect != DLESS)
				fd_open = ft_open_redirect(redirect->file, flag, flag2, fd);
			else if (buil == 1 && redirect->redirect != DLESS)
				fd_open = ft_open_redirect_builtins(redirect->file, flag, flag2);
					redirect = redirect->next;
		}
		if (buil == 1)
			return (fd_open);
	}
	if (redirect == NULL && flag == HEREDOC)
		return (EXIT_SUCCESS);
	if (fd != NOTHING)
	{
	if (flag2 == O_RDONLY)
		dup2(fd_open, 0);
		else
			dup2(fd_open, fd);
	}
	return(EXIT_SUCCESS);
}
