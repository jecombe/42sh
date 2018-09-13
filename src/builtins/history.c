
#include "heart.h"

void					history_save(t_history **history)
{
	static t_history	*histsave = NULL;

	if (!(histsave))
		histsave = *history;
	else
		*history = histsave;
}

void			history_add(char *cmd)
{
	t_history	*history;

	history = NULL;
	history_save(&history);
	ft_malloc_cmd(&(history)->cmd, cmd);
}

void			history_get(char **line, int stat)
{
	static int	i = 0;
	t_history	*history;

	history = NULL;
	history_save(&history);
	if (stat == 0)
		if (history->cmd)
			while (history->cmd[i])
				i++;
	if (stat == -1)
		if (history->cmd)
			if ((i - 1) > -1)
			{
				ft_strdel(line);
				*line = ft_strdup(history->cmd[--i]);
			}
	if (stat == 1)
		if (history->cmd)
			if (i < ft_tablen(history->cmd))
			{
				ft_strdel(line);
				*line = ft_strdup(history->cmd[++i]);
			}
}
