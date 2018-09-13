/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_signal.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/29 05:34:53 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/13 21:18:13 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		ft_outchar(int c)
{
	return (write(1, &c, 1));
}

static void		ft_handle_stp(int sig)
{

	(void)sig;
	tputs(tgetstr("cd", NULL), 1, ft_outchar);
	signal(SIGINT, SIG_DFL);
//	signal(SIGTSTP, SIG_DFL);
	ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
}

static void		ft_handle_quit(int sig)
{
	char	*tmp;
	(void)sig;
	if ((tmp = ft_getenv("PID_BIN", g_set)))
	{
	//	kill(atoi(tmp), 9);
		ft_putchar('\n');
		ft_strdel(&tmp);
	}
}

static void		ft_handle_continue(int sig)
{
	(void)sig;
	signal(SIGTSTP, ft_handle_stp);
	signal(SIGCONT, ft_handle_continue);
}

static void		sig_handler(int sig)
{
	if (sig == SIGTSTP)
		ft_handle_stp(sig);
	else if (sig == SIGCONT)
		ft_handle_continue(sig);
	else if (sig == SIGINT)
		ft_handle_quit(sig);
	else if (sig == SIGQUIT)
		ft_handle_quit(sig);
	else if (sig == SIGKILL)
		ft_handle_quit(sig);
	else if (sig == SIGTERM)
		ft_handle_quit(sig);
}

void			signal_shell(void)
{
	int				i;

	i = 0;
	while (i < 33)
		signal(i++, sig_handler);
}
