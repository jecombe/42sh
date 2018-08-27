/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_disable_raw.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/25 10:59:35 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 01:29:33 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"

int		ft_disable_raw(int ret, t_select **t)
{
	t_term		raw_off;

	raw_off = ft_save_raw_off(&(*t));
	tputs(tgetstr("ve", NULL), 1, ft_outc);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_off) == -1)
		ft_error("tcsetattr", &(*t));
	if (!(ret == -42))
		ft_free_t_select(&(*t));
	return (ret);
}
