/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_solver.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/20 12:33:01 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/07/02 15:23:44 by jecombe     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_solver_init(t_token *token, char *arg[100])
{
	t_token		*p;
	int			i;

	printf("SOLVER INIT\n");
	i = -1;
	while (arg[++i] && (i < 100))
		ft_strdel(&arg[i]);
	while (arg[i] && (i < 100))
		arg[i++] = NULL;
	p = token->cmdarg;
	arg[0] = ft_strdup(token->id);
	i = 0;
	while (p)
	{
		arg[++i] = ft_strdup(p->id);
		p = p->next;
	}
	arg[++i] = NULL;
}

static int		ft_solver_bi_error(t_token *token, char *arg[100])
{
	if (ft_strcmp(token->id, "cd") == 0 && arg[2] != NULL)
		return (ft_error_cd("", 1));
	else if (ft_strcmp(token->id, "setenv") == 0)
	{
		if (arg[1] == NULL)
			return (ft_error_env("", 1));
		else if (ft_strrchr(arg[1], '='))
			return (ft_error_env("", 2));
		else if (arg[3] != NULL)
			return (ft_error_env("", 3));
	}
	else if (ft_strcmp(token->id, "unsetenv") == 0)
		if (arg[1] == NULL)
			return (ft_error_env("", 4));
	return (0);
}

static int		ft_solver_bi(t_token *token, char *arg[100])
{
	int			i;
	printf("SOLVER INIT\n");
	if (ft_solver_bi_error(token, arg))
		return (1);
	if (ft_strcmp(token->id, "cd") == 0)
		i = ft_builtin_cd(arg[1]);
	else if (ft_strcmp(token->id, "env") == 0)
		i = ft_builtin_env();
	else if (ft_strcmp(token->id, "setenv") == 0)
		i = ft_builtin_setenv(arg[1], arg[2]);
	else if (ft_strcmp(token->id, "unsetenv") == 0)
		i = ft_builtin_unsetenv(arg[1]);
	else if (ft_strcmp(token->id, "exit") == 0)
		i = ft_builtin_exit(token, arg);
	else
		i = ft_builtin_echo(arg);
	return (i);
}
static int		ft_solver_output(t_token *token, char *arg[100], char *file, int flag)
{
	int			i;
	if (ft_solver_bi_error(token, arg))
		return (1);
	if (ft_strcmp(token->id, "cd") == 0)
		i = ft_builtin_cd_redirect(arg[1], file, flag);
	if (ft_strcmp(token->id, "env") == 0)
		i = ft_builtin_env_output(file, flag);
	/*else if (ft_strcmp(token->id, "setenv") == 0)
	  i = ft_builtin_setenv(arg[1], arg[2]);
	  else if (ft_strcmp(token->id, "unsetenv") == 0)
	  i = ft_builtin_unsetenv(arg[1]);
	  else if (ft_strcmp(token->id, "exit") == 0)
	  i = ft_builtin_exit(token, arg);*/
	if (ft_strcmp(token->id, "echo") == 0)
	{
		printf("va dns echo\n");
		i = ft_builtin_echo_output(arg, token, file, flag);
	}
	return (i);
}



