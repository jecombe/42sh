/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/20 05:15:40 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/20 06:42:32 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "./parsing.h"

int		main(int ac, char **av)
{
	t_lex	*now;
	t_lex	*begin;

	now = malloc(sizeof(t_lex));
	now->name = ft_strdup("ls");
	now->token = WORD;
	begin = now;
	now->next = malloc(sizeof(t_lex));
	now->name = ft_strdup("-R");
	now->token = WORD;
	now = malloc(sizeof(t_lex));
	now->name = ft_strdup(";");
	now->token = SEMI;
	now = malloc(sizeof(t_lex));
	now->name = ft_strdup("echo");
	now->token = WORD;
	now = malloc(sizeof(t_lex));
	now->name = ft_strdup("'garibaldi def efd'");
	now->token = WORD;
	now = malloc(sizeof(t_lex));
	now->name = ft_strdup("|");
	now->token = PIPE;
	now = malloc(sizeof(t_lex));
	now->name = ft_strdup(";;");
	now->token = DSEMI;
	now->next = NULL;
}
