/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   historic.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 10:01:52 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/17 11:25:01 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void	print_str(t_editor **ed)
{
	int			loop;

	loop = 0;
	if ((*ed)->line)
	{
		(*ed)->cursor_str_pos = ft_strlen((*ed)->line);
		while ((*ed)->line[loop])
			add_char_to_line((*ed)->line[loop++], *ed);
	}
}

static int	down_key(t_editor **ed)
{
	if ((*ed)->hist >= 0)
	{
		(*ed)->hist--;
		if ((*ed)->hist == -1)
		{
			ft_strdel(&(*ed)->line);
			if ((*ed)->tmp_line)
			{
				go_to_begin_of_line(*ed);
				delete_from_cursor_to_end(*ed);
				ft_strdel(&(*ed)->line);
				(*ed)->line = ft_strdup((*ed)->tmp_line);
				ft_strdel(&(*ed)->tmp_line);
				print_str(ed);
				(*ed)->cursor_str_pos = ft_strlen((*ed)->line);
			}
			(*ed)->hist = -2;
			return (0);
		}
	}
	else
		return (0);
	return (1);
}

int		term_historic(t_editor **ed)
{
	if (UP_KEY)
	{
		if ((*ed)->hist == -2)
		{
			(*ed)->tmp_line = ft_strdup((*ed)->line);
			(*ed)->hist = 0;
		}
	}
	else if (DOWN_KEY)
		if (!down_key(ed))
			return (0);
	go_to_begin_of_line(*ed);
	delete_from_cursor_to_end(*ed);
	history_get(ed);
	print_str(ed);
	(*ed)->cursor_str_pos = ft_strlen((*ed)->line);
	return (0);
}
