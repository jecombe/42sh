/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 03:53:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/08/01 00:05:43 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/stdin.h"
#include "../include/lexer.h"
#include "../include/parsing.h"

#define cv ft_convert_token_to_string

void				ft_watch_result(char *line, t_lex lex)
{
	int				i = -1;

	printf("%sLINE :%s\n%s\n", RED, END, line);
	printf("%sLEXER : \n%s", RED, END);
	while (lex.name[++i])
		printf(".%s. .%s.\n", lex.name[i], ft_convert_token_to_string(lex.token[i]));
	printf("%s PARSER : \n", RED);
	ft_putstr(END);
}

int					ft_term_init(char **environ)
{
	char			*term;

	g_env = ft_tabdup(environ);
	if (!(term = getenv("TERM")))
		term = "xterm-256color";
	if (tgetent(NULL, term) == ERR)
		return (1);
	return (0);
}

void				ft_101sh(void)
{
	e_prompt		prompt;
	char			*line;
	t_lex			lex;

	prompt = PROMPT;
	line = NULL;
	while (get_stdin(&line, prompt))
	{
		if (line)
		{
			lex = ft_lexer(line);
		/*	ft_parser( &prompt);
			if (ft_parser)
			{
				
			}*/
			ft_watch_result(line, lex);
			ft_strdel(&line);
		}
	}
}

int					main(int ac, char *av[])
{
	extern char		**environ;

	if (ft_term_init(environ))
		return (EXIT_FAILURE);
	ft_101sh();
	return (EXIT_SUCCESS);
}
