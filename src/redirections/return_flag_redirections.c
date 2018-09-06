/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   return_flag_redirections.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:38:59 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/04 18:24:40 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/execute.h"

int		ft_return_flag(t_redirect *redirect)
{
	if (redirect)
	{
		if (redirect->redirect == LESS)
			return (O_RDONLY);
		if (redirect->redirect == DGREAT)
			return (O_APPEND);
		if (redirect->redirect == GREAT)
			return (O_TRUNC);
		if (redirect->redirect == DLESS)
		{
			return (HEREDOC);
		}
	}
	return (NOTHING);
}
