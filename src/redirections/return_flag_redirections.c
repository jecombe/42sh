/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   return_flag_redirections.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:38:59 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/08 06:04:56 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int		ft_return_flag(t_op *t_exec)
{
	if (t_exec->redirect)
	{
		if (t_exec->redirect->redirect == LESS)
			return (O_RDONLY);
		if (t_exec->redirect->redirect == DGREAT)
			return (O_APPEND);
		if (t_exec->redirect->redirect == GREAT)
			return (O_TRUNC);
		if (t_exec->redirect->redirect == DLESS)
			return (HEREDOC);
	}
	return (-1);
}
