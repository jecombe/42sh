/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   separate.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/14 13:00:53 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/08/14 14:35:43 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/heart.h"

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
			//***************** Si il y a un PIPE ******************************//
			if (or_if == 0)
			{
				if (and_if == 0)
				{
			if (opera->token == PIPE)
			{
				//Si il y a un PIPE alors le compteur revient a 0;
				if (opera->prev)
					if (opera->prev->token != PIPE)
						i = 0;
				if (opera->token == PIPE)
				{
					//Compte combien de pipe
					i = ft_count_pipe(opera);
					//Execute les command, en boucle sur opera tant au'il y  a des pipes
					ret = ft_pipe(opera, i, pid);
				}
				while (i != 0)
				{
					opera = opera->next;
					i--;
				}
				if (opera->next)
					opera = opera->next;
				else
					ok = 1;
				if (ret == EXIT_SUCCESS)
				{
					//****Si ||*******//
					if (opera->prev)
					{
						if (opera->prev->token == OR_IF)
							or_if = 1;
						else
							or_if = 0;
						ret = 0;
					}
				}
				//Si echec de solver
				else if (ret == EXIT_FAILURE)
				{
					//****Si &&****//
					if (opera->prev->token == AND_IF)
						and_if = 1;
					else
						and_if = 0;
					ret = 0;
				}
				if (ok == 0)
					if (or_if == 0)
					{
						if (and_if == 0)
							ret = ft_solver(opera, fd, pid);
					}
				if (ret == EXIT_SUCCESS)
				{
					//****Si ||*******//
					if (opera->token == OR_IF)
						or_if = 1;
					else
						or_if = 0;
					ret = 0;
				}
				//Si echec de solver
				else if (ret == EXIT_FAILURE)
				{
					//****Si &&****//
					if (opera->token == AND_IF)
						and_if = 1;
					else
						and_if = 0;
					ret = 0;
				}
			}
				}
			}
			//***********************************************************************//
			if (opera->token != PIPE)
			{
				//******************* Si pas de PIPE ***********************************//
				//***********************************************************************//
				//Condition si or_if(||) et and_if(&&) sont present ou non
				if (or_if == 0 && i == 0)
				{
					if (and_if == 0)
						ret = ft_solver(opera, fd, pid);
				}
				//Si succées de solver
				if (ret == EXIT_SUCCESS)
				{
					//****Si ||*******//
					if (opera->token == OR_IF)
						or_if = 1;
					else
						or_if = 0;
					ret = 0;
				}
				//Si echec de solver
				else if (ret == EXIT_FAILURE)
				{
					//****Si &&****//
					if (opera->token == AND_IF)
						and_if = 1;
					else
						and_if = 0;
					ret = 0;
				}
			}
			//**************************************************************************//
			opera = opera->next;
		}
		return ;
	}
	//Command sans next donc sans séparateur dans opera(b_seq->op)
	else
		ft_solver(opera, fd, pid);
}
