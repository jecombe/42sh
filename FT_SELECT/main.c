/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/01 04:22:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/09 22:21:53 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "includes/ft_select.h"

static int		ft_print_final(t_select **t)
{
	t_line		*tmp;
	int			i;

	i = 1;
	tputs(tgetstr("cd", NULL), 1, ft_outc);
	if (*t)
	{
		while ((*t)->select_max >= i)
		{
			tmp = (*t)->line;
			while (tmp)
			{
				if (tmp->select == i)
				{
					if (i > 1)
						ft_putchar(' ');
					ft_putstr(tmp->elem);
					i++;
				}
				tmp = tmp->next;
			}
		}
	}
	return (0);
}

static int		ft_refresh(t_select *t, int ret, t_ws verif)
{
	if (((ret == 0 || verif.ws_col != t->ws.ws_col)) ||
	g_sign == 1 ||
	t->ws.ws_row != verif.ws_row)
		return (t->bp > t->ws.ws_col ? 2 : 1);
	return (0);
}

int				ft_test(t_select **sel, int ret)
{
	char		*entry;
	t_ws		verif;
	int			refresh;

	refresh = 0;
	entry = NULL;
	ft_get_size_term(&verif, &(*sel), 2);
	while ((*sel && ret != 4) || ret == 0)
	{
		ft_get_size_term(&(*sel)->ws, &(*sel), 2);
		refresh = ft_refresh((*sel), ret, verif);
		if (refresh == 1)
		{
			g_sign = 0;
			ft_get_size_term(&verif, &(*sel), 2);
			ft_print_params(&(*sel));
		}
		refresh == 2 ? ft_putstr_fd("\E[0J", 2) : 0;
		ret = ft_manage_entry(&entry, &(*sel));
		entry ? ft_strdel(&entry) : 0;
	}
	return (0);
}

t_rep	*ft_free_node(t_rep *rep)
{
	t_rep *tmp;

	if (!rep)
		return (NULL);
	tmp = rep->next;
	free(rep);
	rep = NULL;
	return (tmp);
}

char	**list_to_tab(int size, t_rep *begin)
{
	char **rep;
	int i;

	i = 0;
	rep = (char**)malloc(sizeof(char*) * size);
	rep[size] = NULL;
	while (begin->next)
	{
		rep[i++] = ft_strdup(begin->d_name);
		begin = ft_free_node(begin);
	}
	return (rep);
}

char	**ft_directory_content(void)
{
	DIR			*dir;
	t_dirent	*rep;
	t_rep		*begin;
	t_rep		*to_add;
	t_rep		*now;
	int			count;

	count = 0;
	begin = NULL;
	now = NULL;
	to_add = NULL;
	dir = opendir(".");
	while ((rep = readdir(dir)))
	{
		if (rep->d_name[0] != '.')
		{
			to_add = (t_rep*)malloc(sizeof(t_rep));
			to_add->next = NULL;
			if (now)
				now->next = to_add;
			now = to_add;
			ft_strcpy(now->d_name, rep->d_name);
			begin = !begin ? to_add : begin;
			count++;
		}
	}
	return (list_to_tab(count, begin));
}

int				main(void)
{
	t_select	*sel;
	int			ret;
	t_ws		verif;
	char	**rep;

	rep = ft_directory_content();
	ret = 0;
	g_sign = 1;
	ft_enable_raw(&sel);
	ft_signal();
	ft_init_select(&sel, rep);
	ft_get_size_term(&verif, &sel, 2);
	ft_test(&sel, ret);
	return (ft_print_final(&sel) + ft_disable_raw(0, &sel));
}
