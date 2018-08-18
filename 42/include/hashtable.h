/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hashtable.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/17 04:39:54 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/17 06:30:25 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "../libft/include/libft.h"

#define MAX 100

typedef struct			s_hashcase
{
	int					hits;
	char				*command;
	struct s_hashcase	*next;
}						t_hashcase;

typedef struct			s_hashtable
{
	int					key;
	t_hashcase			*hashcase;
}						t_hashtable;

/*
*******************************************************************************
							ft_hashtable.c
*******************************************************************************
*/

void					ft_hashtable(char *cmd, char *raccmd);
int						ft_hash(const char *cmd);
void					ft_hash_print(t_hashtable *hashtable);


/*
*******************************************************************************
							ft_hashtable_manage.c
*******************************************************************************
*/

t_hashtable				*ft_hashtable_create(void);
t_hashcase				*ft_create_case(const char *cmd);
void					ft_save_hash(t_hashtable **hashtable);
void					ft_hash_add(t_hashcase **begin, t_hashcase *hashcase);

#endif
