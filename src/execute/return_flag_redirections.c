/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   return_flag_redirections.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/02 15:38:59 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 04:41:37 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		ft_return_flag(t_redirect *redirect)
{
	if (redirect)
	{
		if (redirect->redirect == DGREAT)
			return (O_APPEND);
		if (redirect->redirect == GREAT)
			return (O_TRUNC);
	}
	return (NOTHING);
}
