/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   separate.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:00:53 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/03 19:06:24 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"


typedef struct s_separate
{
	int i;
	int or_if;
	int and_if;
	int ret;
}			t_separate;

int			ft_separate_pipe_2(t_separate **separate, t_op *opera, pid_t pid)
{
	if (opera->prev)
		if (opera->prev->token != PIPE)
			(*separate)->i = 0;
	if (opera->token == PIPE)
	{
		(*separate)->i = ft_count_pipe(opera);
		(*separate)->i++;
		(*separate)->ret = ft_pipe(opera, (*separate)->i, pid);
	}
	while ((*separate)->i != 0)
	{
		opera = opera->next;
		(*separate)->i--;
	}
	if (opera == NULL)
		return (101);
	return (42);
}
int			ft_separate_pipe(t_separate *separate, t_op *opera, pid_t pid)
{
	if (separate->or_if == 0)
	{
		if (separate->and_if == 0)
		{
			if (opera->token == PIPE)
			{
				if (ft_separate_pipe_2(&separate, opera, pid) == 101)
					return (101);
				if (separate->ret == EXIT_SUCCESS)
				{
					if (opera->prev->token == OR_IF)
						separate->or_if = 1;
					else
						separate->or_if = 0;
					separate->ret = 0;
				}
				else if (separate->ret == EXIT_FAILURE)
				{
					if (opera->prev->token == AND_IF)
						separate->and_if = 1;
					else
						separate->and_if = 0;
					separate->ret = 0;
				}
			}
		}
	}
	return (EXIT_SUCCESS);
}


void			ft_separate_no_pipe(t_separate *separate, t_op *opera, pid_t pid, int fd)
{
	if (opera->token != PIPE)
	{
		if (separate->or_if == 0 && separate->i == 0)
		{
			if (separate->and_if == 0)
			{
				separate->ret = ft_solver(opera, fd, pid, 0);
				add_to_set("?", ft_itoa(separate->ret));
			}
		}
		if (separate->ret == EXIT_SUCCESS)
		{
			if (opera->token == OR_IF)
				separate->or_if = 1;
			else
				separate->or_if = 0;
			separate->ret = 0;
		}
		else if (separate->ret == EXIT_FAILURE)
		{
			if (opera->token == AND_IF)
				separate->and_if = 1;
			else
				separate->and_if = 0;
			separate->ret = 0;
		}
	}
}

void		ft_separate(t_seq *b_seq, int fd, pid_t pid)
{
	t_op *opera;
	t_separate separate;

	separate.i = 0;
	separate.or_if = 0;
	separate.and_if = 0;
	separate.ret = 0;
	opera = b_seq->op;
	if (opera->next)
	{
		while (opera)
		{
			if (ft_separate_pipe(&separate, opera, pid) == 101)
				return ;
			ft_separate_no_pipe(&separate, opera, pid, fd);
			opera = opera->next;
		}
		return ;
	}
	else
	{
		separate.ret = ft_solver(opera, fd, pid, 0);
		add_to_set("?", ft_itoa(separate.ret));
	}
}
/*
void		ft_separate(t_seq *b_seq, int fd, pid_t pid)
{
    t_op *opera;
    int ret;
    int and_if;
    int or_if;
    int i = 0;
    int ok = 0;
    
    and_if = 0;
    or_if = 0;
    opera = b_seq->op;
    ret = 0;
    if (opera->next)
    {
        while (opera)
        {
            ok = 0;
            if (or_if == 0)
            {
                if (and_if == 0)
                {
                    if (opera->token == PIPE)
                    {
                        if (opera->prev)
                            if (opera->prev->token != PIPE)
                                i = 0;
                        if (opera->token == PIPE)
                        {
                            //Compte combien de pipe
                            i = ft_count_pipe(opera);
                            i++;
                            ret = ft_pipe(opera, i, pid);
                        }
                        while (i != 0)
                        {
                            opera = opera->next;
                            i--;
                        }
                        if (opera == NULL)
                            return ;
                        //opera = opera->next;
                        if (ret == EXIT_SUCCESS)
                        {
                            if (opera->prev->token == OR_IF)
                                or_if = 1;
                            else
                                or_if = 0;
                            ret = 0;
                        }
                        //Si echec de solver
                        else if (ret == EXIT_FAILURE)
                        {
                            if (opera->prev->token == AND_IF)
                                and_if = 1;
                            else
                                and_if = 0;
                            ret = 0;
                        }
                    }
                }
            }
            if (opera->token != PIPE)
            {
                if (or_if == 0 && i == 0)
                {
                    if (and_if == 0)
                    {
                        ret = ft_solver(opera, fd, pid, 0);
                        add_to_set("?", ft_itoa(ret));
                    }
                }
                //Si succées de solver
                if (ret == EXIT_SUCCESS)
                {
                    if (opera->token == OR_IF)
                        or_if = 1;
                    else
                        or_if = 0;
                    ret = 0;
                }
                //Si echec de solver
                else if (ret == EXIT_FAILURE)
                {
                    if (opera->token == AND_IF)
                        and_if = 1;
                    else
                        and_if = 0;
                    ret = 0;
                }
            }
            opera = opera->next;
        }
        return ;
    }
    //Command sans next donc sans séparateur dans opera(b_seq->op)
    else
    {
        ret = ft_solver(opera, fd, pid, 0);
        add_to_set("?", ft_itoa(ret));
    }
}*/
