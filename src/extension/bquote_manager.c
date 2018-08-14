#include "../../include/extension.h"

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

char		*recup_tmp_file()
{
	char		*ret;

	ret = NULL;
	return (ret);
}

int			bquote_manager(char ***cmd, int *j_index, int *i_index, int begin)
{
	int			fd;
	char		*tmp = NULL;
	char		*before_bquote = NULL;
	char		*after_bquote = NULL;
	char		*tmp2 = NULL;
	char		**tab_tmp;
	t_lex		lex;
	t_seq		*new_b_seq;
	t_seq		*new_n_seq;
	e_prompt	prompt;
	prompt = PROMPT;

	printf("BEGIN == %d J_INDEX == %d\n", begin, *j_index);
	fflush(NULL);
	if ((before_bquote = recup_before_bquote((*cmd)[*i_index], begin)))
		printf("BEFORE BQUOTE == %s\n", before_bquote);
	if ((after_bquote = recup_after_bquote((*cmd)[*i_index], *j_index)))
		printf("AFTER BQUOTE == %s\n", after_bquote);
	if ((tmp = recup_inside_bquote((*cmd)[*i_index], begin, *j_index)))
	{
		printf("INSIDE BQUOTE == %s\n", tmp);
		fd = open(".tmp_file", O_CREAT, O_RDONLY, O_WRONLY);

		/*
		lex = ft_lexer(tmp, &prompt);
		new_b_seq = ft_parsing(lex);
		if (!extension(&new_b_seq))
		{
			new_n_seq = new_b_seq;
			while (new_n_seq)
			{
				new_n_seq->default_fd = fd;
				ft_sequence(new_n_seq, fd);//J EST LE FICHIER A CREER
				new_n_seq = new_n_seq->next;
			}
		}*/
		fd = open(".tmp_file", O_CREAT, O_RDONLY, O_WRONLY);
		while (get_next_line(fd, &tmp) > 0)
		{
			if (tmp2)
			{
				tmp2 = ft_strjoin(tmp2, "\n");
				tmp2 = ft_strjoin(tmp2, tmp);
			}
			else
				tmp2 = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		close(fd);
	}
	printf("--------------\n");
	printf("TMP2 == %s\n", tmp2);
	printf("--------------\n");
	ft_bquote_replace(&(*cmd), tmp2, i_index, j_index);
	return (0);
}
