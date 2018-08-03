/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_search_in_historic.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/24 20:40:35 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/31 08:14:48 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/minishell.h"



static int		ft_advanced_search(char *search, char *in)
{
	size_t		i;

	i = 0;
	if (ft_strlen(search) >= ft_strlen(in))
		return (0);
	while (i < ft_strlen(search) && search[i] == in[i])
		i++;
	return (i == ft_strlen(search) ? 1 : 0);
}

static int		ft_maxsearch(t_tline *tline, t_ltab *ltab)
{
	int			i;

	i = 0;
	while (ltab->next)
	{
		if (ft_advanced_search(tline->actual, ltab->str))
		{
			tline->tmp ? ft_strdel(&tline->tmp) : 0;
			tline->tmp = ft_strdup(ltab->str);
			i++;
		}
		ltab = ltab->next;
	}
	return (i);
}

static void		ft_simplesearch(int *index, t_tline **tline)
{
	t_ltab		*ltab;
	int			i;
	int			tmp;

	ltab = NULL;
	i = ft_file_to_ltab(".historic", &ltab);
	if (i)
	{
		*index >= i ? *index = i - 1 : 0 ;
		tmp = *index;
		while (ltab->next && tmp >= 1)
		{
			ltab = ltab->next;
			tmp--;
		}
		(*tline)->tmp ? ft_strdel(&(*tline)->tmp) : 0;
		(*tline)->tmp = ft_strdup(ltab->str);
		//
		(*tline)->x_max = (int)ft_strlen((*tline)->tmp);
		(*tline)->x_instr = (int)ft_strlen((*tline)->tmp);
		//temporaire !
		(*tline)->x_inline = (int)ft_strlen((*tline)->tmp);
	}
}

static void		ft_manage_advanced_search(t_tline **tline, int *index)
{
	int			i;
	t_ltab		*ltab;
	int			tmp;

	ltab = NULL;
	i = ft_file_to_ltab(".historic", &ltab);
	if (i)
	{
		i = ft_maxsearch((*tline), ltab);
		*index >= i ? *index = i - 1 : 0 ;
		tmp = *index;
		while (ltab && tmp >= 0)
		{
			if (ft_advanced_search((*tline)->actual, ltab->str))
			{
				(*tline)->tmp ? ft_strdel(&(*tline)->tmp) : 0;
				(*tline)->tmp = ft_strdup(ltab->str);
				//
				(*tline)->x_max = (int)ft_strlen((*tline)->tmp);
				(*tline)->x_instr = (int)ft_strlen((*tline)->tmp);
				//temporaire !
				(*tline)->x_inline = (int)ft_strlen((*tline)->tmp);
				tmp--;
			}
			ltab = ltab->next;
		}
	}
}

void			ft_manage_historic(int *index, t_tline **tline, int version)
{
	t_ltab		*ltab;
	int			cmptr;

	cmptr = 0;
	ltab = NULL;
//	printf("\n\rtmp == %s actual == %s\r\n", (*tline)->tmp, (*tline)->actual);
	if (((*tline)->actual || (*tline)->tmp) && (*tline)->x_instr > 0)
//	if (((*tline)->x_max > 0 && (*tline)->x_instr == (*tline)->x_max))
	{
		tputs(tgoto(tgetstr("LE", NULL), 0, (int)ft_strlen((*tline)->tmp ?
		(*tline)->tmp : (*tline)->actual)), 1, ft_outc);
	}
	ft_putstr("\E[0J");
//	ft_putstr("INDEX == ");
//	ft_putendl(ft_itoa(*index));
	if (version == 1 && *index == -1)
	{
//		printf("\n\rIIIIINNNNNNDEEEXXXX ======= ----11111\n\r");
		(*tline)->tmp ? ft_strdel(&(*tline)->tmp) : 0;
	}
	else
	{
		if (!(*tline)->actual)
			ft_simplesearch(&(*index), &(*tline));
		else
			ft_manage_advanced_search(&(*tline), &(*index));
	}
	ft_putstr((*tline)->tmp ? (*tline)->tmp : (*tline)->actual);
}
