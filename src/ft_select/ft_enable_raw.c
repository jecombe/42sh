/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_enable_raw.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/01 04:22:21 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 00:03:01 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"

void	ft_enable_raw(t_select **t)
{
	t_term		raw_on;
	char		*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		ft_error("getenv", &(*t));
	if (tgetent(NULL, name_term) != 1)
		ft_error("tgetent", &(*t));
	raw_on = ft_save_raw_off(&(*t));
	raw_on.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw_on.c_oflag &= ~(OPOST);
	raw_on.c_cflag |= (CS8);
	raw_on.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	raw_on.c_cc[VMIN] = 0;
	raw_on.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &raw_on) == -1)
		ft_error("tcsetattr", &(*t));
	tputs(tgetstr("vi", NULL), 1, ft_outc);
}
