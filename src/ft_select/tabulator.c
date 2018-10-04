/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 04:29:30 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 04:19:05 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		echap_char(char **element)
{
	int		i;

	i = -1;
	while ((*element)[++i])
		if (ft_isechap((*element)[i]))
			ft_add_to_str(&*element, '\\', i++);
	return (0);
}

int		add_bin(t_editor **ed, DIR *dir, char *path, int version)
{
	struct dirent	*t_dir;
	char			*tmp;
	char			*line;
	int				len_file;
	char			*tmp2;

	(void)version;
	line = (*ed)->t.word;
	while ((t_dir = readdir(dir)))
	{
		tmp2 = ft_strdup(t_dir->d_name);
		echap_char(&tmp2);
		len_file = (*ed)->t.is_file ? ft_strlen((*ed)->t.is_file) : 0;
		tmp = ft_stat(tmp2, path) == '2' ?
			ft_strjoin(tmp2, "/") : ft_strdup(tmp2);
		if ((line && 0 == ft_strncmp(line, tmp, ft_strlen(line))) ||
			(!line && tmp[0] != '.'))
		{
			ft_add_to_str(&(*ed)->t.is_file, ft_stat(tmp2, path), len_file);
			ft_malloc_cmd(&(*ed)->t.elem, tmp);
		}
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	return (0);
}

int		search_bin(t_editor **ed)
{
	char		*tmp;
	char		**path;
	int			i;
	DIR			*dir;

	i = -1;
	if ((tmp = ft_getenv("PATH", g_env)))
	{
		if ((path = ft_strsplit(tmp, ':')))
		{
			while (path[++i])
				if ((dir = opendir(path[i])))
				{
					add_bin(ed, dir, path[i], 0);
					closedir(dir);
				}
			ft_strdel(&tmp);
			ft_tabdel(&path);
		}
	}
	return (0);
}

int		search_in_rep(t_editor **ed)
{
	char		*path;
	char		*tmp;
	DIR			*dir;

	path = ft_search_path((*ed)->t.word);
	if (ft_isdir(path) == 0)
	{
		ft_strdel(&path);
		return (0);
	}
	if ((dir = opendir(path)))
	{
		tmp = ft_strdup((*ed)->t.word);
		ft_cut_word_and_before(&(*ed)->t.word, tmp, &(*ed)->t.before);
		ft_strdel(&tmp);
		add_bin(ed, dir, path, 1);
		ft_strdel(&path);
		closedir(dir);
	}
	return (0);
}

char	**search_var(char *word)
{
	char	**ret;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		i;

	i = 0;
	ret = NULL;
	tmp = word[1] ? ft_strdup(word + 1) : NULL;
	if (g_set)
	{
		while (g_set[i])
		{
			if (!tmp || (tmp && 0 == ft_strncmp(tmp, g_set[i], ft_strlen(tmp))))
			{
				tmp2 = ft_get_var(g_set[i]);
				tmp3 = ft_strjoin("$", tmp2);
				ft_malloc_cmd(&ret, tmp3);
				ft_strdel(&tmp2);
				ft_strdel(&tmp3);
			}
			i++;
		}
		i = -1;
	}
	ft_strdel(&tmp);
	return (ret);
}

void	binorfile(t_editor **ed, size_t *end_word)
{
	int			i;
	t_tab_lex	t;
	int			cursor;

	i = 0;
	(*ed)->t.nb_word = 0;
	while ((*ed)->t.cmd[0][i])
	{
		cursor = -1;
		t.c = (*ed)->t.cmd[0][i];
		t.i = i;
		t.count = 0;
		if (issep((*ed)->t.cmd[0], i))
			(*ed)->t.nb_word = 0;
		else if (ft_isprint((*ed)->t.cmd[0][i]))
			(*ed)->t.nb_word++;
		i++;
	}
	(*ed)->t.nb_char = 1;
	*end_word = ft_strlen((*ed)->t.cmd[0]) + ft_strlen((*ed)->t.cmd[1]);
}

int		lexer_tab(t_editor **ed)
{
	size_t		end_word;

	if (((*ed)->t.cmd = ft_tabsplit(ed)))
	{
		binorfile(ed, &end_word);
		if ((*ed)->cursor_str_pos < end_word)
		{
			(*ed)->cursor_str_pos = end_word;
			return (-1);
		}
		else
		{
			if ((*ed)->t.cmd[1][0])
			(*ed)->t.word = ft_strdup((*ed)->t.cmd[1]);
			else
				(*ed)->t.word = NULL;
		}
		if ((*ed)->t.word && (*ed)->t.word[0] == '$')
			(*ed)->t.nb_word = -1;
	}
	return (1);
}

void	place_cursor_before(t_editor *ed)
{
	int line_max;
	int	nb_line;
	int	to_jump;

	line_max = ed->prompt_size;
	line_max += ed->line ? ft_strlen(ed->line) : 0;
	nb_line = line_max / ed->ws_col + 1;
	to_jump = (ed->cursor_str_pos + ed->prompt_size) / ed->ws_col;
	while (nb_line - to_jump > 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_putchar);
		nb_line--;
	}
	ft_putchar('\r');
}

