#include "heart.h"

static void		ft_skip_n(char *line)
{
	int i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
}
int	ft_read_line(char *s)
{
	char	line[100];
	char	*list[100];
	int		i;
	e_prompt	prompt;
	int file;

	prompt = E_HDOC;
	display_prompt(NULL, prompt);
	ft_bzero(line, 100);
	ft_bzero(list, 100 * sizeof(*list));
	i = 0;
	file = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (read(1, line, 4096) > 0)
	{
		ft_skip_n(line);
		if (ft_strcmp(line, s) == 0)
			break ;
		else
		{
			display_prompt(NULL, prompt);
			ft_strcat(line, "\n");
			list[i++] = ft_strdup(line);
		}
		ft_bzero(line, 100);
	}
	i = -1;
	while (list[++i])
		ft_putstr_fd(list[i], file);
	close(file);
	file = open("/tmp/.heredoc", O_RDONLY);
	return (file);
}

int				ft_redirect_heredoc(t_redirect *redirect, int buil)
{
	int fd_open;

	return ((fd_open = ft_read_line(redirect->file)));
}
