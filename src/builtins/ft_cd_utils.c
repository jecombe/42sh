/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 22:26:15 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/28 04:27:11 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int			ft_canonical(char **curpath)
{
	char	buf[BI_MAX];
	char	cwd[BI_MAX];

	ft_strclr(buf);
	ft_strclr(cwd);
	if (*curpath[0] != '/')
	{
		if (!getcwd(cwd, sizeof(cwd)))
			return (EXIT_FAILURE);
		ft_strcpy(buf, cwd);
		buf[ft_strlen(buf) - 1] != '/' ? ft_strcat(buf, "/") : 0;
		ft_strcat(buf, *curpath);
		ft_strdel(curpath);
		if (!(*curpath = ft_strdup(buf)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_remove_sdot(char ***grid)
{
	int		i;
	char	**dupgrid;

	i = -1;
	dupgrid = NULL;
	while ((*grid)[++i])
		if ((ft_strcmp((*grid)[i], ".")) != 0)
			ft_malloc_cmd(&dupgrid, (*grid)[i]);
	ft_tabdel(grid);
	if (!(*grid = ft_tabdup(dupgrid)))
		return (EXIT_FAILURE);
	ft_tabdel(&dupgrid);
	return (EXIT_SUCCESS);
}

static int	ft_remove_ddot(char ***grid)
{
	int		i;
	int		j;
	char	**dupgrid;

	i = -1;
	j = -1;
	dupgrid = NULL;
	while ((*grid)[++i])
	{
		if ((ft_strcmp((*grid)[i], "..")) != 0)
		{
			if (ft_malloc_cmd(&dupgrid, (*grid)[i]))
				return (EXIT_FAILURE);
			j++;
		}
		else
			ft_strdel(&dupgrid[j--]);
	}
	ft_tabdel(grid);
	if (!(*grid = ft_tabdup(dupgrid)))
		return (EXIT_FAILURE);
	ft_tabdel(&dupgrid);
	return (EXIT_SUCCESS);
}

int			ft_rules(char **cmd)
{
	char	buf[BI_MAX];
	char	**grid;
	int		i;

	ft_strclr(buf);
	grid = NULL;
	i = -1;
	(*cmd[0] == '/') ? buf[0] = '/' : 0;
	if (!(grid = ft_strsplit(*cmd, '/')))
		return (EXIT_FAILURE);
	ft_remove_sdot(&grid);
	ft_remove_ddot(&grid);
	while (grid[++i])
	{
		(buf[0] == '\0') ? ft_strcpy(buf, grid[i]) : ft_strcat(buf, grid[i]);
		buf[ft_strlen(buf)] = '/';
	}
	ft_tabdel(&grid);
	ft_strdel(cmd);
	*cmd = ft_strdup(buf);
	return (EXIT_SUCCESS);
}
