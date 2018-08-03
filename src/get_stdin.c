/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_stdin.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/12 00:01:33 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/02 23:43:08 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

int		term_reinit(struct termios *raw_mode)
{
	static struct termios term_default;
	static int state = 0;

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

int		get_keyboard_key(int *ret, t_editor *ed)
{
	ioctl(0, TIOCGWINSZ, &sz);
	if (CTRL_D)
		*ret = 0;
	else if (CTRL_C)
		end_of_text(ed);
	else if (!ft_strcmp(SHIFT_UP, ed->key) || !ft_strcmp(SHIFT_DOWN, ed->key))
		!ft_strcmp(SHIFT_UP, ed->key) ? move_cursor_up(ed) : move_cursor_down(ed);
	else if (HOME_KEY || END_KEY || CTRL_A || CTRL_E)
		HOME_KEY || CTRL_A ? go_to_begin_of_line(ed) : go_to_end_of_line(ed);
	else if (BACKSPACE && ed->line && ed->cursor_str_pos)
		return (backspace(ed));
	else if (LEFT_KEY || RIGHT_KEY)
		LEFT_KEY ? move_cursor_left(ed) : move_cursor_right(ed);
	else if (CTRL_L)
		return (clear_window(ed));
	else if ((!ft_strcmp(SHIFT_RIGHT, ed->key) || !ft_strcmp(SHIFT_LEFT, ed->key)) && ed->line)
		!ft_strcmp(SHIFT_LEFT, ed->key) ? move_word_left(ed) : move_word_right(ed);
	else if (ed->cursor_str_pos == ft_strlen(ed->line) && ft_strlen(ed->key) == 1 && ft_isprint(ed->key[0]))
		return (add_char_to_line(ed->key[0], ed));
	else if (ed->cursor_str_pos != ft_strlen(ed->line) && ft_strlen(ed->key) == 1 && ft_isprint(ed->key[0]))
		return (add_char_into_line(ed->key[0], ed));
	else if (CTRL_K && ft_strlen(ed->line + ed->cursor_str_pos))
		delete_from_cursor_to_end(ed);
	else if (CTRL_P)
		paste_clipboard(ed);
	else if (TAB_KEY)
		tabulator(ed);
	else if (UP_KEY || DOWN_KEY)
		historic(ed);
	return (0);
}

int		line_editor_init(char **line, e_prompt prompt, t_editor **ed)
{
//	ioctl(0, TIOCGWINSZ, &sz);
	if (!(*ed = (t_editor*)malloc(sizeof(t_editor))))
		return (0);
	(*ed)->clipboard = NULL;
//	(*ed)->ws_row = sz.ws_row;
//	(*ed)->ws_col = sz.ws_col;
	(*ed)->cursor_str_pos = 0;
	(*ed)->first_row = get_cursor_position(1);
	(*ed)->last_row = (*ed)->first_row;
	(*ed)->line = NULL;
	*line = prompt != PROMPT && prompt != E_PIPE? ft_strjoin_free(*line, "\n") : *line;
	(*ed)->prompt = prompt;
	return (1);
}

void	save_ed(t_editor **ed, int mode)
{
	static t_editor *save;

	if (!mode)
		save = *ed;
	else
		*ed = save;
}

void	check_if_hist_file(t_hist **hist)
{
	int fd;

	(void)hist;
	if (!(fd = open("./101sh_history", O_RDONLY | O_CREAT, 00600)))
		return ;
//	else
//	{

//	}
}

void	save_hist(t_hist	**hist, int mode)
{
	static t_hist *save;
	static int fill;

	if (!fill)
	{
		check_if_hist_file(hist);
		fill = 1;
	}
	if (!mode)
		save = *hist;
	else
		*hist = save;
}

int		check_quote(char *line)
{
	(void)line;
	return (-1);
}

int		get_stdin(char **line, e_prompt prompt)
{
	int ret;
	t_editor *ed;
	t_hist *hist;

	hist = NULL;
	get_term_raw_mode(1);
//	save_hist(&hist, 1);
	line_editor_init(line, prompt, &ed);
	display_prompt(prompt == 0 ? find_var_string(g_env, "HOME", 0) : NULL, ed->prompt);
	ed->prompt_size = get_cursor_position(0);
//	printf("test: %zu\n", ed->prompt_size);
	signal(SIGWINCH, myhandler_winsize_change);
	while ((ret = read(STDIN_FILENO, ed->key, BUFF_SIZE)) > 0)
	{
		tputs(tgetstr("vi", NULL), 1, ft_putchar);
		ed->key[ret] = '\0';
		//printf("\ned->key[0]: %d, ed->key[1]: %d, ed->key[2]: %d, ed->key[3]: %d, ed->key[4]: %d ed->key[5]: %d\n", ed->key[0], ed->key[1], ed->key[2], ed->key[3], ed->key[4], ed->key[5]);
		if (get_keyboard_key(&ret, ed))
			ed->line = ft_strjoin_free(ed->line, ed->key);
		save_ed(&ed, 0);
		tputs(tgetstr("ve", NULL), 1, ft_putchar);
		if (ft_strchr(ed->key, '\n') || (!ret && !(ed->line) && prompt == 0))
			break ;
	}
	if ((ed->last_row - get_cursor_position(1)) != 0)
		tputs(tgoto(tgetstr("DO", NULL), 0,
		ed->last_row - get_cursor_position(1)), 1, ft_putchar);
	ft_putchar('\n');
	if (prompt != PROMPT && prompt != E_PIPE)
	{
		*line = ed->line == NULL ? *line : ft_strjoin_free(*line, ed->line);
		ft_strdel(&ed->line);
	}
	else
		*line = ed->line;
	if ((ed->line && prompt == PROMPT) || (ed->line && prompt != PROMPT && check_quote(*line)))
			fill_hist_list(hist, ed->line);
	//*line = prompt != PROMPT ? ft_strjoin_free(*line, ed->line) : ed->line;
	free(ed);
	get_term_raw_mode(0);
	return (ret);
}
