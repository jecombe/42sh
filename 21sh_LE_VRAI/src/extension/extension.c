#include "../../include/extension.h"

int			ft_convert(t_seq **n_seq)
{
	t_op		*n_op;
	int			i;
	int			j;

	n_op = (*n_seq)->op;
	while (n_op)
	{
		i = -1;
		while (n_op->cmd[++i])
		{
			
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
		if (ft_convert(&n_seq))
			return (1);
		n_seq = n_seq->next;
	}
	return (0);
}
