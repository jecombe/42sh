/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 04:29:30 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 00:36:00 by dzonda      ###    #+. /#+    ###.fr     */
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

	line = (*ed)->t.word;
	while ((t_dir = readdir(dir)))
	{
		tmp = NULL;
		tmp = ft_strdup(t_dir->d_name);
		echap_char(&tmp);
		len_file = (*ed)->t.is_file ? ft_strlen((*ed)->t.is_file) : 0;
		if ((line && 0 == ft_strncmp(line, tmp, ft_strlen(line))) ||
			!line)
		{
			if (version == 0)
				ft_add_to_str(&(*ed)->t.is_file, '1', len_file);
			else
				ft_add_to_str(&(*ed)->t.is_file, ft_stat(tmp, path), len_file);
//			printf("IS_FILE == %s\n\n", (*ed)->t.is_file);
//			sleep(1);
			ft_malloc_cmd(&(*ed)->t.elem, tmp);
		}
		ft_strdel(&tmp);
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
//					printf("WORD == %s\n", (*ed)->t.word);
//					sleep(2);
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
	int			ret;

	ret = 0;
	path = ft_search_path((*ed)->t.word);
//	printf("WORD == %s NB_WORD == %d\n", (*ed)->t.word, (*ed)->t.nb_word);
//	printf("PATH == %s\n", path);
//			sleep(2);
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
			if ((tmp && 0 == ft_strncmp(tmp, g_set[i], ft_strlen(tmp))) || !tmp)
			{
				tmp2 = ft_get_var(g_set[i]);
				tmp3 = ft_strjoin("$", tmp2);
				ft_malloc_cmd(&ret, tmp3);
				ft_strdel(&tmp2);
				ft_strdel(&tmp3);
			}
			i++;
		}
	}
	ft_strdel(&tmp);
	return (ret);
}

int		search_end_word(int index, char **tablo)
{
	int		i;
	int		count;

	(void)index;
	count = 0;
	i = 0;
	if (tablo)
	{
		while (tablo[i])
		{
			count += ft_strlen(tablo[i]);
			i++;
		}
	}
	return (count);
}

void	binorfile(t_editor **ed, int *end_word)
{
	int		i;

	i = 0;
	if ((*ed)->t.cmd)
		while ((*ed)->t.cmd[i] && *end_word < (int)(*ed)->cursor_str_pos)
		{
			*end_word += ft_strlen((*ed)->t.cmd[i]);
			if (ft_isseparator((*ed)->t.cmd[i][0]))
				(*ed)->t.nb_word = 0;
			else if (ft_isprint((*ed)->t.cmd[i][0]))
				(*ed)->t.nb_word++;
			i++;
		}
	(*ed)->t.nb_char = i;
}

int		lexer_tab(t_editor **ed)
{
	int		end_word;

	(*ed)->t.cmd = ft_tabsplit((*ed)->line, (*ed)->cursor_str_pos);
	end_word = 0;
	binorfile(ed, &end_word);
	if ((int)(*ed)->cursor_str_pos != end_word)
	{
		(*ed)->cursor_str_pos = end_word;
		return (-1);
	}
	if ((*ed)->t.cmd)
	{
		if ((*ed)->t.cmd && !ft_isblank((*ed)->t.cmd[(*ed)->t.nb_char - 1][0]))
			(*ed)->t.word = ft_strdup((*ed)->t.cmd[(*ed)->t.nb_char - 1]);
		else
		{
//			ft_malloc_cmd(&(*ed)->t.cmd, "");//A MODIFIER SELON INDEX
			ft_add_str_at(&(*ed)->t.cmd, " ", (*ed)->t.nb_char - 1);
			(*ed)->t.nb_char++;
			//VOIR SELON LE COMPORTEMENT
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
	int	cursor;
	int	to_jump;

	cursor = 0;
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
	int	nb_line;
	int	cursor;

	cursor = 0;
	line_max = ed->prompt_size;
	line_max += ed->line ? ft_strlen(ed->line) : 0;
	nb_line = line_max / ed->ws_col + 1;
	while (nb_line > 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		nb_line--;
	}
	display_prompt(find_env_var(g_env, "HOME", 0), 0);
	ft_putfreshstr(ed->line);
	while (line_max > (int)(ed->cursor_str_pos + ed->prompt_size))
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
			}
		}
	}
	else if ((*ed)->tabu >= 0 && version == 1)
	{
		if ((*ed)->t.elem && (*ed)->t.elem[1])
			ft_select(ed, 1);
	}
	else if (version == 2)
	{
		//refresh
	//	ft_select(ed, 2);
	}
	else if (version == 0)
	{
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		if ((*ed)->sel)
		{
			/*
			while ((*ed)->sel->nbl >= 0)
			{
				tputs(tgoto(tgetstr("do", NULL), 1, 1), 1, ft_putchar);
				(*ed)->sel->nbl--;
			}*/
		}
		ft_free_t_tab(&(*ed)->t);
		ft_free_t_select(&(*ed)->sel);
	}
	version != 0 ? place_cursor_after(*ed) : 0;
//	place_cursor_after(*ed);
	return (0);
}
