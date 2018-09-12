
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