static int		ft_solver_cmd(char *arg[100])
{
	pid_t		cpid;
	int			status;
	int			ret;
	char		*cmd;

	ret = 0;
	cmd = ft_strdup(arg[0]);
	ft_strdel(&arg[0]);
	arg[0] = ft_strdup(ft_strrchr(cmd, '/') + 1);
	if ((cpid = fork()) == 0)
	{
		if (execve(cmd, arg, g_env) == -1)
		{
			printf("BON\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("BON2\n");
			exit(EXIT_SUCCESS);
		}
	}
	if (cpid > 0)
	{
		printf("BON222\n");
		wait(&status);
		ret = WEXITSTATUS(status);
	}
	cmd ? ft_strdel(&cmd) : 0;
	if (ret == 1)
		return (1);
	return (0);
}

int			ft_redirect_output(t_token *tok, char *arg[100], char *file, int flag)
{
	t_token *tmptock;
	pid_t		cpid;
	int i = 1;
	char		*cmd;
	int flag2;
	int ret;

	if (flag == O_RDONLY)
		flag2 = O_RDONLY;
	else
		flag2 = O_WRONLY;
	tmptock = tok;
	cmd = ft_strdup(arg[0]);
	ft_strdel(&arg[0]);
	arg[0] = ft_strdup(ft_strrchr(cmd, '/') + 1);
	cpid = fork();
	if (cpid > 0)
		wait(0);
	else
	{
		i = 1;
		if (flag2 == O_WRONLY)
			ret = open(file, O_WRONLY | flag | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		if (flag2 == O_RDONLY)
			ret = open(file, O_RDONLY);
		if (ret == -1)
			return (0);
		if (flag2 == O_RDONLY)
			dup2(ret, 0);
		else
			dup2(ret, 1);
		execve(cmd, arg, g_env);
		close(ret);
	}
	return (0);
}

int				ft_return_flag(char *one, int dd)
{
	if (ft_strcmp(one, ">") == 0)
		return (O_APPEND);
	if (ft_strcmp(one, "<") == 0)
		return (O_RDONLY);
	if (dd == 1)
		return (O_RDONLY);
	else
		return (O_TRUNC);
}

int				ft_verif_file(t_token *tmp, int pasbon)
{
	struct stat sb;

	while (tmp)
	{
		if (ft_strcmp(tmp->id, "<") != 0 && ft_strcmp(tmp->id, ";") != 0)
		{
			if (lstat(tmp->id, &sb) == -1)
			{
				if (pasbon == 0)
					ft_error_file_directory(tmp->id);
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
/*
void		ft_solver_cmd2(char *arg[100])
{
	pid_t		cpid;
	int			status;
	int			ret;
	char		*cmd;

	ret = 0;
	cmd = ft_strdup(arg[0]);
	ft_strdel(&arg[0]);
	arg[0] = ft_strdup(ft_strrchr(cmd, '/') + 1);
	cpid = fork();
	if (cpid > 0)
		wait(&status);
	else
		execve(cmd, arg, g_env);
	cmd ? ft_strdel(&cmd) : 0;
}
*/
static int		ft_solver_cmd2(char *arg[100])
{
	pid_t		cpid;
	int			status;
	int			ret;
	char		*cmd;

	ret = 0;
	cmd = ft_strdup(arg[0]);
	ft_strdel(&arg[0]);
	arg[0] = ft_strdup(ft_strrchr(cmd, '/') + 1);
	if ((cpid = fork()) == 0)
	{
		if (execve(cmd, arg, g_env) == -1)
		{
			exit(EXIT_FAILURE);
		}
		else
		{
			exit(EXIT_SUCCESS);
		}
	}
	if (cpid > 0)
	{
		wait(&status);
		ret = WEXITSTATUS(status);
	}
	cmd ? ft_strdel(&cmd) : 0;
	if (ret == 1)
		return (1);
	return (0);
}


void	ft_read_line(int fd, char *s)
{
	char	line[100];
	char	*list[100];
	int		i;
	ssize_t	retval;

	ft_memset(line, 0, 100);
	ft_memset(list, 0, 100 * sizeof(*list));
	i = 0;
	while ((retval = read(1, line, PATH_MAX)) > 0)
	{
		if (ft_strcmp(line, s) == 0)
			break ;
		else
			list[i++] = ft_strdup(line);
		ft_memset(line, 0, 100);
	}
	i = -1;
	while (list[++i])
		write(fd, list[i], ft_strlen(list[i]));
}
/*void	ft_read_line(int fd, char *s)
{
	char	line[100];
	char	*list[100];
	char		buff[PATH_MAX];
	//char *save[100];
	int		i;
	//ssize_t	retval;
printf("---------> %s--\n", s);
	ft_memset(line, 0, 100);
	ft_memset(list, 0, 100 * sizeof(*list));
	i = 0;
	while (101)
	{
		ft_putchar('\r');
		ft_putstr("heredoc>");
		ft_bzero(buff, PATH_MAX);
		if (!(i = read(0, line, PATH_MAX)))
			break ;
		if (ft_strcmp(line, s) == 0)
		{
			printf("RESULT\n");
			break ;
		}
		else
		{
			printf("OKOKOK\n");
			list[i++] = ft_strdup(line);
		}
		ft_memset(line, 0, 100);
	}
	i = -1;
	while (list[++i])
	{
		printf("========>  %s\n", list[i]);
		write(fd, list[i], ft_strlen(list[i]));
	}
//}

	while ((retval = read(1, line, 100)) > 0)
	{
		if (!ft_strncmp(line, s, ft_strlen(line) - 1))
			break ;
		else
			list[i++] = ft_strdup(line);
		ft_memset(line, 0, 100);
	}
	if (retval == 0)
		ft_putendl("21sh: warning: here-document delimited by end-of-file");
	i = -1;
	while (list[++i])
		write(fd, list[i], ft_strlen(list[i]));
}*/



void			ft_print_new_prompt(char *file, char *exec, char **arg)
{
	//char		buff[PATH_MAX];
	int i;
	//char *save[100];
	(void)exec;
	(void)arg;
	i = 0;
	printf("ICIC\n");
	int fd[2];
	pipe(fd);
	ft_read_line(fd[1],file);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_solver_cmd2(arg);
	/*while (101)
	{
		ft_putchar('\r');
		ft_putstr("heredoc>");
		ft_bzero(buff, PATH_MAX);
		if (!(i = read(0, buff, PATH_MAX)))
			break ;
		save[i] = ft_strdup(buff);
		i++;
		if (ft_strcmp(buff, file) == 0)
		{
			printf("RESULT\n");
			ft_solver_cmd2(arg);
			return ;
		}
	}*/
}

/*int				ft_check_parse(t_token *tbegin)
{
	t_token *tmp;
	tmp = tbegin;
	while (tmp)
	{
		printf("===========>>> %s %s\n", tmp->id, tmp->cmdarg->id);
		tmp = tmp->next;
	}
	return (1);
}*/
int				ft_solver(t_token *tbegin)
{
	t_token		*token;
	int			i;
	char		*arg[100];
	int 		o;
	int ok = 0;
	int co;
	char *file;
	int flag2;
	int f;
	int exec;
	int pasbon = 0;
	int flag = 0;

	i = 0;
	o = 0;
	co = 1;
	exec = 0;
	arg[0] = NULL;
	//ft_check_parse(tbegin);
	while (tbegin)
	{
		co++;
		exec = 0;
		pasbon = 0;
		token = tbegin;
			ft_solver_init(token, arg);
		if (token->type == BI)
		{
			//conditions pour les builtins
			ok = 0;
			if (token->next != NULL)
			{
				//si il y a un chevron > ou <
				if (ft_return_flag(token->next->id, 0) == O_APPEND || ft_return_flag(token->next->id, 0) == O_RDONLY)
				{
					ok = 1;
					flag2 = ft_return_flag(token->next->id, 0);
					if (flag2 == O_RDONLY)
						f = 1;
					else
						f = 0;
					//si chevron >>
					if ((flag = ft_return_flag(token->next->next->id, f)) == O_APPEND)
						file = token->next->next->next->id;
					//si chevron <
					else if ((flag = ft_return_flag(token->next->next->id, f)) == O_RDONLY)
					{
						if (f == 1)
						{
							//si chevron <
							file = token->next->next->id;
							if (ft_verif_file(token->next->next, pasbon) == -1)
								pasbon = 1;
							//ok = 0;
						}
						else
						{
							//a gere le <<
							file = token->next->next->next->id;
							//ft_print_new_prompt();
							return (i);
						}
						exec = 1;
					}
					//si aucun chevron
					if ((flag = ft_return_flag(token->next->next->id, f)) == O_TRUNC)
						file = token->next->next->id;
					i = ft_solver_output(token, arg, file, flag);
					//--------------------------- si plusieur chevron sur une ligne----------
					if (token->next->next->next != NULL)
						if ((ft_strcmp(token->next->next->next->id, ">") == 0) || (ft_strcmp(token->next->next->next->id, "<") == 0)) 
						{
							if (ft_strcmp(token->next->next->next->id, "<") == 0)
							{
								t_token *tmpp;
								tmpp = token->next->next->next;
								if (ft_verif_file(tmpp, pasbon) == -1)
									return (i);
								else
									;
							}
							if (token->next->next->next->next->next)
							{
								t_token *tmp;
								tmp = token->next->next->next->next;
								ft_solver_init(token, arg);
								int g = 0;
								while (tmp)
								{
									g++;
									if (ft_strcmp(tmp->id, ">") != 0 && ft_strcmp(tmp->id, "<") != 0)
									{
										if (g > 0)
											ft_solver_init(token, arg);
										file = tmp->id;
										if (exec == 0)
											i = ft_redirect_output(tmp, arg, file, flag);
									}
									tmp = tmp->next;
								}
							}
							else
							{
								file = token->next->next->next->next->id;
								ft_solver_init(token, arg);
								if (exec == 0)
								{
									i = ft_redirect_output(token, arg, file, flag);
								}
							}
						}
				}
			}
			if (ok == 0)
				i = ft_solver_bi(token, arg);
		}
		//-------------------------------fin---------------------------------
		else if (token->type == ID)
		{
			//condition pour les fonction execve
			ok = 0;
			if (token->next != NULL)
			{
				if (ft_return_flag(token->next->id, 0) == O_APPEND || ft_return_flag(token->next->id, 0) == O_RDONLY)
				{
					ok = 1;
					o = 1;
					flag2 = ft_return_flag(token->next->id, 0);
					if(flag2 == O_RDONLY)
						f = 1;
					else
						f = 0;
					if ((flag = ft_return_flag(token->next->next->id, f)) == O_APPEND)
						file = token->next->next->next->id;
					if ((flag = ft_return_flag(token->next->next->id, f)) == O_RDONLY)
					{
						if (f == 1)
						{
							file = token->next->next->id;
							if (ft_strcmp(token->next->next->id,"<") == 0)
							{
								char *file2;
								char *exec;
								exec = token->id;
								file2 = token->next->next->next->id;
								ft_strcat(file2, "\n");
								ft_print_new_prompt(file2, exec, arg);
								g_heredoc = 1;
								return (i);
							
							}
							if (ft_strcmp(token->next->next->id,"<") != 0)
								if (ft_verif_file(token->next->next, pasbon) == -1)
								{
									return (i);
								}
						}
						else
							file = token->next->next->next->id;
						exec = 1;
					}
					if ((flag = ft_return_flag(token->next->next->id, f)) == O_TRUNC)
						file = token->next->next->id;
					i = ft_redirect_output(token, arg, file, flag);
					if (token->next->next->next != NULL)
						if ((ft_strcmp(token->next->next->next->id, ">") == 0) || (ft_strcmp(token->next->next->next->id, "<") == 0)) 
						{
							if (ft_strcmp(token->next->next->next->id, "<") == 0)
							{
								t_token *tmpp;
								tmpp = token->next->next->next;
								if (ft_verif_file(tmpp, pasbon) == -1)
								{
									return (i);
								}
								else
									;
							}
							if (token->next->next->next->next->next)
							{
								t_token *tmp;
								tmp = token->next->next->next->next;
								ft_solver_init(token, arg);
								int g = 0;
								while (tmp)
								{
									g++;
									if (ft_strcmp(tmp->id, ">") != 0 && ft_strcmp(tmp->id, "<") != 0)
									{
										if (g > 0)
											ft_solver_init(token, arg);
										file = tmp->id;
										if (exec == 0)
											i = ft_redirect_output(tmp, arg, file, flag);
									}
									tmp = tmp->next;
								}
							}
							else
							{
								file = token->next->next->next->next->id;
								ft_solver_init(token, arg);
								if (exec == 0)
									i = ft_redirect_output(token, arg, file, flag);
							}
						}
				}
			}
			if (ok == 0)
				i = ft_solver_cmd(arg);
		}
		else if (token->type == NONE && ok == 0)
		{
			i = ft_error_none(arg[0]);

		}
		ft_lexer_del(arg);
		tbegin = tbegin->next;
	}
	return (i);
}
