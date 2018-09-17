/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 10:16:39 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 03:09:48 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		check_metacharacter_nb(char *file)
{
	int i;
	int meta_nb;

	i = -1;
	meta_nb = 0;
	while (file[++i])
		if (ft_strchr("<>?*[]'\";|$&^()#\\`~", file[i]))
			meta_nb++;
	return (meta_nb);
}

char	*check_metacharacter(char **file)
{
	int		i;
	int		j;
	int		meta_nb;
	char	*tmp;

	i = -1;
	j = 0;
	meta_nb = check_metacharacter_nb(*file);
	tmp = meta_nb ? ft_strnew(meta_nb + ft_strlen(*file)) : NULL;
	if (meta_nb)
	{
		while ((*file)[++i])
		{
			if (ft_strchr("<>?*[]'\";|$&^()#\\`~", (*file)[i]) != NULL)
				tmp[j++] = '\\';
			tmp[j++] = (*file)[i];
		}
		ft_strdel(file);
	}
	return (tmp ? tmp : *file);
}

char	*add_slash_to_dir(int file_type, char *file, char *path)
{
	char	*tmp;
	DIR		*dir;
	char full_path[4096];

	dir = NULL;
	ft_bzero(full_path, 4096);
	if (file_type == 10)
	{
		if (!path)
			getcwd(full_path, 4096);
		else
			ft_strcat(full_path, path);
		if (full_path[ft_strlen(full_path) - 1] != '/')
			ft_strcat(full_path, "/");
		ft_strcat(full_path, file);
	}
	tmp = ft_strnew(ft_strlen(file) + 1);
	ft_strcpy(tmp, file);
	if (file_type == 4 || (file_type == 10 && (dir = opendir(full_path))))
		tmp[ft_strlen(file)] = '/';
	if (dir)
		closedir(dir);
	ft_strdel(&file);
	return (tmp);
}



int		tabulator_mode(t_editor *ed, size_t *path_begin)
{
	while (*path_begin)
	{
		if (ed->line[*path_begin - 1] == ' ' && (!ed->line[*path_begin]
		|| ft_strchr("&|;", ed->line[*path_begin])))
			return (2);
		if (ed->line[*path_begin - 1] == ' ' && ed->line[*path_begin])
			return (3);
		if (ft_strchr("&|;", ed->line[*path_begin - 1]) && (ed->line[*path_begin] == ' '
		|| ed->line[*path_begin] == '\0'))
			return (4);
		(*path_begin)--;
	}
	if (!(*path_begin) && ed->line)
		return (1);
	return (0);
}

char	*recup_bin(int mode, char **paths, char *bin_name, int *nb_line)
{
	(void)mode, (void)bin_name;
	int			i;
	int			node_nb;
	char		**bin;
	DIR			*dir;
	t_dirent	*rep;

	bin = NULL;
	i = -1;
	node_nb = 0;
	while (paths[++i])
		if ((dir = opendir(paths[i])))
		{
			while ((rep = readdir(dir)))
				if ((!mode && ft_strcmp(".", rep->d_name) && ft_strcmp("..", rep->d_name))
				|| (mode == 1 && !ft_strncmp(bin_name, rep->d_name, ft_strlen(bin_name))))
				{
					ft_malloc_cmd(&bin, rep->d_name);
					node_nb++;
				}
			closedir(dir);
		}
	if (node_nb == 1)
		return (bin[0]);
	else if (node_nb > 1)
		return (ft_select(bin, nb_line));
	else
		return (NULL);
}

void	search_bin(t_editor *ed, char *bin, int *nb_line)
{
	(void)ed;
	char *env_path;
	char **bin_path;

	env_path = NULL;
	bin_path = NULL;
	if (!bin)
	{
		if ((env_path = find_env_var(g_env, "PATH", 0)))
				if ((bin_path = ft_strsplit(env_path, ':')))
					recup_bin(0, bin_path, NULL, nb_line);
	}
	else
		if ((env_path = find_env_var(g_env, "PATH", 0)))
			if ((bin_path = ft_strsplit(env_path, ':')))
				recup_bin(1, bin_path, bin, nb_line);
}

char	*search_data(t_editor *ed, int path_begin)
{
	int path_end;
	char *path;

	path_end = path_begin - 1;
	path = NULL;
	while (ed->line[++path_end])
		if (ed->line[path_end] == ' ' || ft_strchr("&|<>;", ed->line[path_end]))
		{
			path = ft_strsub(ed->line, path_begin, path_end - path_begin);
			break ;
		}
	if (!path)
		path = ft_strdup(ed->line + path_begin);
	return (path);
}



