/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@le-101.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/12 19:29:18 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/06/01 23:48:32 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

t_fd			*ft_multi_fd(t_fd **gnl, const int fd)
{
	t_fd	*cur;

	cur = *gnl;
	while (cur && cur->fd != fd)
		cur = cur->next;
	if (!cur)
	{
		cur = (t_fd*)malloc(sizeof(t_fd));
		cur->save = ft_strdup("");
		cur->fd = fd;
		cur->next = *gnl;
		*gnl = cur;
	}
	return (cur);
}

int				get_next_line(const int fd, char **line)
{
	static	t_fd	*gnl;
	t_fd			*cur;

	cur = ft_multi_fd(&gnl, fd);
	while ((cur->ret = read(fd, cur->buf, BUFF_SIZE)) > 0)
	{
		cur->buf[cur->ret] = '\0';
		cur->save = ft_strjoin_free(cur->save, cur->buf);
		if (ft_strchr(cur->buf, '\n'))
			break ;
	}
	if (ft_strchr(cur->save, '\n'))
	{
		*line = ft_strsub(cur->save, 0, ft_strchr(cur->save, '\n') - cur->save);
		cur->tmp = ft_strdup(cur->save + ft_strlen(*line) + 1);
		ft_strdel(&cur->save);
		cur->save = ft_strdup(cur->tmp);
		ft_strdel(&cur->tmp);
		return (cur->ret == -1 ? -1 : 1);
	}
	if (!ft_strchr(cur->save, '\n') && ft_strlen(cur->save) == 0)
		return (cur->ret == -1 ? -1 : 0);
	*line = ft_strdup(cur->save);
	cur->save = ft_strdup("");
	return (cur->ret == -1 ? -1 : 1);
}
