/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension_error.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/09 07:14:01 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/09/14 05:38:52 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

static int		error_n_redirect(t_redirect **b_redirect)
{
	t_redirect	*n_redirect;

	n_redirect = *b_redirect;
	while (n_redirect)
	{
		if (!n_redirect->file)
		{
			ft_putendl("bash: ambiguous redirect");
			return (1);
		}
		n_redirect = n_redirect->next;
	}
	return (0);
}

static int				is_assign(char *cmd)
{
	int			i;

	i = 0;
	while (cmd[i])
	{
		if (ft_isalnum(cmd[i]) || cmd[i] == '=')
		{
			if (cmd[i] == '=')
				return (ft_isalpha(cmd[0]) ? 1 : 0);
		}
		else
			return (0);
		i++;
	}
	return (0);
}

static int		manage_var_builtin(char ***tablo)
{
	int			i;

	i = 0;
	if (*tablo)
	{
		while ((*tablo)[i] && is_assign((*tablo)[i]))
			i++;
		if (i == ft_tablen((*tablo)))
			ft_add_str_at(tablo, "ft_assign", 0);
		else if (i)
			while (i)
			{
				ft_strdel_in_tab(tablo, 0);
				i--;
			}
	}
	return (0);
}

static int		error_n_op(t_op **b_op)
{
	t_op		*n_op;
	t_op		*tmp;

	int i = 0;
	n_op = *b_op;
	while (n_op)
	{
		i = 0;
		if (n_op->cmd)
		{
			while (n_op->cmd[i])
			{
				printf("N_OP->CMD[i] == %s\n", n_op->cmd[i]);
				i++;
			}
		}
		else
		{
			printf("!!! N_OP->CMD\n");
		}
		tmp = NULL;
		if (error_n_redirect(&n_op->redirect))
			return (2);
		manage_var_builtin(&n_op->cmd);
		if (!n_op->redirect && !n_op->cmd)
		{
			printf("DEL_OP\n");
			if (del_nop_empty(&n_op, &tmp, b_op))
				return (1);
		}
		n_op = n_op ? n_op->next : tmp;
	}
	return (0);
}

int				extension_error(t_seq **b_seq)
{
	t_seq		*n_seq;
	t_seq		*tmp;
	int			ret;

	ret = 0;
	n_seq = *b_seq;
	while (n_seq)
	{
		tmp = NULL;
		if (n_seq->op)
		{
			if ((ret = error_n_op(&n_seq->op)))
			{
				if (ret == 1 && (n_seq->prev || n_seq->next))
				{
					printf("000EXT_ERR\n");
		//			tmp = n_seq->next ? n_seq->next : NULL;
		//			*b_seq = !(*b_seq)->prev ? (*b_seq)->next : *b_seq;
		//			ft_free_n_seq(&n_seq, b_seq);
					if (ft_free_n_seq(&n_seq, b_seq) == 1)
						return (1);
				}
				else
				{
					printf("111EXT_ERR\n");
					ft_free_b_seq(b_seq);
					return (1);
				}
			}
		}
		else
		{
			printf("222EXT_ERR\n");
		//		if (n_seq->prev || n_seq->next)
		//		{
		//			tmp = n_seq->next ? n_seq->next : NULL;
		//			*b_seq = !(*b_seq)->prev ? (*b_seq)->next : *b_seq;
		//			ft_free_n_seq(&n_seq);
		//		}
		//		else
		//		{
					ft_free_b_seq(b_seq);
					return (1);
		//		}
		}
		n_seq = n_seq ? n_seq->next : tmp;
	}
	return (0);
}
