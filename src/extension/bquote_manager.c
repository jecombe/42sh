#include "../../include/heart.h"

int			ft_bquote_replace(char ***cmd, char *in_bquote, int *i_index, int *j_index)
{
	char	*ifs;
	char	**tab_tmp;
	char	**tab_tmp2;
	char	*str_tmp1 = NULL;
	char	*str_tmp2 = NULL;
	int		i = 0;

	ifs = ft_strdup("a.");
	tab_tmp = NULL;
	tab_tmp2 = NULL;
	while (i < *i_index)
		ft_malloc_cmd(&tab_tmp, (*cmd)[i++]);
	i = 0;
//	str_tmp1 = ft_return_back_b_quote();
	tab_tmp2 = ft_split_bquote(in_bquote, ifs);
	while (tab_tmp2[i])
	{
		if (str_tmp1)
		{
			str_tmp2 = ft_strjoin(str_tmp1, tab_tmp2[i++]);
			ft_malloc_cmd(&tab_tmp, str_tmp2);
			ft_strdel(&str_tmp1);
			ft_strdel(&str_tmp2);
		}
		else
			ft_malloc_cmd(&tab_tmp, tab_tmp2[i++]);
	}
	i = *i_index + 1;
//	str_tmp1 = ft_return_after_b_quote();
	while ((*cmd)[i])
	{
		if ((*cmd)[i + 1] || (!(*cmd)[i + 1] && !str_tmp1))
			ft_malloc_cmd(&tab_tmp, (*cmd)[i++]);
		else
		{
			str_tmp2 = ft_strjoin((*cmd)[i++], str_tmp1);
			ft_malloc_cmd(&tab_tmp, str_tmp2);
		}
	}
	ft_tabdel(&(*cmd));
	if (tab_tmp)
		*cmd = ft_tabdup(tab_tmp);
	return (0);
}

char		*recup_inside_bquote(char *cmd, int begin, int j_index)
{
	char		*ret;

	ret = NULL;
	if (begin + 1 < j_index)
		ret = ft_strsub(cmd, begin + 1, j_index - (begin + 1));
	return (ret);
}

char		*recup_before_bquote(char *cmd, int begin)
{
	char		*ret;

	ret = NULL;
	if (begin > 0)
		ret = ft_strsub(cmd, 0, begin);
	return (ret);
}

char		*recup_after_bquote(char *cmd, int j_index)
{
	char		*ret;

	ret = NULL;
	if (j_index < ft_strlen(cmd) - 1)
		ret = ft_strsub(cmd, j_index + 1, ft_strlen(cmd) - j_index + 1);
	return (ret);
}

char		*recup_tmp_file(char *cmd, int begin, int j_index)
{
	char		*ret;
	char		*tmp;
	char		*line;
	int			fd;

	fd = open(".tmp_file", O_CREAT, O_RDONLY);
	ret = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (ret)
		{
			tmp = ft_strjoin(ret, "\n");
			ft_strdel(&ret);
			ret = ft_strjoin(tmp, line);
		}
		else
		{
			if ((tmp = recup_before_bquote(cmd, begin)))
			{
				printf("BEFORE BQUOTE == %s\n", tmp);
				ret = ft_strjoin(tmp, line);
			}
			else
				ret = ft_strdup(line);
		}
		tmp ? ft_strdel(&tmp) : 0;
		ft_strdel(&line);
	}
	if ((tmp = recup_after_bquote(cmd, j_index)))
	{
		printf("AFTER BQUOTE == %s\n", tmp);
		if (ret)
		{
			line = ft_strdup(ret);
			ft_strdel(&ret);
			ret = ft_strjoin(line, tmp);
			ft_strdel(&line);
		}
		else
			ret = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	close(fd);
	return (ret);
}

int			bquote_manager(char ***cmd, int *j_index, int *i_index, int begin)
{
	int			fd;
	char		*line = NULL;
	char		*before_bquote = NULL;
	char		*after_bquote = NULL;
	e_prompt	prompt;

	prompt = PROMPT;
	printf("BEGIN == %d J_INDEX == %d\n", begin, *j_index);
	fflush(NULL);
	if ((line = recup_inside_bquote((*cmd)[*i_index], begin, *j_index)))
	{
		printf("INSIDE BQUOTE == %s\n", line);
		fd = open(".tmp_file", O_CREAT, O_RDONLY, O_WRONLY);
		heart_of_101sh(line, &prompt, fd);
		ft_strdel(&line);
		//A VOIR AVEC JECOMBE SI IL CLOSE LE FD
	}
	line = recup_tmp_file((*cmd)[*i_index], begin, *j_index);
	printf("--------------\n");
	printf("LINE == %s\n", line);
	printf("--------------\n");
//	ft_bquote_replace(&(*cmd), line, i_index, j_index);
	return (0);
}
