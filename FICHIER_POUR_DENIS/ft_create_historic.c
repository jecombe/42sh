/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_create_historic.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/24 20:49:45 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/03/24 20:49:46 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	ft_search_in_space(char *str)
{
	int		i;

	i = -1;
	if (str)
		while (str[++i])
		{
			if (str[i] >= 33)
				return (0);
		}
	return (1);
}

int			ft_create_historic(char *str)
{
	int		fd;
	char	*tmp;

	tmp = NULL;
	if (ft_search_in_space(str) == 1)
		return (0);
	fd = open(".historic", O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
	ft_putendl_fd(str, fd);
	close(fd);
	return (0);
}
