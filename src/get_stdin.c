/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_stdin.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/12 00:01:33 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/30 04:23:43 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "stdin.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char *tmp;

	if (!s1)
		tmp = ft_strdup(s2);
	else
	{
		tmp = ft_strjoin(s1, s2);
		ft_strdel(&s1);
	}
	return (tmp);
}

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

int		get_keyboard_key(char *key, int *ret, char **line, t_editor *ed, t_shell *sh)
{
	ioctl(0, TIOCGWINSZ, &sz);
	if (CTRL_D)
		*ret = 0;
	else if (CTRL_C)
		end_of_text(line, ed);
	else if (UP_KEY || DOWN_KEY)
		return (0);
	else if (!ft_strcmp(SHIFT_UP, key) || !ft_strcmp(SHIFT_DOWN, key))
		!ft_strcmp(SHIFT_UP, key) ? move_cursor_up(ed) : move_cursor_down(*line, ed);
	else if (HOME_KEY || END_KEY)
		HOME_KEY ? go_to_begin_of_line(ed) : go_to_end_of_line(ed, *line);
	else if (BACKSPACE && line && ed->cursor_str_pos)
		return (backspace(ed, line));
	else if (LEFT_KEY || RIGHT_KEY)
		LEFT_KEY ? move_cursor_left(ed) : move_cursor_right(ed, *line);
	else if (CTRL_L)
		return (clear_window(sh, ed));
	else if ((!ft_strcmp(SHIFT_RIGHT, key) || !ft_strcmp(SHIFT_LEFT, key)) && line)
		!ft_strcmp(SHIFT_LEFT, key) ? move_word_left(*line, ed) : move_word_right(*line, ed);
	else if (ed->cursor_str_pos == ft_strlen(*line) && ft_strlen(key) == 1 && ft_isprint(key[0]))
		return (add_char_to_line(key[0], ed));
	else if (ed->cursor_str_pos != ft_strlen(*line) && ft_strlen(key) == 1 && ft_isprint(key[0]))
		return (add_char_into_line(key[0], line, ed));
	else if (CTRL_K && ft_strlen(*line + ed->cursor_str_pos))
		delete_from_cursor_to_end(line, ed);
	else if (CTRL_P)
		paste_clipboard(line, ed);
	return (0);
}

int		line_editor_init(t_editor **ed)
{
	if (!(*ed = (t_editor*)malloc(sizeof(t_editor))))
		return (0);
	(*ed)->cursor_str_pos = 0;
	(*ed)->first_row = get_cursor_position(1);
	(*ed)->last_row = (*ed)->first_row;
	return (1);
}

int		shell_init(t_shell **sh)
{
	if (!(*sh = (t_shell*)malloc(sizeof(t_shell))))
		return (0);
	(*sh)->err = 0;
	(*sh)->line = NULL;
	g_save_home = NULL;
	g_bin_exit = 0;
	getcwd((*sh)->last_path, sizeof((*sh)->last_path));
	return (1);
}

int		get_stdin(char **line, char **env, e_prompt prompt)
{
	int ret;
	char buf[10];
	t_editor *ed;
	t_shell *sh;

	shell_init(&sh);
	get_term_raw_mode(1);
	line_editor_init(&ed);
	g_save_home = find_var_string(env, "HOME", 0);
	ed->prompt_size = display_prompt(sh->pwd, g_save_home, sh->err, cut_pwd_dir(sh->pwd));
		//printf("prompt_size: %zu\n", ed->prompt_size);
	getcwd(sh->pwd, sizeof(sh->pwd));
	signal(SIGWINCH, myhandler_winsize_change);
	while ((ret = read(STDIN_FILENO, buf, BUFF_SIZE)) > 0)
	{
		tputs(tgetstr("vi", NULL), 1, ft_putchar);
		buf[ret] = '\0';
	//	printf("\nbuf[0]: %d, buf[1]: %d, buf[2]: %d, buf[3]: %d, buf[4]: %d buf[5]: %d\n, buf[6]: %d\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6]);
		if (get_keyboard_key(buf, &ret, line, ed, sh))
			*line = ft_strjoin_free(*line, buf);
		tputs(tgetstr("ve", NULL), 1, ft_putchar);
		if (ft_strchr(buf, '\n') || (!ret && !(*line)))
			break ;
	}
	if (g_save_home)
	ft_strdel(&g_save_home);
	if ((ed->last_row - get_cursor_position(1)) != 0)
		tputs(tgoto(tgetstr("DO", NULL), 0, ed->last_row - get_cursor_position(1)), 1, ft_putchar);
	get_term_raw_mode(0);
	ft_putchar('\n');
	printf("line:     [%s]\n", *line);
	return (ret);
}
