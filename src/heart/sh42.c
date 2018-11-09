/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh42.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/08 16:21:29 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/09 07:30:09 by gmadec      ###    #+. /#+    ###.fr     */
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
	history_save((char ***)NULL, line, 1, (char *)NULL);
	if ((seq = ft_parsing(lex)))
	{
		if (!(ret = extension(&seq)))
		{
			ret = ft_sequence(seq, fd_base);
			if (ret >= -255 && ret <= 256)
			{
				ft_free_b_seq(&seq);
				ft_lexer_del(&lex);
				return (ret);
			}
		}
		ft_free_b_seq(&seq);
	}
	ft_lexer_del(&lex);
	return (999);
}
void			ft_speak(int sound)
{
	pid_t pid;
	static char	*sound_hello[] = {"sh", "speak_hello.sh", NULL};
	static char	*sound_exit[] = {"sh", "speak_exit.sh", NULL};

	pid = fork();
	if (pid > 0)
		wait(0);
	else
	{
		if (sound == 1)
			execve("/bin/sh", sound_hello, g_env);
		if (sound == 2)
			execve("/bin/sh", sound_exit, g_env);
	}
}

static void		ft_print_logo(void)
{
	ft_putstr("\e[95m");
	ft_putendl(" _  _  ____      _");
	ft_putendl("| || ||___ \\ ___| |__		dzonda");
	ft_putendl("| || |_ __) / __| '_ \\		gbarnay");
	ft_putendl("|__   _/ __/\\__ \\ | | |		gmadec");
	ft_putendl("   |_||_____|___/_| |_|		jecombe");
	ft_putstr("\e[39m");
	ft_putstr("\n");
	ft_speak(1);
}

static int		shell(void)
{
	char	*cmd;
	int		ret;

	g_cmd = NULL;
	cmd = NULL;
	g_prompt = PROMPT;
	ft_print_logo();
	while (101)
	{
		ft_get_user_input(&g_prompt);
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
	ft_speak(2);
	return (ret);
}
