/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 05:00:48 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/08 06:15:00 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"

int			ft_strdel_in_tab(char ***tablo, int index)
{
	int			i;
	char		**tmp;

	i = 0;
	if ((*tablo)[i + 1])
	{
		while (i < index)
			if (ft_malloc_cmd(&tmp, (*tablo)[i++]))
				return (1);
		i++;
		while ((*tablo)[i])
			if (ft_malloc_cmd(&tmp, (*tablo)[i++]))
				return (1);
		ft_tabdel(&(*tablo));
		if (!(*tablo = ft_tabdup(tmp)))
			return (1);
	}
	else
		ft_tabdel(&(*tablo));
	return (0);
}

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
		printf("TMP == %s\n", tmp);
		//		ft_strdel(&(*str));
		*index = i;
		*str = ft_strdup(tmp);
	}
	return (0);
}

int			ft_create_tmp_file(void)
{
	static int		fd = 0;

	if (fd)
		fd = open(".tmp_file", O_CREAT, O_APPEND, O_WRONLY, S_IRWXU);
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
				printf("FD == %s, redirect == %s FILE == %s\n", n_redirect->fd, cv(n_redirect->redirect), n_redirect->file);
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
	//	printf("BBUUGG\n");
	while (tab_tmp2[i])
		ft_malloc_cmd(&tab_tmp, tab_tmp2[i++]);
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
	char		*tmp;
	char		**tab_tmp;
	t_lex		lex;
	t_seq		*new_b_seq;

	*j_index = *j_index + 1;
	j = *j_index;
	tmp = NULL;
	while ((*cmd)[i_index][j] != '`')
		j++;
	if (*j_index != j)
	{
		tmp = ft_strsub((*cmd)[i_index], *j_index, j - *j_index);
		printf("TMP = %s\n", tmp);
		*j_index = j;
		ft_bquote_replace(&(*cmd), tmp, i_index);
	}
	else
		ft_tabdel(&(*cmd));
	printf("000BUGG\n");
	*j_index = j + 1;
	lex = ft_lexer(tmp);
	new_b_seq = ft_parsing(lex);
	if (!extension(&new_b_seq))
	{
		j = ft_create_tmp_file();
//	printf("BBBUUUGGG\n");
	while (new_b_seq)
	{
		if (new_b_seq->op)
			ft_solver(new_b_seq->op, j);//PLUS LES FICHIER A CREER
		new_b_seq = new_b_seq->next;
	}
//		ft_watch_result(tmp, lex, new_b_seq);
//		while (get_next_line(i, &tmp))
//		{
//			ft_malloc_cmd(&tab_tmp, tmp);
//			ft_strdel(&tmp);
//		}
		ft_create_tmp_file();
	printf("111BUGG\n");
	}
	//	ft_strdel(&tmp);
	return (0);
}

int			ft_parcour_tab(char ***cmd)
{
	int			i;
	int			j;
	int			k;

	i = -1;
	if (*cmd)
		while (*cmd && (*cmd)[++i])
		{
			j = 0;
			while ((*cmd)[i][j])
			{
				if ((*cmd)[i][j] == '\\')
					j += 2;
				else if ((*cmd)[i][j] == '\'')
					ft_manage_quote(&(*cmd), i, &j);
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
				if (!*cmd)//RESOUT LE SEGSEG
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
		{
			printf("0000\n");
			ft_parcour_tab(&n_op->cmd);
			printf("1111\n");
		}
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
	printf("EXT FINISH\n");
	return (0);
}
