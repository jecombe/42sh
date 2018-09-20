/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/18 06:07:24 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/19 16:32:00 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

int		ft_isbegintab(char c, char before, int i)
{
	if ((i == 0 && ft_isprint(c) && !ft_isblank(c)) ||
		(i > 0 && ft_isblank(before) && ft_isprint(c) && !ft_isblank(c)))
		return (1);
	return (0);
}

int		ft_isendtab(char begin, char end, char echap, int i[2])
{
	int		ret;

	ret = 0;
//	if (ft_isquote(begin) && (begin != end && echap != '\\'))
	if (ft_isquote(begin) && begin != end && end != '\0')
	{
		printf("0BEGIN == |%c| END == |%c| ECHAP == |%c|, J == |%d|, I == |%d|\n", begin, end, echap, i[0], i[1]);
		ret = 1;
	}
	else if (ft_isprint(begin) && !ft_isblank(begin) && !ft_isblank(end) && end != '\0')
	{
		printf("1BEGIN == |%c| END == |%c| ECHAP == |%c|, J == |%d|, I == |%d|\n", begin, end, echap, i[0], i[1]);
		ret = 1;
	}
	else if (ft_isblank(begin) && ft_isblank(end) && end != '\0')
	{
		printf("2BEGIN == |%c| END == |%c| ECHAP == |%c|, J == |%d|, I == |%d|\n", begin, end, echap, i[0], i[1]);
		ret = 1;
	}
	else
		printf("3BEGIN == |%c| END == |%c| ECHAP == |%c|, J == |%d|, I == |%d|\n", begin, end, echap, i[0], i[1]);
	return (ret);
}

int		ft_isdir(char *test)
{
	struct stat		stat;

	if (lstat(test, &stat) != -1 && (stat.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}

int		ft_isechap(char c)
{
	if (c == '\n' || c == '\t' || c == '$' || c == ' ' || c == '/' || c == '*'||
		c == '\'' || c == '"' || c == '`' || c == '#' || c == '&' || c == '<' ||
		c == '>' || c == ';' || c == '|' || c == '!' || c == '?' || c == '\\' ||
		c == '~')
		return (1);
	return (0);
}

int		ft_isseparator(char c)
{
	if (c == '|' || c == '&' || c == ';')
		return (1);
	return (0);
}

char	*ft_search_pwd(char *ext)
{
	char	*ret;
	char	pwd[4096];
	char	*tmp;

	ret = NULL;
	getcwd(pwd, sizeof(pwd));
	if (ext)
	{
		tmp = ft_strjoin(pwd, "/");
		ret = ft_strjoin(tmp, ext);
		ft_strdel(&tmp);
	}
	else
		ret = ft_strdup(pwd);
	return (ret);
}
