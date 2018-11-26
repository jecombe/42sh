/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt_git.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 21:19:07 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/18 06:01:42 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

void				ft_miniconcat(char **s1, char *s2)
{
	char *ret;

	ret = NULL;
	ret = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = ft_strdup(ret);
	ft_strdel(&ret);
}

static	char		*ft_check_git_config(char **path)
{
	int		fd;
	char	*line;

	ft_miniconcat(path, "/config");
	fd = open(*path, O_RDONLY);
	ft_strdel(path);
	while (get_next_line(fd, &line))
	{
		if (!ft_strncmp("[branch ", line, 8))
		{
			line[ft_strlen(line) - 2] = '\0';
			*path = ft_strdup(line + 9);
			ft_strdel(&line);
			close(fd);
			return (*path);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(fd);
	return (NULL);
}

static	char		*ft_get_git_branch_inner(void)
{
	int		i;
	char	cwd[1024];
	char	*path;

	getcwd(cwd, 1024);
	path = ft_strdup(cwd);
	ft_miniconcat(&path, "/.git");
	i = ft_strlen(path);
	while (--i >= 0)
	{
		if (path[i] == '/' && ft_strcmp(path + i, ".git"))
		{
			path[i] = '\0';
			ft_miniconcat(&path, "/.git");
		}
		if (!access(path, F_OK))
			return (ft_check_git_config(&path));
	}
	free(path);
	return (NULL);
}

void				ft_print_git_branch(void)
{
	char	*prompt;
	char	*git_branch;

	prompt = ft_strdup("\e[94mgit:(\e[95m");
	git_branch = ft_get_git_branch_inner();
	ft_miniconcat(&prompt, git_branch);
	free(git_branch);
	ft_miniconcat(&prompt, "\e[94m)\e[0m ");
	ft_putstr(prompt);
	free(prompt);
}

int					ft_get_git_branch(char buff[])
{
	char	*git_branch;
	int		ret;

	ret = 0;
	if ((git_branch = ft_get_git_branch_inner()))
	{
		ft_geoprintf(buff, "\e[94mgit:(\033[1;31m%s\e[94m)\e[0m ", git_branch);
		ret = ft_strlen(git_branch);
		free(git_branch);
	}
	return (ret);
}
