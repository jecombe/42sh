/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heredoc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 18:43:44 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 08:05:21 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		ft_skip_n(char *line, char *s)
{
	char		*tmp;
	int			ok;

	ok = 0;
	tmp = ft_strdup(line);
	tmp[ft_strlen(tmp) - 1] = '\0';
	if (ft_strcmp(tmp, s) == 0)
		ok = 1;
	ft_strdel(&tmp);
	if (ok == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void			ft_read_line(int fd, char *s)
{
	char		*heredoc;
	char		*line;

	g_prompt = E_HDOC;
	heredoc = NULL;
	while ((line = ft_get_user_input(&g_prompt)))
	{
		if (ft_skip_n(line, s))
			break ;
		heredoc = ft_strjoin_free(heredoc, line);
		ft_strdel(&line);
	}
	ft_putstr_fd(heredoc, fd);
	ft_strdel(&heredoc);
	ft_strdel(&line);
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
