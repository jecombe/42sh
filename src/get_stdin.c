/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_stdin.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/12 00:01:33 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/17 22:38:29 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "shell.h"

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
		raw_mode.c_lflag &= ~(ECHO | ICANON);
		raw_mode.c_lflag |= (ISIG);
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

char	*cursor_position_escape_sequence(int row, int col)
{
	char *h_pos;
	char *v_pos;
	char *cursor_pos;

	v_pos = ft_itoa(get_cursor_position(1) - row);
	h_pos = ft_itoa(get_cursor_position(0) - col);
	cursor_pos = ft_strnew(6 + ft_strlen(v_pos) + ft_strlen(h_pos));
	ft_strcpy(cursor_pos, "\E[");
	ft_strcat(cursor_pos, v_pos);
	ft_strcat(cursor_pos, ";");
	ft_strcat(cursor_pos, h_pos);
	ft_strcat(cursor_pos, "H");
	ft_strdel(&h_pos);
	ft_strdel(&v_pos);
	return (cursor_pos);
}

void	reset_cursor_position_escape_sequence(char *cursor_positon)
{
	if (cursor_positon)
	{
		ft_putstr(cursor_positon);
		ft_strdel(&cursor_positon);
	}
}

int		backspace()
{
	char tmp[ft_strlen(g_save_line)];
	char *cursor_reset;

	ioctl(0, TIOCGWINSZ, &sz);
	bzero(tmp, sizeof(tmp));
	g_cursor_str_pos--;
	if (g_cursor_col_pos == 1)
	{
		tputs(tgoto(tgetstr("sr", NULL), 1, 1), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, sz.ws_col - 1), 1, ft_putchar);
	}
	else
		tputs(tgetstr("le", NULL), 1, ft_putchar);
	ft_strncpy(tmp, g_save_line, g_cursor_str_pos);
	ft_strcat(tmp, g_save_line + (g_cursor_str_pos + 1));
	ft_strdel(&g_save_line);
	g_save_line = ft_strdup(tmp);
	cursor_reset = cursor_position_escape_sequence(0, 0);
	ft_putstr("\E[0J");
	ft_putstr(g_save_line + g_cursor_str_pos);
	ft_putstr(cursor_reset);
	free(cursor_reset);
	if (!((ft_strlen(g_save_line) + g_prompt_size) % sz.ws_col))
		g_row_number--;
	if (!ft_strlen(g_save_line))
		ft_strdel(&g_save_line);
	return (0);
}

int		clear_window(t_shell *sh)
{
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	display_prompt(sh->pwd, g_save_home, sh->err, cut_pwd_dir(sh->pwd));
	if (g_save_line)
		ft_putstr(g_save_line);
	g_cursor_row_number = get_cursor_position(1);
	g_row_number = g_cursor_row_number;
	g_home_position = g_cursor_row_number;
	return (0);
}

int		move_cursor_horizontaly(int key)
{
	char *capability;

	ioctl(0, TIOCGWINSZ, &sz);
	capability = key == 68 ? "le" : "nd";
	capability = tgetstr(capability, NULL);
	if ((g_cursor_str_pos > 0 && key == 68) ||
			((g_cursor_str_pos < ft_strlen(g_save_line)) && key == 67))
	{
		if (key == 68)
			g_cursor_str_pos--;
		else
			g_cursor_str_pos++;
		if (g_cursor_col_pos == 1 && g_cursor_str_pos && key == 68)
		{
			tputs(tgoto(tgetstr("sr", NULL), 1, 1), 1, ft_putchar);
			tputs(tgoto(tgetstr("ch", NULL), 0, sz.ws_col - 1), 1, ft_putchar);
		}
		else if (g_cursor_col_pos == sz.ws_col && key == 67)
			tputs(tgetstr("sf", NULL), 1, ft_putchar);
		else
		tputs(capability, 1, ft_putchar);
	}
	return (0);
}

