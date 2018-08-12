/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   return_flag_redirections.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:38:59 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/12 08:10:36 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int		ft_return_flag(t_redirect *redirect)
{
	if (redirect)
	{
		printf("REDIRECT\n");
		if (redirect->redirect == LESS)
			return (O_RDONLY);
		if (redirect->redirect == DGREAT)
			return (O_APPEND);
		if (redirect->redirect == GREAT)
			return (O_TRUNC);
		if (redirect->redirect == DLESS)
		{
			printf("OKKKKKKKKK\n");
			return (HEREDOC);
		}
	}
	return (NOTHING);
}
int		ft_return_flag2(t_op *op)
{
	if (op->redirect)
	{
		if (op->redirect->redirect == LESS)
			return (O_RDONLY);
		if (op->redirect->redirect == DGREAT)
			return (O_APPEND);
		if (op->redirect->redirect == GREAT)
			return (O_TRUNC);
		if (op->redirect->redirect == DLESS)
			return (HEREDOC);
	}
	return (NOTHING);
}
