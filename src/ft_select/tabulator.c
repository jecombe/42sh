/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 04:29:30 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 17:44:22 by gmadec      ###    #+. /#+    ###.fr     */
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
			!line)
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
//					//printf("WORD == %s\n", (*ed)->t.word);
//					//sleep(2);
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
		while ((*ed)->t.cmd[i] && (size_t)*end_word < (*ed)->cursor_str_pos)
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
	//printf("000\n");
	if ((*ed)->cursor_str_pos != (size_t)end_word)
	{
	//printf("111\n");
	//sleep(2);
		(*ed)->cursor_str_pos = end_word;
		return (-1);
	}
	//printf("222\n");
//	//printf("CMD[%d] == %s\n", (*ed)->t.nb_char, (*ed)->t.cmd[(*ed)->t.nb_char]);
	//sleep(2);
	if ((*ed)->t.cmd)
	{
		if ((*ed)->t.nb_char == 0 && !ft_isblank((*ed)->t.cmd[0][0]))
			(*ed)->t.word = ft_strdup((*ed)->t.cmd[(*ed)->t.nb_char]);
		else if ((*ed)->t.cmd && !ft_isblank((*ed)->t.cmd[(*ed)->t.nb_char - 1][0]))
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
	//printf("WORD == %s\n", (*ed)->t.word);
	//sleep(2);
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
	int	nb_line;

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
	//printf("CURSOR\n");
	//sleep(2);
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
	//printf("000\n");
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
	//printf("000\n");
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
//		//printf("KEY == %s\n", (*ed)->key);
		(*ed)->key[0] = 0;
		(*ed)->key[1] = 0;
//		//sleep(2);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		ft_free_t_tab(&(*ed)->t);
		ft_free_t_select(&(*ed)->sel);
		(*ed)->tabu = -1;
	}
	//printf("123\n");
	//sleep(2);
	version != 0 ? place_cursor_after(*ed) : 0;
	//printf("456\n");
	//sleep(2);
	return (0);
}
