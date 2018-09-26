/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_select.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/26 11:58:36 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/26 12:28:57 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_select.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/02 20:48:47 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/26 11:52:57 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/ft_select.h"

static t_line	*ft_init_begin(t_line **line, char *av)
{
	t_line	*after;

	after = malloc(sizeof(t_line));
	(*line) = after;
	after->prev = NULL;
	after->next = NULL;
	after->x_char_pos = 0;
	after->ds = 0;
	after->x_param_pos = 0;
	after->y_pos = 0;
	after->elem = ft_strdup(av);
//	after->is_file = ft_is_file(av);
	return (after);
}

void			manage_init(t_editor **ed, int i, t_line *line)
{
	while ((*ed)->t.elem[++i])
	{
		if ((*ed)->sel->line)
			ft_first_sort(&(*ed)->sel->line, (*ed)->t.elem[i]);
		else
			ft_init_begin(&(*ed)->sel->line, (*ed)->t.elem[i]);
	}
	i = -1;
	line = (*ed)->sel->line;
	while (line)
	{
		if (++i > -1 && line->next)
			line->is_file = ft_is_file(line->elem, i);
		else
			line->is_file = ft_is_file(line->elem, i == 0 ? -2 : -1);
		line->cursor_inside = (*ed)->tabu ? 1 : 0;
		line = line->next;
	}
	(*ed)->sel->bp = ft_search_big_param((*ed)->sel->line);
	(*ed)->sel->pose_min = 0;
	(*ed)->sel->ds = NULL;
	(*ed)->sel->ret = NULL;
	ft_get_size_term(&(*ed)->sel->ws, &(*ed)->sel, 1);
	(*ed)->sel->pbl = ft_params_by_line((*ed)->sel);
	(*ed)->sel->nbl = ft_count_line((*ed)->sel);
	(*ed)->sel->nbp = ft_count_params((*ed)->sel->line);
}

char			*search_path(char *line)
{
	char		*pwd;
	char		*tmp;
	int			i;
	char		getpwd[4096];

	printf("LINE == %s\n", line);
	if (!line || !ft_strchr(line, '/'))
		pwd = ft_search_pwd(NULL);
	else if (ft_strchr(line, '/') && !(line[0] == '/'))
	{
		//COMPARER LE GETCPWD ET LA LINE
		ft_search_relative_path(line);
		printf("1PWD == %s\n", pwd);
	}
	else
	{
		pwd = ft_search_absolute_path(line);
		//GARGER JUSQU AU DERNIER '/'
	}
	return (pwd);
}

void			ft_init_select(t_editor **ed)
{
	int		i;
	t_line	*line;
	DIR		*dir;
	char	*pwd;
	char	**file;

	file = NULL;
	i = -1;
	line = NULL;
	(*ed)->sel = malloc(sizeof(t_select));
	(*ed)->sel->line = NULL;
	if ((*ed)->t.elem)
	{
		pwd = search_path((*ed)->t.cmd[(*ed)->t.nb_char - 1]);
		manage_init(ed, i, line);
	}
}