int		add_char_into_line(char *key)
{
	char tmp[ft_strlen(g_save_line) + 2];
	char *cursor_reset;

	g_cursor_str_pos++;
	bzero(tmp, sizeof(tmp));
	ioctl(0, TIOCGWINSZ, &sz);
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	if (!((ft_strlen(g_save_line) + g_prompt_size) % sz.ws_col) && g_row_number == sz.ws_row)
	{
		ft_putstr(key);
		cursor_reset = cursor_position_escape_sequence(1, 0);
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
		tputs(tgoto(tgetstr("DO", NULL), 0, (g_row_number - g_cursor_row_number)), 1, ft_putchar);
		tputs(tgetstr("sf", NULL), 1, ft_putchar);
		tputs(tgetstr("rc", NULL), 1, ft_putchar);
		ft_putstr(cursor_reset);
		free(cursor_reset);
		g_home_position--;
	}
	else if (!(g_cursor_col_pos % sz.ws_col))
	{
		ft_putstr(key);
		tputs(tgetstr("do", NULL), 1, ft_putchar);
	}
	else if (!((ft_strlen(g_save_line) + g_prompt_size) % sz.ws_col))
	{
		ft_putstr(key);
		g_row_number++;
	}
	else
		ft_putstr(key);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	ft_strncpy(tmp, g_save_line, g_cursor_str_pos);
	tmp[g_cursor_str_pos - 1] = key[0];
	ft_strcat(tmp, g_save_line + g_cursor_str_pos - 1);
	ft_strdel(&g_save_line);
	g_save_line = ft_strdup(tmp);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	ft_putstr(g_save_line + g_cursor_str_pos);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	return (0);
}

int		add_char_to_line(char *key)
{
	ioctl(0, TIOCGWINSZ, &sz);
	g_cursor_str_pos++;
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	if (g_cursor_col_pos  == sz.ws_col && g_cursor_row_number != sz.ws_row)
	{
		ft_putstr(key);
		tputs(tgetstr("do", NULL), 1, ft_putchar);
		g_row_number++;
	}
	else if (g_cursor_col_pos  == sz.ws_col && g_cursor_row_number == sz.ws_row)
	{
		ft_putstr(key);
		tputs(tgetstr("sf", NULL), 1, ft_putchar);
		g_home_position--;
	}
	else
		ft_putstr(key);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	return (1);
}

void	go_to_home_end_of_line(char *key)
{
	ioctl(0, TIOCGWINSZ, &sz);
	if ((HOME_KEY && g_cursor_str_pos) || END_KEY)
	{
		tputs(tgoto(tgetstr("cv", NULL), 0, g_home_position - 1), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, g_prompt_size - 1), 1, ft_putchar);
		if (HOME_KEY)
			g_cursor_str_pos = 0;
		else
		{
			ft_putstr(g_save_line);
			g_cursor_str_pos = ft_strlen(g_save_line);
			if (!((ft_strlen(g_save_line) + g_prompt_size - 1) % sz.ws_col))
				tputs(tgetstr("do", NULL), 1, ft_putchar);
		}
	}
}

void	move_cursor_up()
{
	ioctl(0, TIOCGWINSZ, &sz);
	if (g_cursor_row_number != g_home_position)
	{
		if (g_cursor_row_number - 1 == g_home_position &&
		g_cursor_col_pos < g_prompt_size)
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, g_prompt_size - 1), 1,
			ft_putchar);
			g_cursor_str_pos = 0;
		}
		else
			g_cursor_str_pos = g_cursor_str_pos - (g_cursor_col_pos +
			(sz.ws_col - g_cursor_col_pos));
		tputs(tgetstr("up", NULL), 1, ft_putchar);
	}
}

void	move_cursor_down()
{
	ioctl(0, TIOCGWINSZ, &sz);
	if (g_cursor_row_number != g_row_number)
	{
		if (g_cursor_row_number + 1 == g_row_number && (ft_strlen(g_save_line +
		g_cursor_str_pos) - (sz.ws_col - g_cursor_col_pos) < g_cursor_col_pos))
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, (ft_strlen(g_save_line +
			g_cursor_str_pos) - (sz.ws_col - g_cursor_col_pos)) - 1), 1,
			ft_putchar);
			g_cursor_str_pos = ft_strlen(g_save_line);
		}
		else
			g_cursor_str_pos = g_cursor_str_pos + ((g_cursor_col_pos +
			(sz.ws_col - g_cursor_col_pos)));
			tputs(tgoto(tgetstr("cv", NULL), 0, g_cursor_row_number), 1,
			ft_putchar);
	}
}

void	move_word_left()
{
	size_t s_pos;
	char *cursor_reset;

	s_pos = g_cursor_str_pos;
	cursor_reset = cursor_position_escape_sequence(0, 0);
	while (g_cursor_str_pos)
	{
		if ((g_save_line[g_cursor_str_pos - 1] == ' ' || g_save_line
		[g_cursor_str_pos - 1] == '\t') && g_save_line[g_cursor_str_pos] >= 33
		&& g_save_line[g_cursor_str_pos] <= 126 && s_pos != g_cursor_str_pos)
			return ;
		if (get_cursor_position(0) == 1)
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar);
			tputs(tgoto(tgetstr("ch", NULL), 0, sz.ws_col), 1, ft_putchar);
		}
		else
			tputs(tgetstr("le", NULL), 1, ft_putchar);
		g_cursor_str_pos--;
	}
	if (g_save_line[0] == '\t' || g_save_line[0] == ' ')
	{
		g_cursor_str_pos = s_pos;
		reset_cursor_position_escape_sequence(cursor_reset);
	}
}

