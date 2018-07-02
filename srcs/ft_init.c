/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/19 06:32:45 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/02 14:02:52 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"
int			g_chev;
static t_type		ft_parse_type(char **cmd, int chev)
{
	char			*bintest;

	if (ft_strcmp(*cmd, "cd") == 0 || ft_strcmp(*cmd, "echo") == 0 ||
			ft_strcmp(*cmd, "env") == 0 || ft_strcmp(*cmd, "setenv") == 0 ||
			ft_strcmp(*cmd, "unsetenv") == 0 || ft_strcmp(*cmd, "exit") == 0)
		return (BI);
	else if (chev == 1)
	{
		return (NONE);
	}
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

static t_token		*ft_parse_cmd(char *str, int i, int chev)
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

	token->type = (i == 0) ? ft_parse_type(&token->id, chev) : ARG;
	return (token);
}
/*
int				ft_check_parser(char **tab)
{
	int i = 0;
	int o = 0;
	int p = 0;
	int ok1, ok2, ok3, ok4;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], ";") == 0)
		{
			o = 0;
			p = 0;
		}
		if (ft_strcmp(tab[i], ">") == 0)
			o++;
		if (ft_strcmp(tab[i], "<") == 0)
			p++;
		if ((o == 1 && tab[i + 1] == '\0') || (o == 2 && tab[i + 1] == '\0'))
		{
			ok1 = 1;
			ft_putendl("Erreur near '\\n'");
			return (1);
		}
		if ((p == 1 && tab[i+  1] == '\0') || (p == 2 && tab[i + 1] == '\0'))
		{
			ok2 = 1;
			ft_putendl("Erreur near '\\n'");
			return (1);
		}
		if (o > 2)
		{
			ok3 = 1;
			ft_putendl("ERREUR near '>'");
			return (1);
		}
		if (p > 2)
		{
			ok4 = 1;
			ft_putendl("ERREUR near '<'");
			return (1);
		}
		i++;
	}
	return (0);
}*/
t_token				*ft_init(t_token *tbegin, char *cmd)
{
	t_token			*token;
	t_token			*tokenarg;
	char			*tab[100];
	int				v;
	int				chev;

	token = NULL;
	tbegin = token;
	ft_lexer(cmd, tab);
	v = 0;
	v = 0;
	chev = 0;
/*	if (ft_check_parser(tab) == 1)
		return (NULL);*/
	while (tab[v] && (v < 100))
	{
		chev = 0;
		printf("---> %s\n", tab[v]);
			if (v > 1 && ft_strcmp(tab[v], ">") != 0 && ft_strcmp(tab[v - 1], ">") == 0)
				chev = 1;
			if (v > 1 && ft_strcmp(tab[v], "<") != 0 && ft_strcmp(tab[v - 1], "<") == 0)
				chev = 1;
			if (!(token = ft_parse_cmd(tab[v], 0, chev)))
				return (NULL);
		while (tab[++v] && (v < 100))
		{
			if (ft_isbashop(tab[v][0]) || ft_isbashop(tab[v - 1][0]))
				break ;
			if (!(tokenarg = ft_parse_cmd(tab[v], 1, chev)))
				return (NULL);
			ft_token_add(&token->cmdarg, tokenarg);
		}
		ft_token_add(&tbegin, token);
	}
	ft_lexer_del(tab);
	return (tbegin);
}
