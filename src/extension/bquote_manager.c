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
	str_tmp1 = ft_return_back_b_quote();
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
	str_tmp1 = ft_return_after_b_quote();
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

int			bquote_manager(char ***cmd, int *j_index, int *i_index)
{
	int			j;//fd
	char		*tmp = NULL;
	char		*tmp2 = NULL;
	char		**tab_tmp;
	t_lex		lex;
	t_seq		*new_b_seq;
	t_seq		*new_n_seq;
	e_prompt	prompt;
	prompt = PROMPT;

	j = *j_index + 1;
	while ((*cmd)[*i_index][j] != '`')
		j++;
	if (*j_index + 1 != j)
	{
		tmp = ft_strsub((*cmd)[*i_index], *j_index + 1, j - *j_index + 1);
		//		tmp = ft_strjoin(tmp, " > .tmp_file");
		//		system(tmp);
		lex = ft_lexer(tmp, &prompt);
		new_b_seq = ft_parsing(lex);
		if (!extension(&new_b_seq))
		{
			new_n_seq = new_b_seq;
			while (new_n_seq)
			{
				new_n_seq->default_fd = j;
				ft_sequence(new_n_seq, j);//J EST LE FICHIER A CREER
				new_n_seq = new_n_seq->next;
			}
			j = open(".tmp_file", O_CREAT, O_RDONLY, O_WRONLY);
			while (get_next_line(j, &tmp) > 0)
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
			close(j);
			if (tmp2)
			{
				printf("--------------\n");
				printf("TMP2 == %s\n", tmp2);
				printf("--------------\n");
				ft_bquote_replace(&(*cmd), tmp2, i_index, j_index);
			}
			else
				printf("TMP2 == NULL, REMPLACEMENT DES BQUOTES IMPOSSIBLE\n");
		}
		ft_strdel(&tmp);
	}
	else
		ft_strdel_in_tab(&(*cmd), *i_index);
	return (0);
}
