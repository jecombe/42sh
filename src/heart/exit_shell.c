
#include "heart.h"

int			history_save_file_open(const char *bin)
{
	int		fd;
	char	*buf;
	char	*file;

	fd = -1;
	buf = NULL;
	file = NULL;
	if (!(buf = search_path_of_101sh((char *)bin)))
		return (-1);
	if (!(file = ft_strjoin(buf, "/.101sh_history")))
		return (-1);
	ft_strdel(&buf);
	fd = open(file, O_RDWR | O_APPEND);
	ft_strdel(&file);
	return (fd);
}

void			history_save_file(const char *bin)
{
	t_history	*history;
	int			i;
	int			fd;
	char		buf[BUFF_SIZE];

	history = NULL;
	i = -1;
	fd = -1;
	ft_bzero(buf, BUFF_SIZE);
	history_save(&history);
	if ((fd = history_save_file_open(bin)) == -1)
		return ;
	if (history->cmd)
		while (history->cmd[++i])
		{
			ft_strcpy(buf, "[");
			ft_strcat(buf, history->cmd[i]);
			ft_strcat(buf, "]");
			ft_putendl_fd(buf, fd);
			ft_strclr(buf);
		}
	close(fd);
	ft_tabdel(&(history)->cmd);
	free(history);
}

void		hash_delete(void)
{
	t_hashtable	*hashtable;
	int			i;

	hashtable = NULL;
	i = -1;
	ft_save_hash(&hashtable);
	while (++i < MAX_HASH)
		if (hashtable[i].hashcase)
			while (hashtable[i].hashcase)
			{
				ft_strdel(&hashtable[i].hashcase->command);
				hashtable[i].hashcase = hashtable[i].hashcase->next;
			}
	free(hashtable);
}

void			envset_del(const char *bin)
{
	if (g_env)
		ft_tabdel(&g_env);
	if (g_set)
		ft_tabdel(&g_set);
	hash_delete();
	history_save_file(bin);
}
