/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   open_file_redirections.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:37:51 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/12 06:57:04 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int			ft_open_redirect(char *file, int flag, int flag2, int fd)
{
	int ret2;
	if (flag2 == O_WRONLY)
	{
			ret2 = open(file, O_WRONLY | flag | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	}
	if (flag2 == O_RDONLY)
	{
		ret2 = open(file, O_RDONLY);
		dup2(ret2, 0);
	}
	return (ret2);
	/*else
		dup2(ret2, fd);*/
}

int				ft_open_redirect_builtins(char *file, int flag, int flag2)
{

	if (flag2 == O_WRONLY)
	{
		return (open(file, flag2 | flag | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR));

	}
	if (flag2 == O_RDONLY)
		return (open(file, flag2));
	else
		return (-11);
}