void	place_cursor_after(t_editor *ed)
{
	int		line_max;
	int		nb_line;

	line_max = ed->prompt_size;
	line_max += ed->line ? ft_strlen(ed->line) : 0;
	nb_line = line_max / ed->ws_col + 1;
	while (nb_line > 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		nb_line--;
	}
//	printf("\n\nLINE == %s\n\n", ed->line);
//	sleep(2);
	display_prompt(0);
	ft_putfreshstr(ed->line);
//	sleep(2);
	while ((size_t)line_max > (ed->cursor_str_pos + ed->prompt_size))
	{
		if (get_cursor_position(0) == 1)
		{
			tputs(tgoto(tgetstr("le", NULL), 1, 1), 1, ft_putchar);
			tputs(tgoto(tgetstr("ch", NULL), 1, 1), 1, ft_putchar);
		}
		else
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		line_max--;
	}
}

void	ft_free_t_tab(t_tab *t)
{
	ft_tabdel(&(*t).cmd);
	ft_tabdel(&(*t).elem);
	ft_strdel(&(*t).is_file);
	ft_strdel(&(*t).before);
	ft_strdel(&(*t).word);
	(*t).nb_word = 0;
	(*t).nb_char = 0;
}

int		tabulator(t_editor **ed, int version)
{
	version != 0 ? place_cursor_before(*ed) : 0;
	if ((*ed)->tabu == -1 && version == 1)
	{
		if (lexer_tab(ed) != -1)
		{
			if ((*ed)->t.nb_word == 1 || (*ed)->t.nb_word == 0)
				search_bin(ed);
			else if ((*ed)->t.nb_word == -1)
				(*ed)->t.elem = search_var((*ed)->t.word);
			else
				search_in_rep(ed);
			if ((*ed)->t.elem && (*ed)->t.elem[1])
			{
				(*ed)->tabu = 0;
				ft_select(ed, 0);
			}
			else if ((*ed)->t.elem && (*ed)->t.elem[0])
			{
				(*ed)->sel = malloc(sizeof(t_select));
				(*ed)->sel->ret = ft_strdup((*ed)->t.elem[0]);
				replace_line_after_tab(ed);
				ft_free_t_tab(&(*ed)->t);
			}
		}
	}
	else if ((*ed)->tabu >= 0 && version == 1 && !ENTER_KEY)
	{
		if ((*ed)->t.elem && (*ed)->t.elem[1])
			ft_select(ed, 1);
	}
	else if (version == 2)
	{
		//refresh
	//	ft_select(ed, 2);
	}
	else if (version == 0 || (version == 1 && ENTER_KEY && (*ed)->tabu >= 0))
	{
		int i;

		if ((*ed)->line)
		{
			i = (*ed)->cursor_str_pos + (*ed)->prompt_size;
			while ((size_t)i < (*ed)->prompt_size + ft_strlen((*ed)->line))
			{
				move_right();
				i++;
			}
		}
		(*ed)->key[0] = 0;
		(*ed)->key[1] = 0;
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		if ((*ed)->line)
		{
			i = (*ed)->cursor_str_pos + (*ed)->prompt_size;
			while ((size_t)i < (*ed)->prompt_size + ft_strlen((*ed)->line))
			{
				move_left(*ed);
				i++;
			}
		}
		ft_free_t_tab(&(*ed)->t);
		ft_free_t_select(&(*ed)->sel);
		(*ed)->tabu = -1;
	}
	version != 0 ? place_cursor_after(*ed) : 0;
	return (0);
}
