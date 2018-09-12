/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_files.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/10 02:02:08 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/10 02:02:59 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "heart.h"

int			init_files(const char *bin)
{
	char	*path;
	char	*buf;

	path = NULL;
	buf = NULL;
	if (!(path = search_path_of_101sh((char *)bin)))
		return (EXIT_FAILURE);
	if ((access((buf = ft_strjoin(path, "/.101sh_history")), F_OK)) == -1)
		creat(buf, 0644);
	ft_strdel(&buf);
	if ((access((buf = ft_strjoin(path, "/.101sh_aliases")), F_OK)) == -1)
		creat(buf, 0644);
	ft_strdel(&buf);
	ft_strdel(&path);
	return (EXIT_SUCCESS);
}
