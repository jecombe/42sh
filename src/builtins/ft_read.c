/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_read.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2060/00/00 00:00:00 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/07 15:06:56 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void		ft_read_input(t_read *rd)
{
	char	key[4];
	time_t	start;

	start = time(NULL);
	rd->interactive ? DO_NOTHING : get_term_raw_mode(1);
	ft_bzero(key, sizeof(key));
	ft_putstr(rd->prompt);
	while (read(rd->fd, key, 1) != -1)
	{
		if ((key[0] == rd->delimiter) ||
			(rd->secs && (time(NULL) - start >= rd->secs)) ||
			(rd->limit && rd->line && ft_strlen(rd->line) >= (size_t)rd->limit))
		{
			get_term_raw_mode(0);
			return ;
		}
		else if (rd->line)
			ft_miniconcat(&rd->line, key);
		else
			rd->line = ft_strdup(key);
		if (!rd->hide)
			write(STDOUT_FILENO, key, sizeof(key));
		ft_bzero(key, sizeof(key));
	}
	rd->interactive ? DO_NOTHING : get_term_raw_mode(0);
}

int			ft_read_options_long(t_read *rd, char letter, char *arg)
{
	if (!arg || !arg[0])
		return (0);
	if (letter == 'u')
		rd->fd = ft_atoi(arg);
	else if (letter == 't')
		rd->secs = ft_atoi(arg);
	else if (letter == 'p')
		rd->prompt = arg;
	else if (letter == 'a')
	{
		rd->split = 1;
		if (rd->vars[0])
			free(rd->vars[0]);
		rd->vars[0] = ft_strdup(arg);
	}
	else if (letter == 'n')
		rd->limit = ft_atoi(arg);
	else if (letter == 'd')
		rd->delimiter = arg[0];
	return (1);
}

void		ft_read_parse_vars(t_read *rd, char **cmd)
{
	int i;

	if (rd->split)
		return ;
	i = -1;
	while (cmd[++i])
	{
		ft_strdel(&rd->vars[i]);
		rd->vars[i] = ft_strdup(cmd[i]);
	}
}

int			ft_read_options(t_read *rd, char **cmd, int i, int j)
{
	while (cmd[i] && cmd[++i] && cmd[i][j] == '-')
	{
		while (cmd[i][++j])
		{
			if (cmd[i][j] == 'e')
				rd->interactive = 1;
			else if (cmd[i][j] == 'r')
				rd->backs = 1;
			else if (cmd[i][j] == 's')
				rd->hide = 1;
			else if (ft_strchr("utpand", cmd[i][j]) && !cmd[i][j + 1])
			{
				if (!ft_read_options_long(rd, cmd[i][j], cmd[i + 1]))
					return (0);
				i++;
				break ;
			}
			else
				return (0);
		}
		j = 0;
	}
	ft_read_parse_vars(rd, cmd + i);
	return (1);
}

void		ft_read(char **cmd)
{
	t_read	rd;

	ft_init_read(&rd);
	if (!ft_read_options(&rd, cmd, 0, 0))
	{
		ft_putstr("read: usage: read [-ers] [-u fd] [-t timeout] [-p prompt] "
				"[-a array] [-n nchars] [-d delim] [name ...]\n");
		return ;
	}
	ft_read_input(&rd);
	if (!rd.line)
		return ;
	if (rd.split)
		ft_split_to_array(&rd);
	if (!rd.backs)
		ft_read_str_escape(&rd.line);
	ft_read_add_to_set(&rd);
	ft_putchar('\n');
}
