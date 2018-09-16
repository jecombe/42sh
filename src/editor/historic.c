/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   historic.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 10:01:52 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/16 09:35:55 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int		historic(t_editor *ed, int serie)
{
	static int	 index = 0;

	go_to_begin_of_line(ed);
	delete_from_cursor_to_end(ed);
	if (UP_KEY)
		index = serie == -101 ? index + 1 : 0;
	else if (DOWN_KEY)
		index = serie == -101  && index > 0 ? index - 1 : 0;
	printf("0ED->LINE == %s\n", ed->line);
	printf("INDEX == %d\n", index);
	//	ed->line = ft_strdup("p");
	history_get(&(ed)->line, index);//500 == INDEX
	printf("1ED->LINE == %s\n", ed->line);
	if (ed->line)
	{
		ft_putstr(ed->line);
		ed->cursor_str_pos = ft_strlen(ed->line);
	}
	return (-42);
}
