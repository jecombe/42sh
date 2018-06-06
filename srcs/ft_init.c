/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jecombe <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/05 15:50:14 by jecombe      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/06 15:23:58 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/19 06:32:45 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 15:49:55 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

static t_type		ft_parse_type(char **cmd)
{
	char			*bintest;

	if (ft_strcmp(*cmd, "cd") == 0 || ft_strcmp(*cmd, "echo") == 0 ||
			ft_strcmp(*cmd, "env") == 0 || ft_strcmp(*cmd, "setenv") == 0 ||
			ft_strcmp(*cmd, "unsetenv") == 0 || ft_strcmp(*cmd, "exit") == 0)
		return (BI);
	else if ((bintest = ft_isbin(*cmd)))
	{
		ft_strdel(cmd);
		*cmd = ft_strdup(bintest);
		ft_strdel(&bintest);
		return (ID);
	}
	else if (ft_isbashop(*cmd[0]))
		return (BASHOP);
	return (NONE);
}

static t_token		*ft_parse_cmd(char *str, int i)
{
	t_token			*token;

	if (!(token = ft_token_new()))
		return (NULL);
	if (ft_isquote(str[0]))
	{
		token->quote = str[0];
		token->id = ft_strsub(str, 1, ft_strlen(str) - 2);
	}
	else
	{
		token->id = ft_strdup(str);
	}
	token->type = (i == 0) ? ft_parse_type(&token->id) : ARG;
	return (token);
}

t_token				*ft_init(t_token *tbegin, char *cmd)
{
	t_token			*token;
	t_token			*tokenarg;
	char			*tab[100];
	int				v;

	token = NULL;
	tbegin = token;
	ft_lexer(cmd, tab);
	v = 0;
	v = 0;
	while (tab[v] && (v < 100))
	{
		if (!(token = ft_parse_cmd(tab[v], 0)))
		{
			return (NULL);
		}
		while (tab[++v] && (v < 100))
		{
			if (ft_isbashop(tab[v][0]) || ft_isbashop(tab[v - 1][0]))
			{
				break ;
			}
			if (!(tokenarg = ft_parse_cmd(tab[v], 1)))
				return (NULL);
			ft_token_add(&token->cmdarg, tokenarg);
		}
		ft_token_add(&tbegin, token);
	}
	ft_lexer_del(tab);
	return (tbegin);
}
