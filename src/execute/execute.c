/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execute.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 01:52:13 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/13 08:16:05 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

void			ft_write_fd(int fd, char **cmd)
{
	int i = 1;

	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
}


int				ft_while_redirect(t_redirect *redirect, char *bin_cmd, pid_t cpid, int buil, char **cmd, t_op *op, int fd2)
{
	int fd;
	int flag;
	int flag2;
	int fd_open;

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
			//************** SI < ****************//
			if (flag == O_RDONLY)
				if (ft_check_source(redirect->file) == -1)
					return (EXIT_FAILURE);
			//*************************************/

			//*********** SI << ******************//
			if (flag == HEREDOC)
			{
				//HEREDOC MARCHE PAS EN MULTIPLES
				if (ft_redirect_heredoc(redirect, flag, bin_cmd, cpid) == EXIT_SUCCESS)
					;
				else
					break;
			}
			//*******************************************************//
			fd = redirect->fd;
			if (flag != NOTHING)
			{
				//Si il y a des redirections, alors va checker si le fichier ne soit pas une directory
				if (ft_check_file_is_directory(redirect->file) == -1)
					return (EXIT_FAILURE);
			}
			if (fd != NOTHING && flag != HEREDOC)
			{
				// Si il y a pas << et qu'il y a des redirections, alors flag2 prend une valeur selon flag
				if (flag == O_RDONLY)
					flag2 = O_RDONLY;
				else
					flag2 = O_WRONLY;
			}
			//Pour l'instant si ce n'est pas des command builtins
			if (buil == 0)
				ft_open_redirect(redirect->file, flag, flag2, fd);
			else
			{
				fd_open = ft_open_redirect_builtins(redirect->file, flag, op->redirect->fd);
			}
				redirect = redirect->next;
		}
		if (buil == 1)
		{
			return (fd_open);
		}
	}
	return(EXIT_SUCCESS);

}
int				ft_exec(t_op *tmp_op, char *bin_cmd, int fd)
{
	pid_t		cpid;
	int			status;
	int			ret;
	t_redirect *redirect;

	redirect = NULL;
	ret = 0;
	if (tmp_op->redirect)
		redirect = tmp_op->redirect;
	if ((cpid = fork()) == 0)
	{
		//Gestion des multiples redirections
		if (ft_while_redirect(redirect, bin_cmd, cpid, 0, tmp_op->cmd, tmp_op, fd) == EXIT_SUCCESS)
			;
		else
			return(EXIT_FAILURE);
		//EXECVE
		if (execve(bin_cmd, tmp_op->cmd, g_env) == -1)
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	if (cpid > 0)
	{
		wait(&status);
		ret = WEXITSTATUS(status);
	}
	if (ret == 1)
	{
		//ECHEC
		return (EXIT_FAILURE);
	}
	else
	{
		//REUSSITE
		return (EXIT_SUCCESS);
	}
}
