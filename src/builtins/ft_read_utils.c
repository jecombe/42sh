/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_read.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gbarnay <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2060/00/00 00:00:00 by gbarnay      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 01:56:09 by gbarnay     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

/*
**void		ft_debug_rd(t_read *rd)
**{
**	printf("-------------\n");
**	printf("line:\t[%s]\n", rd->line);
**	printf("prompt:\t[%s]\n", rd->prompt);
**	printf("delim:\t[%c]\n", rd->delimiter);
**	printf("limit:\t[%d]\n", rd->limit);
**	printf("hide:\t[%d]\n", rd->hide);
**	printf("backs:\t[%d]\n", rd->backs);
**	printf("split:\t[%d]\n", rd->split);
**	for (int i = 0; rd->vars[i]; i++)
**		printf("var[%d]:\t[%s]\n", i, rd->vars[i]);
**	printf("fd:\t[%d]\n", rd->fd);
**	printf("secs:\t[%d]\n", rd->secs);
**	printf("inter:\t[%d]\n", rd->interactive);
**	printf("-------------\n");
**}
*/

void		ft_init_read(t_read *rd)
{
	rd->line = NULL;
	rd->prompt = NULL;
	rd->delimiter = '\n';
	rd->limit = 0;
	rd->hide = 0;
	rd->backs = 0;
	rd->split = 0;
	ft_bzero(rd->vars, sizeof(rd->vars));
	rd->fd = 0;
	rd->secs = 0;
	rd->interactive = 0;
}

void		ft_split_to_array(t_read *rd)
{
	char	**splitted;
	int		i;
	char	*tmp;

	splitted = ft_strsplit(rd->line, ' ');
	free(rd->line);
	rd->line = ft_strdup("(");
	i = -1;
	while (splitted[++i])
	{
		if (i > 0)
			ft_miniconcat(&rd->line, " ");
		ft_miniconcat(&rd->line, "[");
		tmp = ft_itoa(i);
		ft_miniconcat(&rd->line, tmp);
		free(tmp);
		ft_miniconcat(&rd->line, "]=\"");
		ft_miniconcat(&rd->line, splitted[i]);
		ft_miniconcat(&rd->line, "\"");
		free(splitted[i]);
	}
	ft_miniconcat(&rd->line, ")");
	free(splitted);
}

void		ft_read_str_escape(char **s)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = ft_memalloc(ft_strlen(*s) + 1);
	i = -1;
	j = -1;
	while ((*s)[++i])
	{
		if ((*s)[i] == '\n' || (*s)[i] == '\r' || (*s)[i] == '\t' ||
				(*s)[i] == '\f' || (*s)[i] == '\v' || (*s)[i] == '\b')
		{
			tmp[++j] = ' ';
		}
		else
		{
			if ((*s)[i] == '\\' && ft_strncmp(*s + i, "\\\\", 2))
				i++;
			tmp[++j] = (*s)[i];
		}
	}
	free(*s);
	*s = ft_strdup(tmp);
	free(tmp);
}

void		ft_read_add_to_set(t_read *rd)
{
	int		i;
	char	**splitted;

	if (!rd->vars[0])
		add_to_set("REPLY", rd->line);
	else if (!rd->split)
	{
		splitted = ft_strsplit(rd->line, ' ');
		i = 0;
		while (rd->vars[i] && splitted[i])
		{
			add_to_set(rd->vars[i], splitted[i]);
			free(rd->vars[i]);
			free(splitted[i++]);
		}
		free(splitted);
	}
	else
	{
		add_to_set(rd->vars[0], rd->line);
		free(rd->vars[0]);
		free(rd->line);
	}
}
