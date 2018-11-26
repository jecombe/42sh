/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_init.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/26 09:03:00 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 03:09:23 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int				ft_init_shell_struct(t_shell *sh, t_prompt *prompt)
{
	g_cmd = NULL;
	g_interupt = 0;
	g_cursor_pos = 0;
	sh->tmp_line = NULL;
	sh->tabu = -1;
	sh->hist = -2;
	sh->sel = NULL;
	sh->t.cmd = NULL;
	sh->t.elem = NULL;
	sh->t.is_file = NULL;
	sh->t.before = NULL;
	sh->t.word = NULL;
	sh->t.nb_word = 0;
	sh->t.nb_line = 0;
	sh->t.nb_char = 0;
	ft_get_cols(&sh->ws);
	sh->prompt_len = display_prompt(*prompt);
	return (0);
}

int				get_term_raw_mode(int mode)
{
	t_termios	term;

	ft_memset(&term, 0, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	if (mode)
	{
		term.c_lflag &= ~(ECHO | ICANON | ISIG);
		term.c_oflag &= ~(OPOST);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
	}
	else
	{
		term.c_lflag |= (ECHO | ICANON | ISIG);
		term.c_oflag |= (OPOST);
	}
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	mode ? TERMCAP("ns") : 0;
	return (1);
}

void			ft_read_raw_mode(void)
{
	t_termios	term;

	ft_bzero(&term, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHO | ICANON | ISIG);
	term.c_oflag &= ~(OPOST);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}
