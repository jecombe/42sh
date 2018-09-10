/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor_position.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 04:13:30 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/09/09 23:53:20 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/stdin.h"

static int		get_row(char *str)
{
	int		i;
	char	tmp[ft_strlen(str) + 1];

	i = -1;
	while (str[++i] != ';')
		tmp[i] = str[i];
	tmp[i] = '\0';
	free(str);
	return (ft_atoi(tmp));
}

static int		get_col(char *str)
{
	int		i;
	char	tmp[ft_strlen(str) + 1];

	i = -1;
	while (str[++i])
		if (i && str[i - 1] == ';')
		{
			ft_strcpy(tmp, str + i);
			break ;
		}
	free(str);
	return (ft_atoi(tmp));
}

static int		cursor_position(int mode)
{
	char	buf[2];
	int		ret;
	char	*cursor_position;

	cursor_position = NULL;
	write(1, "\E[6n", 4);
	while ((ret = read(0, buf, 1)) > 0)
	{
		buf[ret] = '\0';
		if ((buf[0] >= '0' && buf[0] <= '9') || (buf[0] == ';'))
			cursor_position = ft_strjoin_free(cursor_position, buf);
		if (ft_strchr(buf, 'R'))
			break ;
	}
	return (mode ? get_row(cursor_position) : get_col(cursor_position));
}

size_t			get_cursor_position(int mode)
{
	size_t res;

	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	res = cursor_position(mode);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	return (res);
}
