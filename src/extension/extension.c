/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 05:00:48 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/12 03:02:49 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"

int			ft_add_tild(char **str, int *index)
{
	char		*var;
	char		*tmp;
	int			i;
	int			j;

	j = 1;
	i = -1;
	if ((var = ft_getenv("HOME", g_env)) && (!(*str)[*index + 1] || (*str)[*index + 1] == '/'))
	{
		tmp = malloc(sizeof(char*) * (ft_strlen(*str) + ft_strlen(var)));
		while (var[++i])
			tmp[i] = var[i];
		while ((*str)[j])
			tmp[i++] = (*str)[j++];
		tmp[i] = '\0';
		*index = i;
		*str = ft_strdup(tmp);
	}
	return (0);
}

int			ft_create_tmp_file(void)
{
	static int		fd = 0;

	if (!fd)
	{
		fd = open(".tmp_file", O_CREAT, O_RDONLY, O_WRONLY);
		system("chmod 777 .tmp_file");
	}
	else
	{
		close(fd);
		fd = 0;
	}
	return (fd);
}

#define cv ft_convert_token_to_string

static void	ft_watch_result(char *line, t_lex lex, t_seq *n_seq)
{			
	int		i = -1;
	t_op	*n_op;
	t_redirect	*n_redirect;

	printf("%sLINE :%s\n%s\n", RED, END, line);
	printf("%sLEXER : \n%s", RED, END);
	while (lex.name[++i])
		printf(".%s. .%s.\n", lex.name[i], ft_convert_token_to_string(lex.token[i]));
	while (n_seq)
	{
		n_op = n_seq->op;
		while (n_op)
		{
			if (n_op->cmd)
			{
				i = -1;
				while (n_op->cmd[++i])
					printf("CMD[%d] == %s\n", i, n_op->cmd[i]);
			}
			n_redirect = n_op->redirect;
			while (n_redirect)
			{
				printf("FD == %d, redirect == %s FILE == %s\n", n_redirect->fd, cv(n_redirect->redirect), n_redirect->file);
				n_redirect = n_redirect->next;
			}
			printf("n_op->token == %s\n", cv(n_op->token));
			n_op = n_op->next;
		}
		printf("n_seq->token == %s\n", cv(n_seq->token));
		n_seq = n_seq->next;
	}
	ft_putstr(END);
}

int			ft_bquote_replace(char ***cmd, char *in_bquote, int index)
{
	char	*ifs;
	char	**tab_tmp;
	char	**tab_tmp2;
	int		i = 0;

	ifs = ft_strdup("pa");
	tab_tmp = NULL;
	tab_tmp2 = NULL;
	while (i < index)
		ft_malloc_cmd(&tab_tmp, (*cmd)[i++]);
	i = 0;
	tab_tmp2 = ft_split_bquote(in_bquote, ifs);
	while (tab_tmp2[i])
		ft_malloc_cmd(&tab_tmp, tab_tmp2[i++]);
		printf("BBUUGG\n");
	i = index + 1;
	while ((*cmd)[i])
		ft_malloc_cmd(&tab_tmp, (*cmd)[i++]);
	ft_tabdel(&(*cmd));
	if (tab_tmp)
		*cmd = ft_tabdup(tab_tmp);
	return (0);
}

int			ft_bquote(char ***cmd, int *j_index, int i_index)
{
	int			j;//fd
	char		*tmp = NULL;
	char		*tmp2 = NULL;
	char		**tab_tmp;
	t_lex		lex;
	t_seq		*new_b_seq;

	*j_index = *j_index + 1;
	j = *j_index;
	while ((*cmd)[i_index][j] != '`')
		j++;
	if (*j_index != j)
	{
		tmp = ft_strsub((*cmd)[i_index], *j_index, j - *j_index);
		tmp = ft_strjoin(tmp, " > .tmp_file");
		printf("TMP = %s\n", tmp);
		system(tmp);
//		*j_index = j;
//		lex = ft_lexer(tmp);
//		new_b_seq = ft_parsing(lex);
		ft_strdel(&tmp);
//		if (!extension(&new_b_seq))
//		{
	//		j = ft_create_tmp_file();
//			while (new_b_seq)
//			{
//				if (new_b_seq->op)
//				{
//					printf("JECOMBE TU GERES PAS MDRRR\n");
//					ft_solver(new_b_seq->op, j);//J EST LE FICHIER A CREER
//				}
//				new_b_seq = new_b_seq->next;
//			}
//			ft_watch_result(tmp, lex, new_b_seq);
			j = open(".tmp_file", O_CREAT, O_RDONLY);
			while (get_next_line(j, &tmp))
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
			ft_bquote_replace(&(*cmd), tmp2, i_index);
//			printf("TMP2 FILE == %s\n", tmp2);
			close(j);
			//ft_create_tmp_file();
//		}
	//	ft_strdel(&tmp);
	}
	else
		ft_strdel_in_tab(&(*cmd), i_index);
	*j_index = j + 1;
	return (0);
}

int			backslash_out_dquote(char **cmd, int *j)
{
	char		*tmp;
	int			i;
	int			i2;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(*cmd));
	while (i < *j)
	{
		tmp[i] = (*cmd)[i];
		i++;
	}
	i2 = i;
	i++;
	while ((*cmd)[i])
	{
		tmp[i2] = (*cmd)[i];
		i++;
		i2++;
	}
	tmp[i2] = '\0';
	ft_strdel(&(*cmd));
	*cmd = ft_strdup(tmp);
	return (0);
}

int			ft_manage_backslash(char ***cmd, int i, int *j, int d_quote)
{
	if (d_quote == 0)
		backslash_out_dquote(&(*cmd)[i], j);
	else
		*j = *j + 1;
	*j = *j + 1;
	return (0);
}

int			ft_parcour_tab(char ***cmd)
{
	int			i;
	int			j;
	int			k;
	int			dquote;

	dquote = 0;
	i = -1;
	if (*cmd)
		while (*cmd && (*cmd)[++i])
		{
			j = 0;
			while ((*cmd)[i][j])
			{
				if ((*cmd)[i][j] == '\\')
				{
					ft_manage_backslash(&(*cmd), i, &j, dquote);
				}
				else if ((*cmd)[i][j] == '\'' && dquote == 0)
				{
					ft_manage_quote(&(*cmd), i, &j, ft_replace_quote);
				}
				else if ((*cmd)[i][j] == '"')
				{
					ft_manage_quote(&(*cmd), i, &j, ft_replace_dquote);
					dquote = dquote == 1 ? 0 : 1;
				}
				else if ((*cmd)[i][j] == '~' && j == 0)
				{
					if (ft_add_tild(&(*cmd)[i], &j))
						return (1);
				}
				else if ((*cmd)[i][j] == '`')
				{
					ft_bquote(&(*cmd), &j, i);
				}
				else
					j++;
				if (!(*cmd) || !(*cmd)[i])//RESOUT LE SEGSEG
					return (0);
			}
		}
	return (0);
}

int			ft_parcour_op(t_op **b_op)
{
	t_op		*n_op;

	n_op = *b_op;
	while (n_op)
	{
		if (n_op->cmd)
			ft_parcour_tab(&n_op->cmd);
		n_op = n_op->next;
	}
	return (0);
}

int			extension(t_seq **b_seq)
{
	t_seq		*n_seq;

	n_seq = *b_seq;
	while (n_seq)
	{
		if (n_seq->op)
			if (ft_parcour_op(&n_seq->op))
				return (1);
		n_seq = n_seq->next;
	}
	extension_error(b_seq);
	return (0);
}
