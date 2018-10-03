/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   heredoc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/28 18:43:44 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 13:26:02 by jecombe     ###    #+. /#+    ###.fr     */
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

void			ft_tabdell(char *list[100])
{
	int i;

	i = 0;
	while (list[i])
	{
		ft_strdel(&list[i]);
		i++;
	}
}

void			ft_read_line(int fd, char *s)
{
	char		line[100];
	char		*list[100];
	int			i;
	e_prompt	prompt;

	prompt = E_HDOC;
	display_prompt(prompt);
	ft_bzero(line, 100);
	ft_bzero(list, 100 * sizeof(*list));
	i = 0;
	while (read(1, line, 4096) > 0)
	{
		ft_skip_n(line);
		if (ft_strcmp(line, s) == 0)
			break ;
		else
		{
			display_prompt(prompt);
			ft_strcat(line, "\n");
			list[i++] = ft_strdup(line);
		}
		ft_bzero(line, 100);
	}
	i = -1;
	while (list[++i])
		ft_putstr_fd(list[i], fd);
	ft_tabdell(list);
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
