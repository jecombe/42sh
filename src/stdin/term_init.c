/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_init.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/10 02:51:08 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/09 23:53:18 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

int		term_reinit(struct termios *raw_mode)
{
	static struct termios	term_default;
	static int				state = 0;

	if (state == 0)
	{
		tcgetattr(STDIN_FILENO, &term_default);
		state = 1;
	}
	*raw_mode = term_default;
	return (0);
}

int		get_term_raw_mode(int mode)
{
	struct termios raw_mode;

	term_reinit(&raw_mode);
	if (mode)
	{
		raw_mode.c_lflag &= ~(ECHO | ICANON | ISIG);
		raw_mode.c_cflag &= ~(CSIZE | PARENB);
		raw_mode.c_cflag |= CS8;
		raw_mode.c_cc[VMIN] = 1;
		raw_mode.c_cc[VTIME] = 1;
		tcsetattr(STDIN_FILENO, TCSANOW, &raw_mode);
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &raw_mode);
	return (0);
}
