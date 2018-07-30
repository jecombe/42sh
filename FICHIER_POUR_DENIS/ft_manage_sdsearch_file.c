/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sdsearch_file.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/01 23:43:32 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/03 05:15:33 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/minishell.h"

int			ft_is_rep(char *complete_path)
{
	struct stat		stat;
	int				ret;

	if (complete_path)
	{
		ret = lstat(complete_path, &stat);
		if (ret != -1)
			if ((stat.st_mode & S_IFMT) == S_IFDIR)
				return (1);
	}
	return (0);
}

void		ft_search_path(char **file, char **actual_rep, char **ret)
{
	*ret = ft_strdup(ft_strrchr(*file, '/'));
	if (*file[0] == '/')
	{
		if (ft_strlen(*file) - ft_strlen(ft_strrchr(*file, '/')) > 0)
			*actual_rep = ft_strsub(*file, 0, ft_strlen(*file) -
			ft_strlen(ft_strrchr(*file, '/')) + 1);
		else
			*actual_rep = ft_strdup("/");
	}
	else
	{
		*actual_rep = ft_strjoin(*actual_rep, "/");
		*actual_rep = ft_strjoin(*actual_rep, ft_strsub(*file, 0,
		ft_strlen(*file) - ft_strlen(ft_strrchr(*file, '/')) + 1));
	}
	if (ft_strrchr(*file, '/') + 1 != '\0')
	{
		*file = ft_strdup(ft_strrchr(*file, '/') + 1);
		if (!(*file[0] >= '!' && *file[0] <= '~'))
			ft_strdel(&(*file));
	}
	else if (*file)
		ft_strdel(&(*file));
}

char		*ft_search_occurences_in_current(char **file, char **actual_rep)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*str = NULL;
	char			*ret;

	ret = NULL;
	if (ft_strchr(*file, '/') && *actual_rep)
		ft_search_path(&(*file), &(*actual_rep), &ret);
	dir = opendir(*actual_rep);
	if (dir)
		while ((dirent = readdir(dir)))
			if ((str = ft_search_occurences(*file, dirent->d_name, 1)) != NULL)
				if (ft_is_rep(ft_strjoin(*actual_rep, dirent->d_name)) == 1)
					return (ft_strjoin(str, "/"));
	dir ? closedir(dir) : 0;
	dir = opendir(*actual_rep);
	if (dir)
		while ((dirent = readdir(dir)))
			if ((str = ft_search_occurences(*file, dirent->d_name, 0)) != NULL)
				return (str);
	dir ? closedir(dir) : 0;
	return (NULL);
}

char		*ft_sdsearch_file(char *file, char **my_env)
{
	char			*actual_rep;
	char			*ret;
	char			*new_file;


	if (!(actual_rep = ft_getenv("PWD", my_env)))
		return (NULL);
	actual_rep = ft_strjoin(actual_rep, "/");
	if (file)
		new_file = ft_strdup(file);
	if ((ret = ft_search_occurences_in_current(&new_file, &actual_rep)))
		return (ret);
	return (NULL);
}

void		ft_manage_sdsearch_file(t_tline **tline, char ** my_env, char **str)
{
	int			ret;
	char		*tmp;
	if ((tmp = ft_sdsearch_file(*str, my_env)))
	{
		if (strchr(*str, '/'))
			tmp = ft_strjoin(ft_strsub(*str, 0, ft_strlen(*str) - ft_strlen(ft_strrchr(*str, '/')) + 1), tmp);
		ft_putstr(tmp + ft_strlen(*str));
		(*tline)->searchdyn = ft_strdup(tmp + ft_strlen(*str));
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
