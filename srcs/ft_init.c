/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/19 06:32:45 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/12 13:33:43 by jecombe     ###    #+. /#+    ###.fr     */
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
	while (tab[v] && (v < 100))
	{
			if (v > 1 && ft_strcmp(tab[v], ">") != 0 && ft_strcmp(tab[v - 1], ">") == 0)
				chev = 1;
			if (v > 1 && ft_strcmp(tab[v], "<") != 0 && ft_strcmp(tab[v - 1], "<") == 0)
				chev = 1;
			else
				chev = 0;
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
