/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   separate.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:00:53 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/09/17 05:01:15 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"


int			ft_separate_pipe_2(t_separate **separate, t_op **opera, pid_t pid, int fd2)
{
	if ((*opera)->prev)
		if ((*opera)->prev->token != PIPE)
			(*separate)->i = 0;
	if ((*opera)->token == PIPE)
	{
		(*separate)->i = ft_count_pipe((*opera));
		(*separate)->i++;
		(*separate)->ret = ft_pipe((*opera), (*separate)->i, fd2);
	}
	while ((*separate)->i != 0)
	{
		(*opera) = (*opera)->next;
		(*separate)->i--;
	}
	if ((*opera) == NULL)
		return (101);
	return (42);
}

int			ft_separate_pipe(t_separate *separate, t_op **opera, pid_t pid, int fd2)
{
	if (ft_separate_pipe_2(&separate, &(*opera), pid, fd2) == 101)
		return (101);

	if (separate->ret == EXIT_SUCCESS)
	{
		if ((*opera)->prev->token == OR_IF)
			separate->or_if = 1;
		else
			separate->or_if = 0;
		separate->ret = 0;
	}
	else if (separate->ret == EXIT_FAILURE)
	{
		if ((*opera)->prev->token == AND_IF)
			separate->and_if = 1;
		else
			separate->and_if = 0;
		separate->ret = 0;
	}
	return (EXIT_SUCCESS);
}


/*void			ft_separate_no_pipe(t_separate *separate, t_op *opera, pid_t pid, int fd)
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
}*/
/*
int			perform_pipe(t_op *op, int fdd)
{
	int fd[2];

	pipe(fd);
	int fd_out =  1;
	int fd_in = 0;
	int status = 0;
	char *bin = ft_search_bin(op->cmd[0]);
	if (bin != NULL)
		ft_exec_no_null(op, fd, fd_out, fd_in);
	else
		ft_print_error(op->cmd[0], "Command not found !");

}*/

void	ft_save_fd(int fd_org[3])
{
	fd_org[0] = dup(0);
	fd_org[1] = dup(1);
	fd_org[2] = dup(2);
}

void	ft_restore_fd(int fd_org[3])
{
	dup2(fd_org[0], 0);
	dup2(fd_org[1], 1);
	dup2(fd_org[2], 2);
}


static void			ft_parent_fork(t_pipe **tpipe, t_op *op)
{
	if ((*tpipe)->fd_in > 0)
		close((*tpipe)->fd_in);
	if ((*tpipe)->fd_out != 1)
		close((*tpipe)->fd_out);
	close(g_fd[1]);
	if ((*tpipe)->fd_save)
		close((*tpipe)->fd_save);
	(*tpipe)->fd_save = g_fd[0];
}


void		ft_separate(t_seq *b_seq, int fd, pid_t pid)
{
	t_op *opera;
	t_separate separate;
	t_token		token;
	int		fd_org[3];
	token = TOKEN;
	int ret = -1;
	int fdd[2];
	separate = ft_init_separate();
	opera = b_seq->op;
	g_start = ft_count_pipe(b_seq->op);
	//g_save = 0;
	while (opera)
	{
		pipe(g_fd);
		g_input = 0;
		g_output = 1;
		printf("=============+> %s\n", opera->cmd[0]);
		/*if (opera->token == PIPE)
			if (ft_separate_pipe(&separate, &opera, pid, fd) == 101)
				return ;
		if (opera->token != PIPE)
		{
			//ft_separate_no_pipe(&separate, opera, pid, fd);
			
		}*/
		/*if (token == AND_IF && ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if ()
		{
			
		}*/
		if ((token == TOKEN) || (token == PIPE) ||
				(token == AND_IF && ret == EXIT_SUCCESS) ||
				(token == OR_IF && ret == EXIT_FAILURE))
		{
		//	if (token == PIPE)
		//		perform_pipe(opera, fd);
			ft_save_fd(fd_org);
			ret = ft_solver(opera, fd, pid, 0, fdd, 0, 1);
//int			ft_solver(t_op *t_exec, int fd, pid_t pid, int save, int *fdd, int input, int output)
			token = opera->token;
			printf("\n%d\n", opera->token);
			ft_restore_fd(fd_org);
		}
		opera = opera->next;
		//g_start--;

	}
	return ;
	//else
	//{
		///pipe(g_fd);
		//separate.ret = ft_solver(opera, fd, pid, 0);
		//add_to_set("?", ft_itoa(separate.ret));
	//}
}

/*
void		ft_separate(t_seq *b_seq, int fd, pid_t pid)
{
	t_op *opera;
	t_separate separate;

	separate = ft_init_separate();
	opera = b_seq->op;
	if (opera->next)
	{
		while (opera)
		{
			if (opera->token == PIPE)
				if (ft_separate_pipe(&separate, &opera, pid, fd) == 101)
					return ;
			if (opera->token != PIPE)
			{
				pipe(g_fd);
				ft_separate_no_pipe(&separate, opera, pid, fd);
			}
			opera = opera->next;
		}
		return ;
	}
	else
	{
		pipe(g_fd);
		separate.ret = ft_solver(opera, fd, pid, 0);
		add_to_set("?", ft_itoa(separate.ret));
	}
}
*/
/*void		ft_separate(t_seq *b_seq, int fd, pid_t pid)
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
							ret = ft_pipe(opera, i, pid, fd);
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