char	**recup_files(int mode, DIR *dir, char *path, char *file)
{
	char		**files;
	t_dirent	*rep;
	char		*d_name;

	files = NULL;
	d_name = NULL;
	while ((rep = readdir(dir)))
	{
		if ((!mode && rep->d_name[0] != '.') || (mode == 1 &&
		!ft_strncmp(rep->d_name, file, ft_strlen(file))))
		{
			d_name = ft_strdup(rep->d_name);
			d_name = check_metacharacter(&d_name);
			if (rep->d_type == 4 || rep->d_type == 10)
				d_name = add_slash_to_dir(rep->d_type, d_name, path);
			ft_malloc_cmd(&files, d_name);
			ft_strdel(&d_name);
		}
	}
	if (dir)
		closedir(dir);
	return (files);
}

void	new_line(t_editor *ed, size_t path_begin, char *path, char *file)
{
	char tmp[ft_strlen(ed->line + path_begin) + ft_strlen(file)];
	size_t path_end;
	size_t new_cursor_pos;

	ft_bzero(tmp, ft_strlen(ed->line + path_begin) + ft_strlen(file));
	path_end = path_begin;
	while (ed->line[path_end] && ed->line[path_end] != ' ')
		path_end++;
	ft_strncpy(tmp, ed->line, path_begin);
	ft_strcat(tmp, path);
	ft_strcat(tmp, file);
	if (ed->line[path_end])
		ft_strcat(tmp, ed->line + path_end);
	new_cursor_pos = ft_strlen(ed->line + path_end) + 1;
	ft_strdel(&ed->line);
	ed->line = ft_strdup(tmp);
	while (ed->cursor_str_pos)
		move_cursor_left(ed);
	ft_putstr(ed->line);
	ed->cursor_str_pos = ft_strlen(ed->line);
	while (--new_cursor_pos)
		move_cursor_left(ed);
}

DIR		*check_if_there_is_a_slash_at_end(DIR *dir, char *path, t_editor *ed, size_t path_begin)
{
	(void)ed;
	if (path[ft_strlen(path) - 1] != '/')
	{
		path = add_slash_to_dir(10, (path), ".");
		new_line(ed, path_begin, path, "");
		closedir(dir);
		return (NULL);
	}
	return (dir);
}

DIR		*check_if_data_is_dir(char **path, char **arg, t_editor *ed, size_t path_begin)
{
	char	tmp[ft_strlen((*path))];
	DIR		*dir;
	int path_end;

	dir = NULL;
	path_end = ft_strlen((*path));
	if ((dir = opendir((*path))))
		return (check_if_there_is_a_slash_at_end(dir, *path, ed, path_begin));
	else
		while (path_end >= 0)
		{
			ft_bzero(tmp, path_end + 1);
			ft_strncpy(tmp, (*path), path_end);
			if ((*path)[path_end - 1] == '/' && (dir = opendir(tmp)))
			{
				(*arg) = ft_strlen(*path) ? ft_strdup(*path + path_end) : NULL;
				ft_strdel(path);
				(*path) = ft_strdup(tmp);
				break ;
			}
			path_end--;
		}
	return (!dir ? opendir(".") : dir);
}

void	tab_mode_3(t_editor *ed, size_t path_begin, int *nb_line)
{
	char *path;
	char *arg;
	DIR *dir;
	char **files;

	dir = NULL;
	files = NULL;
	path = NULL;
	arg = NULL;
	if ((path = search_data(ed, path_begin)))
	{
		dir = check_if_data_is_dir(&path, &arg, ed, path_begin);
		if (dir)
		{
			files = recup_files(1, dir, path, arg);
			if (ft_tablen(files) == 1)
			{
				new_line(ed, path_begin, path, files[0]);
				ft_tabdel(&files);
			}
			else if (ft_tablen(files) > 1)
			{
				ft_putchar('\n');
				ft_select(files, nb_line);
			}
		}
	}
}

void	tab_mode_2(t_editor *ed, size_t path_begin)
{
	char	**files;
	DIR		*dir;

	(void)path_begin;
	(void)ed;
	files = NULL;
	if ((dir = opendir(".")))
			files = recup_files(0, dir, NULL, NULL);
	int i = 0;
	while (files[i])
		printf("%s\n", files[i++]);
}

void	tabulator(t_editor *ed)
{
	int		nb_line;
	size_t	path_begin;
	char	*arg;
	char	*path;
	int		mode;
	int		last_dir;

	last_dir = -2;
	path = NULL;
	arg = NULL;
	nb_line = 0;
	path_begin = ed->cursor_str_pos;
	mode = tabulator_mode(ed, &path_begin);
	if (!mode)
		search_bin(ed, NULL, &nb_line);
	else if (mode == 1)
	{
		if ((path = search_data(ed, path_begin)))
			search_bin(ed, path, &nb_line);
	}
	else if (mode == 2)
		tab_mode_2(ed, path_begin);
	else if (mode == 3)
		tab_mode_3(ed, path_begin, &nb_line);
	//else if (mode == 4)
}
