/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term_init.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/10 02:51:08 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 08:03:19 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

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
		raw_mode.c_cc[VMIN] = 0;
		raw_mode.c_cc[VTIME] = 1;
		tcsetattr(STDIN_FILENO, TCSANOW, &raw_mode);
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &raw_mode);
	return (0);
}

void	init_t_tab(t_editor **ed)
{
	(*ed)->t.cmd = NULL;
	(*ed)->t.elem = NULL;
	(*ed)->t.is_file = NULL;
	(*ed)->t.before = NULL;
	(*ed)->t.word = NULL;
	(*ed)->t.nb_word = 0;
	(*ed)->t.nb_line = 0;
	(*ed)->t.nb_char = 0;
}

int		line_editor_init(char **line, e_prompt prompt, t_editor **ed)
{
	if (!(*ed = (t_editor*)malloc(sizeof(t_editor))))
		return (0);
	(*ed)->clipboard = NULL;
	(*ed)->cursor_str_pos = 0;
	(*ed)->first_row = get_cursor_position(1);
	(*ed)->last_row = (*ed)->first_row;
	(*ed)->line = NULL;
	(*ed)->tmp_line = NULL;
	(*ed)->hist = -2;
	(*ed)->tabu = -1;
	(*ed)->sel = NULL;
	init_t_tab(ed);
	(*ed)->cur_pos = get_cursor_position(0);
	*line = prompt != PROMPT && prompt != E_PIPE ?
	ft_strjoin_free(*line, "\n") : NULL;
	return (1);
}
