/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heredoc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 18:43:44 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 17:53:57 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static void		ft_skip_n(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
}

/*static void			ft_tabdell(char *list[100])
{
	int i;

	i = 0;
	while (list[i])
	{
		ft_strdel(&list[i]);
		i++;
	}
}*/

void			ft_read_line(int fd, char *s)
{
	char		*line;
	char		*list[100];
	char		*listt;
	int ret;
	int			i;
	e_prompt	prompt;

	prompt = E_HDOC;
	ft_bzero(list, 100 * sizeof(*list));
	i = 0;
	while ((ret = get_stdin(&line, &prompt)) != -2)
	{
		listt = ft_strdup(line + 1);
		if (ft_strcmp(listt, s) == 0 || ret == -3)
			break ;
		else
		{
			list[i++] = ft_strdup(line);
			ft_strdel(&line);
		}
	}
	if (ret != -3)
	{
		i = -1;
		while (list[++i])
			ft_putstr_fd(list[i], fd);
	}
}

int				ft_redirect_heredoc(t_redirect *redirect)
{
	int fd[2];

	pipe(fd);
	ft_read_line(fd[1], redirect->file);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (EXIT_SUCCESS);
}
