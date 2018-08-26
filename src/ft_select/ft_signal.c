/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_signal.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/29 05:34:53 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/05/04 01:27:34 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/ft_select.h"

static void		ft_handle_stp(int sig)
{
	t_select		*t;

	(void)sig;
	t = NULL;
	g_sign = 1;
	ft_save_shell(&t, 1);
	tputs(tgetstr("cd", NULL), 1, ft_outc);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
	ft_disable_raw(-42, &t);
}

static void		ft_handle_quit(int sig)
{
	t_select		*t;

	t = NULL;
	(void)sig;
	exit(ft_disable_raw(0, &t));
}

static void		ft_handle_continue(int sig)
{
	t_select		*t;

	(void)sig;
	g_sign = 1;
	t = NULL;
	signal(SIGTSTP, ft_handle_stp);
	signal(SIGCONT, ft_handle_continue);
	ft_save_shell(&t, 1);
	ft_enable_raw(&t);
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

void			ft_signal(void)
{
	int				i;

	i = 0;
	while (i < 33)
		signal(i++, sig_handler);
}
