/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 03:53:04 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/30 09:57:49 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parsing.h"

#define cv ft_convert_token_to_string

void		ft_parcour_op(t_op *n_op)
{
	int		i;
	int		j = 0;
	t_redirect		*n_redirect;

	while (n_op)
	{
		i = 0;
		if (n_op->cmd)
		{
			while (n_op->cmd[i])
			{
				printf("CMD[%d] == %s\n", i, n_op->cmd[i]);
				i++;
			}
		}
		else
			printf("CMD == (NULL)\n");
		if (n_op->redirect)
		{
			n_redirect = n_op->redirect;
			i = 1;
			while (n_redirect)
			{
				j = i;
				while (j--)
					printf("\t");
				printf("n_redirect->fd == %s\n", n_redirect->fd);
				j = i;
				while (j--)
					printf("\t");
				printf("n_redirect->redirect == %s\n", cv(n_redirect->redirect));
				j = i;
				while (j--)
					printf("\t");
				printf("n_redirect->file == %s\n", n_redirect->file);
				n_redirect = n_redirect->next;
				i++;
			}
		}
		printf("TOKEN == %s\n", cv(n_op->token));
		n_op = n_op->next;
	}
}

int        ft_exec(t_op *tmp_op, char **env, char *bin_cmd)
{
	pid_t        cpid;
	int            status;
	int            ret;
	char        *cmd;

	ret = 0;
	//cmd = ft_strdup(tmp_op->cmd[0]);
	//ft_strdel(&tmp_op->cmd[0]);
	//tmp_op->cmd[0] = ft_strdup(ft_strrchr(cmd, '/') + 1);
printf("1 %s\n", tmp_op->cmd[1]);
	if ((cpid = fork()) == 0)
	{
		if (execve(bin_cmd, tmp_op->cmd, env) == -1)
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	if (cpid > 0)
	{
		wait(&status);
		ret = WEXITSTATUS(status);
	}
	if (ret == 1)
		return (1);
	return (0);
}

char *ft_avance(char *bin)
{
	bin++;
	bin++;
	bin++;
	bin++;
	bin++;
	return (bin);

}
void 			ft_get_bin(char **env)
{
	int  i = 0;
	int o = 4;
	char *bin;
	printf("get bin\n");
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			//env[i]++;
			bin = ft_strdup(env[i]);
			bin = ft_avance(bin);
			g_bin = ft_strsplit(bin, ':');
			printf("-%s-\n", g_bin[0]);
		}
		i++;
	}
}

char			*ft_search_bin(char *cmd)
{
	char *bin;
	char *tmp;
	int i = 0;
	int u = 0;
	int t = 0;
	struct stat st;
	while (cmd[u])
	{
		if (cmd[u] == '\n')
		{
			cmd[u] = '\0';
			break;
		}
		u++;
	}
	while (g_bin[i])
	{
		tmp = ft_strdup(g_bin[i]);	
		while (tmp[t])
		{
			t++;
		}
		tmp[t] = '\0';
		t = 0;
		tmp = ft_strcat(tmp, "/");
		tmp = ft_strcat(tmp, cmd);
		printf("=+=+=+=+=+ %s-\n", tmp);
		if (lstat(tmp, &st) == -1)
			;
		else
		{
			printf("yes %s\n" , tmp);
			return (tmp);
		}
		i++;
	}
	return (bin);
}
void 			ft_skip_n(char **tab)
{
	int i = 1;
	int t = 0;
	while (tab[i])
	{
		while (tab[i][t])
		{
			if (tab[i][t] == '\n')
			{
				tab[i][t] = '\0';
				t = 0;
			}
			t++;


		}
		i++;
	}
}
void 			ft_solver(t_op *tmp_op, char **env)
{
	ft_get_bin(env);
	char *tmp_bin;
	if (tmp_op->cmd[0])
	{
		ft_skip_n(tmp_op->cmd);
		tmp_bin = ft_search_bin(tmp_op->cmd[0]);
		//printf("LLLLLLLLLLLLLL %s\n", tmp_bin);
		ft_exec(tmp_op, env, tmp_bin);
	}
	while (tmp_op)
	{
		printf("==============> %s\n", tmp_op->cmd[0]);
		tmp_op = tmp_op->next;
	}
}
int			 main(int ac, char *argv[] ,char **env)
{
	t_lex	lex;
	t_seq	*b_seq;
	int		i = -1;
	char buff[2048];
	t_op *tmp_op;
	int p = 0;

	(void)ac;
	while (101)
	{
		if (!(read(0, buff, 2048)))
			break;
		lex = ft_lexer(buff);
		while (lex.name[++i])
			printf(".%s. .%s.\n", lex.name[i], ft_convert_token_to_string(lex.token[i]));
		b_seq = ft_parsing(lex);
		ft_putstr("\x1b[32m");
		printf("-------------- PARSING -------------\n");
		i = 0;
		if (b_seq->op)
		{
			tmp_op = b_seq->op;
			printf("okokokokokokokokokokokokokok\n");
		}
		while (b_seq)
		{
			printf("SEQUENCE NUMBER %d, LIST TERMINATOR == %s\n", i, ft_convert_token_to_string(b_seq->token));
			if (b_seq->op)
				ft_parcour_op(b_seq->op);
			i++;
			if (b_seq->next)
				printf("\n");
			b_seq = b_seq->next;
		}
		printf("okookokok\n");
		ft_putstr("\x1b[0m");
		ft_solver(tmp_op, env);
	}
	//	ft_free_b_seq(&b_seq);
	//	printf("B_SEQ FREE AVEC SUCCES\n");
	return (0);
}
