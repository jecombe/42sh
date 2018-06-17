/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sdsearch_soft.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/31 15:06:11 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/03 06:54:24 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*ft_open_file(char *path, char *file)
{
	DIR				*dir;
	struct dirent	*dirent;
	int				i;
	char			*str;

	i = 0;
	str = NULL;
	dir = opendir(path);
	if (dir)
		while ((dirent = readdir(dir)))
		{
			if ((str = ft_search_occurences(file, dirent->d_name, 0)) != NULL)
			{
//				printf("\n\r11str11 == %s\n\r", str);
				return (str);
			}
		}
	if (dir)
		closedir(dir);
	return (NULL);
}

char		*ft_search_builtin(char *str)
{
	if (str)
	{
		if (ft_search_occurences(str, "cd", 0))
			return ("cd");
		else if (ft_search_occurences(str, "echo", 0))
			return ("echo");
		else if (ft_search_occurences(str, "env", 0))
			return ("env");
		else if (ft_search_occurences(str, "exit", 0))
			return ("exit");
		else if (ft_search_occurences(str, "search_dyn", 0))
			return ("search_dyn");
		else if (ft_search_occurences(str, "setenv", 0))
			return ("setenv");
		else if (ft_search_occurences(str, "unsetenv", 0))
			return ("unsetenv");
	}
	return (NULL);
}

char		*ft_sdsearch_soft(char *str, char **my_env)
{
	char		**path_bin;
	int			i;
	char		*ret;

	i = 0;
	path_bin = NULL;
	if ((ret = ft_search_builtin(str)) != NULL)
	{
		return (ret);
	}
	else if (ft_recup_pathbin(&path_bin, my_env) == 0)
	{
		while (path_bin[i])
		{
			if ((ret = ft_open_file(path_bin[i++], str)) != NULL)
			{
	//			printf("\n\r0str0 == %s\n\r", ret);
				return (ret);
			}
		}
	}
	return (str);
}

void		ft_manage_sdsearch_soft(t_tline **tline, char **my_env, char **str)
{
	int		ret;
	char	*tmp;

	if ((tmp = ft_sdsearch_soft(*str, my_env)))
	{
		(*tline)->searchdyn = ft_strdup(tmp + ft_strlen(*str));
		ft_putstr((*tline)->searchdyn);
		ret = (int)ft_strlen((*tline)->searchdyn);
		while (ret)
		{
			tputs(tgetstr("le", NULL), 1, ft_outc);
			ret--;
		}
	}
	else if ((*tline)->searchdyn)
		ft_strdel(&(*tline)->searchdyn);
}
