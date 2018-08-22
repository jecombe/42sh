/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_stdin.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/12 00:01:33 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/22 21:47:44 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

void	get_keyboard_key_next(t_editor *ed, e_prompt *prompt)
{
	if (ed->cursor_str_pos != ft_strlen(ed->line) &&
	ft_strlen(ed->key) == 1 && ft_isprint(ed->key[0]))
		add_char_into_line(ed->key[0], ed);
	else if (CTRL_K && ft_strlen(ed->line + ed->cursor_str_pos))
		delete_from_cursor_to_end(ed);
	else if (CTRL_P)
		paste_clipboard(ed);
	else if (TAB_KEY && *prompt == PROMPT)
		tabulator(ed);
	else if (UP_KEY || DOWN_KEY)
		historic(ed);
}

int		get_keyboard_key(int *ret, t_editor *ed, e_prompt *prompt, char **line)
{
	ioctl(0, TIOCGWINSZ, &sz);
	if (CTRL_D)
		*ret = 0;
	else if (CTRL_C)
		end_of_text(ed, prompt, line);
	else if (!ft_strcmp(SHIFT_UP, ed->key) || !ft_strcmp(SHIFT_DOWN, ed->key))
		!ft_strcmp(SHIFT_UP, ed->key) ? move_cursor_up(ed) :
		move_cursor_down(ed);
	else if (HOME_KEY || END_KEY || CTRL_A || CTRL_E)
		HOME_KEY || CTRL_A ? go_to_begin_of_line(ed) : go_to_end_of_line(ed);
	else if (BACKSPACE && ed->line && ed->cursor_str_pos)
		return (backspace(ed));
	else if (LEFT_KEY || RIGHT_KEY)
		LEFT_KEY ? move_cursor_left(ed) : move_cursor_right(ed);
	else if (CTRL_L)
		return (clear_window(ed, *prompt));
	else if ((!ft_strcmp(SHIFT_RIGHT, ed->key) ||
	!ft_strcmp(SHIFT_LEFT, ed->key)) && ed->line)
		!ft_strcmp(SHIFT_LEFT, ed->key) ? move_word_left(ed) :
		move_word_right(ed);
	else if (ed->cursor_str_pos == ft_strlen(ed->line) &&
	ft_strlen(ed->key) == 1 && ft_isprint(ed->key[0]))
		return (add_char_to_line(ed->key[0], ed));
	get_keyboard_key_next(ed, prompt);
	return (0);
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
	*line = prompt != PROMPT && prompt != E_PIPE ?
	ft_strjoin_free(*line, "\n") : NULL;
	return (1);
}

void	get_stdin_next(char **line, t_editor *ed, e_prompt *prompt)
{
	if ((ed->last_row - get_cursor_position(1)) != 0)
		tputs(tgoto(tgetstr("DO", NULL), 0,
		ed->last_row - get_cursor_position(1)), 1, ft_putchar);
	ft_putchar('\n');
	if (*prompt != PROMPT && *prompt != E_PIPE)
	{
		*line = ed->line == NULL ? *line : ft_strjoin_free(*line, ed->line);
		ft_strdel(&ed->line);
	}
	else
		*line = ed->line;
	free(ed);
}

int		get_stdin(char **line, e_prompt *prompt)
{
	int			ret;
	t_editor	*ed;

	ed = NULL;
	get_term_raw_mode(1);
	line_editor_init(line, *prompt, &ed);
	display_prompt(prompt == 0 ?
	find_var_string(g_env, "HOME", 0) : NULL, *prompt);
	ed->prompt_size = get_cursor_position(0);
	signal(SIGWINCH, myhandler_winsize_change);
	while ((ret = read(STDIN_FILENO, ed->key, BUFF_SIZE)) > 0)
	{
		tputs(tgetstr("vi", NULL), 1, ft_putchar);
		ed->key[ret] = '\0';
		if (get_keyboard_key(&ret, ed, prompt, line))
			ed->line = ft_strjoin_free(ed->line, ed->key);
	//	save_ed(&ed, 0);
		tputs(tgetstr("ve", NULL), 1, ft_putchar);
		if (ft_strchr(ed->key, '\n') || (!ret && !(ed->line) && *prompt == 0))
			break ;
	}
	get_stdin_next(line, ed, prompt);
	get_term_raw_mode(0);
	return (ret);
}
