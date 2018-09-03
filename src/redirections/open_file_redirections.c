/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   open_file_redirections.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:37:51 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 18:40:33 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int			ft_open_redirect(char *file, int flag, int flag2)
{
	int ret2;
	if (flag2 == O_WRONLY)
		return (ret2 = open(file, O_WRONLY | flag | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR));
	return (EXIT_FAILURE);
}