void	move_word_right()
{
	size_t s_pos;
	char *cursor_reset;

	s_pos = g_cursor_str_pos;
	cursor_reset = cursor_position_escape_sequence(0, 0);
	while (g_save_line[g_cursor_str_pos])
	{
		if ((g_save_line[g_cursor_str_pos - 1] == ' ' || g_save_line
		[g_cursor_str_pos - 1] == '\t') && g_save_line[g_cursor_str_pos] >= 33
		&& g_save_line[g_cursor_str_pos] <= 126 && s_pos != g_cursor_str_pos)
			return ;
		if (get_cursor_position(0) == sz.ws_col)
		{
			tputs(tgetstr("do", NULL), 1, ft_putchar);
		}
		else
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
		g_cursor_str_pos++;
	}
	//if (g_save_line[g_cursor_str_pos] == '\t' || g_save_line[g_cursor_str_pos] == ' ')
	//{
		g_cursor_str_pos = s_pos;
		reset_cursor_position_escape_sequence(cursor_reset);
	//}
}

int		get_keyboard_key(char *key, int *ret, t_shell *sh)
{
	//printf("\n\n\n\n\n\n\n\n[NOK]\n\n\n\n\n\n\n\n\n");
	g_cursor_row_number = get_cursor_position(1);
	g_cursor_col_pos = get_cursor_position(0);
	ioctl(0, TIOCGWINSZ, &sz);
	if (CTRLD)
		*ret = 0;
	else if (UP_KEY || DOWN_KEY)
		return (0);
	else if (!ft_strcmp(SHIFT_UP, key) || !ft_strcmp(SHIFT_DOWN, key))
		!ft_strcmp(SHIFT_UP, key) ? move_cursor_up() : move_cursor_down();
	else if (HOME_KEY || END_KEY)
		go_to_home_end_of_line(key);
	else if (BACKSPACE && g_save_line && g_cursor_str_pos)
		return (backspace());
	else if (LEFT_KEY || RIGHT_KEY)
		return (move_cursor_horizontaly(key[2]));
	else if (CTRLL)
		return (clear_window(sh));
	else if (!ft_strcmp(SHIFT_RIGHT, key) || !ft_strcmp(SHIFT_LEFT, key))
		!ft_strcmp(SHIFT_LEFT, key) ? move_word_left() : move_word_right();
	else if (g_cursor_str_pos == ft_strlen(g_save_line) && ft_strlen(key) == 1 && ft_isprint(key[0]))
		return (add_char_to_line(key));
	else if (g_cursor_str_pos != ft_strlen(g_save_line) && ft_strlen(key) == 1 && ft_isprint(key[0]))
		return (add_char_into_line(key));
	return (0);
}

int		get_stdin(t_shell *sh, char **line)
{
	int ret;
	char buf[10];

	g_cursor_str_pos = 0;
	g_save_line = NULL;
	get_term_raw_mode(1);
	g_cursor_row_number = get_cursor_position(1);
	g_home_position = g_cursor_row_number;
	g_row_number = g_cursor_row_number;
	getcwd(sh->pwd, sizeof(sh->pwd));
	g_save_home = find_var_string(sh->my_env, "HOME", 0);
	display_prompt(sh->pwd, g_save_home, sh->err, cut_pwd_dir(sh->pwd));
	g_cursor_col_pos = get_cursor_position(0);
	signal(SIGWINCH, myhandler_winsize_change);
	while ((ret = read(STDIN_FILENO, buf, BUFF_SIZE)) > 0)
	{
		tputs(tgetstr("vi", NULL), 1, ft_putchar);
		buf[ret] = '\0';
		//printf("%zu\n", ft_strlen(buf));
	//	printf("\nbuf[0]: %d, buf[1]: %d, buf[2]: %d, buf[3]: %d, buf[4]: %d buf[5]: %d\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
		if (get_keyboard_key(buf, &ret, sh))
			g_save_line = ft_strjoin_free(g_save_line, buf);
		tputs(tgetstr("ve", NULL), 1, ft_putchar);
		if (ft_strchr(buf, '\n') || (!ret && !g_save_line))
			break ;
	}
	get_term_raw_mode(0);
	ft_strdel(&g_save_home);
	*line = g_save_line;
	if ((g_row_number - g_cursor_row_number) != 0)
		tputs(tgoto(tgetstr("DO", NULL), 0, g_row_number - g_cursor_row_number), 1, ft_putchar);
	ft_putchar('\n');
	printf("line:     [%s]\n", *line);
	return (ret);
}
