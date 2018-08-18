/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   extension_error.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/09 07:14:01 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/18 19:56:16 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/extension.h"

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

static int		error_n_op(t_op **b_op)
{
	t_op		*n_op;
	t_op		*tmp;
	int i = 0;

	n_op = *b_op;
	tmp = NULL;
	while (n_op)
	{
		if (!n_op->cmd && !n_op->redirect)
		{
			printf("N_OP A DEL\n");
			tmp = n_op;
			if (n_op->prev)
				n_op->prev->token = n_op->token;
			if (n_op->next && !n_op->prev)
				*b_op = (*b_op)->next;
			else if (n_op->next && n_op->prev)
				n_op->prev->next = n_op->next;
		}
//		else
//			printf("TOUT EST NORMAL\n");
		if (n_op->redirect)
			if (error_n_redirect(&n_op->redirect))
				return (1);
		n_op = n_op->next;
		if (tmp)
		{
//			printf("0\n");
			free(tmp);
			tmp = NULL;
//			printf("1\n");
//			fflush(NULL);
		}
//		if (tmp)
//			printf("TMP EXIST TOUJOURS\n");
//		else
//			printf("TMP N'EXIST PLUS\n");
//		if (n_op)
//			printf("N_OP EXIST TOUJOURS\n");
//		else
//			printf("N_OP N'EXIST PLUS\n");
		i++;
	}
//		if (*b_op)
//			printf("B_OP EXIST TOUJOURS\n");
//		else
//			printf("B_OP N'EXIST PLUS\n");
//	printf("I == %d\n", i);
	return (0);
}

int				extension_error(t_seq **b_seq)
{
	t_seq		*n_seq;

	n_seq = *b_seq;
	while (n_seq)
	{
		if (n_seq->op)
		{
			if (error_n_op(&n_seq->op) == 1)
			{
				ft_free_b_seq(b_seq);
				return (1);
			}
		}
//		if (n_seq->token == TOKEN && !n_seq->op)
		if (!n_seq->op)
		{
//			printf("N_SEQ A DEL\n");
			if (n_seq->prev && n_seq->next)
				n_seq->prev->next = n_seq->next;
			else if (!n_seq->prev && n_seq->next)
				*b_seq = (*b_seq)->next;
			free(n_seq);
			n_seq = NULL;
			return (1);
		}
		n_seq = n_seq->next;
	}
//	if (*b_seq)
//		printf("BSEQ EXIST\n");
//	else
//		printf("BSEQ EST DEAD\n");
	return (*b_seq ? 0 : 1);
}
