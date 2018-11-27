/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 05:00:48 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/26 10:52:57 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int	ft_parcour_tab(char ***cmd)
{
	t_bquote	*i;
	int			ret;

	if (init_parcour_tab(&i))
		return (1);
	while (*cmd && (*cmd)[++i->i])
	{
		i->j = 0;
		while (i->j >= 0 && (*cmd)[i->i][i->j])
		{
			replace_parcour(&ret, cmd, &i);
			if (!(*cmd) || !(*cmd)[i->i] || ret == -1 || g_interupt == 1)
				return (return_parcour_tab(*cmd, ret, &i));
		}
	}
	free(i);
	return (0);
}

static int	ft_parcour_file(t_redirect **redirect)
{
	t_bquote	*i;
	int			ret;
	char		**cmd;
	t_redirect	*t;

	t = *redirect;
	while (t && t->file)
	{
		cmd = NULL;
		ft_malloc_cmd(&cmd, t->file);
		if (init_parcour_tab(&i))
			return (1);
		i->i = 0;
		while (cmd[i->i][i->j])
		{
			replace_parcour(&ret, &cmd, &i);
			if (!cmd || !cmd[i->i] || ret == -1 || g_interupt == 1)
				return (return_parcour_tab(cmd, ret, &i) + ft_strdel(&t->file));
		}
		t->file = ft_strdup_free(cmd[0], t->file);
		ft_tabdel(&cmd);
		free(i);
		t = t->next;
	}
	return (0);
}

static int	ft_parcour_op(t_op **b_op)
{
	t_op		*n_op;
	int			ret;

	n_op = *b_op;
	while (n_op)
	{
		if (n_op->cmd)
		{
			if ((ret = ft_parcour_tab(&n_op->cmd)) != 0 && ret != 2)
				return (1);
			else if (ret != 2 && n_op && (ret =
						ft_parcour_file(&n_op->redirect)) && ret != 2)
			{
				return (1);
			}
			else if (ret == 2)
			{
				if (!n_op->redirect)
					return (2);
			}
		}
		n_op = n_op->next;
	}
	return (0);
}

int			begin_ft_sequence(int *v_if, t_token *tk, int fd, t_seq **n_seq)
{
	t_loop		loop;

	if (*tk == TOKEN || *tk == SEMI || *tk == AND ||
			(*tk == AND_IF && !*v_if) || (*tk == OR_IF && *v_if))
	{
		*v_if = ft_sequence(*n_seq, fd, &loop);
		if (loop.exit == 1)
			return (loop.result);
	}
	*tk = (*n_seq)->token;
	*n_seq = (*n_seq)->next;
	return (1111);
}

int			extension(t_seq **b_seq, int fd)
{
	t_seq		*n_seq;
	int			ret;
	int			v_if;
	int			err;
	t_token		tk;

	init_extension(&tk, &v_if, b_seq, &n_seq);
	while (n_seq)
	{
		if ((ret = ft_parcour_op(&n_seq->op)) != 0 && ret != 2)
			return (999);
		if (ret == 2)
		{
			if (ft_free_n_seq(&n_seq, b_seq) == 1)
				return (999);
		}
		else if (!(err = extension_error(b_seq, 0)))
		{
			if ((err = begin_ft_sequence(&v_if, &tk, fd, &n_seq)) != 1111)
				return (err);
		}
		else
			return (999);
	}
	return (fd ? 999 : v_if);
}
