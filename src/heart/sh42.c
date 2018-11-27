/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh42.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 16:21:29 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/24 03:11:23 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "heart.h"

int				heart_of_101sh(char *line, int fd_base)
{
	t_lex	lex;
	t_seq	*seq;
	int		ret;

	ret = 0;
	ft_memset(&lex, 0, sizeof(t_lex));
	seq = NULL;
	lex = lexer(line);
	fd_base == 1 ? history_save((char ***)NULL, line, 1, (char *)NULL) : 0;
	if ((seq = ft_parsing(lex)))
	{
		if ((ret = extension(&seq, fd_base)) >= -255 && ret <= 256)
		{
			ft_free_b_seq(&seq);
			ft_lexer_del(&lex);
			return (ret);
		}
		ft_free_b_seq(&seq);
	}
	ft_lexer_del(&lex);
	return (fd_base ? 999 : ret);
}

static void		ft_print_logo_and_init(void)
{
	g_cmd = NULL;
	g_prompt = PROMPT;
	ft_putstr(CYANB);
	ft_putendl(" _  _  ____      _");
	ft_putendl("| || ||___ \\ ___| |__		dzonda");
	ft_putendl("| || |_ __) / __| '_ \\		gbarnay");
	ft_putendl("|__   _/ __/\\__ \\ | | |		gmadec");
	ft_putendl("   |_||_____|___/_| |_|		jecombe");
	ft_putstr(STOP);
	ft_putstr("\n");
}

static int		shell(void)
{
	char	*cmd;
	int		ret;

	cmd = NULL;
	ft_print_logo_and_init();
	while (101)
	{
		ft_get_user_input(&g_prompt);
		if (g_cmd && g_prompt == PROMPT && !ft_strncmp(FT_KEY_CTRL_D, g_cmd, 4))
			return (0);
		cmd = ft_strjoin_free(cmd, g_cmd);
		ft_strdel(&g_cmd);
		if (cmd && !(g_prompt = prelexer(&cmd)))
		{
			if ((ret = heart_of_101sh(cmd, 1)) != 999)
			{
				ft_tabdel(&g_set);
				return (ret + ft_strdel(&cmd) + ft_tabdel(&g_env));
			}
			ft_strdel(&cmd);
			g_prompt = PROMPT;
		}
		cmd ? cmd = ft_strjoin_free(cmd, "\n") : 0;
	}
	return (0);
}

int				main(int ac, const char **av)
{
	int		ret;

	if (init_shell(ac, av))
	{
		ft_putstr("This shell can't run in non-interactive mode.");
		return (EXIT_FAILURE);
	}
	ret = shell();
	exit_shell();
	return (ret);
}
