/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_stdin.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/12 00:01:33 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/16 21:17:23 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void		get_stdin_next(char **line, t_editor *ed, e_prompt *prompt)
{
	if ((ed->last_row - get_cursor_position(1)) != 0)
		tputs(tgoto(tgetstr("DO", NULL), 0,
		ed->last_row - get_cursor_position(1)), 1, ft_putchar);
	ft_putchar('\n');
	if (*prompt != PROMPT && *prompt != E_PIPE)
	{
		*line = ed->line == NULL ? *line : ft_strjoin_free(*line, ed->line);
	}
	else
		*line = ft_strdup(ed->line);
}

static int		get_keyboard_key_ctrl(t_editor **ed, char **line, e_prompt *p)
{
	if (CTRL_D && !(*ed)->line)
		(*ed)->ret = -2;
	else if (CTRL_C)
		end_of_text(*ed, p, line);
	else if (CTRL_L)
		clear_window(*ed, *p);
	else if (CTRL_K && (ft_strlen((*ed)->line) + (*ed)->cursor_str_pos))
		delete_from_cursor_to_end(*ed);
	else if (CTRL_P)
		paste_clipboard(*ed);
	return (EXIT_SUCCESS);
}

static int		get_keyboard_key_tab(t_editor **ed)
{
	if (!(TAB_KEY || UP_KEY || DOWN_KEY || LEFT_KEY || RIGHT_KEY || ENTER_KEY))
		tabulator(ed, 1);
	else
	{
		tabulator(ed, 0);
		ft_strdel(&((*ed)->line));
		(*ed)->tabu = -1;
	}
	return (EXIT_SUCCESS);
}

int				enough_space_on_screen(t_editor *ed)
{
	dprintf(2, "max_char: %zu\n", ed->ws_col * ed->ws_row);
	dprintf(2, "line_len: %zu\n", ed->first_char * ed->first_row);
	return (1);
}

static int		get_keyboard_key(t_editor **ed, e_prompt *prompt, char **line)
{
	if (!(UP_KEY || DOWN_KEY) && (*ed)->hist != -2)
	{
		ft_strdel(&(*ed)->tmp_line);
		(*ed)->hist = -2;
	}
	else if (!(TAB_KEY || UP_KEY || DOWN_KEY || RIGHT_KEY || LEFT_KEY || CTRL_D)
			&& (*ed)->tabu != -1)
	{
		tabulator(ed, 0);
		ft_strdel(&(*ed)->tmp_line);
		(*ed)->tabu = -1;
		(*ed)->last_row = get_cursor_position(1);
		(*ed)->cur_col = get_cursor_position(0);
		(*ed)->cur_row = get_cursor_position(1);
	}
	if ((TAB_KEY && *prompt == PROMPT) || ((UP_KEY || DOWN_KEY || LEFT_KEY ||
	RIGHT_KEY || ENTER_KEY) && (*ed)->tabu != -1))
		tabulator(ed, 1);
	else if (CTRL_D || CTRL_C || CTRL_L || CTRL_K || CTRL_P)
		get_keyboard_key_ctrl(ed, line, prompt);
	else if (UP_KEY || DOWN_KEY)
		term_historic(ed);
	else if (LEFT_KEY || RIGHT_KEY)
		LEFT_KEY ? move_cursor_left(*ed) : move_cursor_right(*ed);
	else if (SHIFT_UP || SHIFT_DOWN)
		SHIFT_UP ? move_cursor_up(*ed) : move_cursor_down(*ed);
	else if ((SHIFT_LEFT || SHIFT_RIGHT) && (*ed)->line)
		SHIFT_LEFT ? move_word_left(*ed) : move_word_right(*ed);
	else if (HOME_KEY || CTRL_A || END_KEY || CTRL_E)
		HOME_KEY || CTRL_A ? go_to_begin_of_line(*ed) : go_to_end_of_line(*ed);
	else if (ft_isprint((*ed)->key[0]) /*&& enough_space_on_screen(*ed)*/)
		return (print_key(ed));
	else if (BACKSPACE && (*ed)->line && (*ed)->cursor_str_pos)
		backspace(*ed);
	return (EXIT_SUCCESS);
}

int				get_stdin(char **line, e_prompt *prompt)
{
	t_editor	*ed;

	ed = NULL;
	get_term_raw_mode(1);
	display_prompt(*prompt);
	if ((ed = line_editor_init(line, *prompt)) == NULL)
		return (-2);
	term_size(ed);
	while (ed->ret != -1)
	{
		ft_bzero(ed->key, BUFF_SIZE);
		ed->ret = read(STDIN_FILENO, ed->key, BUFF_SIZE - 1);
		tputs(tgetstr("vi", NULL), 1, ft_putchar);
		if (term_size(ed) == EXIT_SUCCESS)
			window_resize(&ed, prompt);
		if (ed->ret && get_keyboard_key(&ed, prompt, line))
			ed->line = ft_strjoin_free(ed->line, ed->key);
		tputs(tgetstr("ve", NULL), 1, ft_putchar);
		if (ed->key[0] && ((ft_strchr(ed->key, '\n') ||
			(ed->ret == -2 && !ed->line) || (ed->ret == -3 && *prompt == E_HDOC))))
			break ;
	}
	get_stdin_next(line, ed, prompt);
	get_term_raw_mode(0);
	return (line_editor_delete(&ed));
}
