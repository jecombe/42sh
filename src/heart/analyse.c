
#include "heart.h"

char			*ft_convert_token_to_string(t_token token)
{
	static char	*tkname[] = {";", "&", ";;", "(", ")", "!", "&&", "||",
		"|", "|&", "<", "<>", ">", ">|", ">>", ">&", "<<", "<&", "<<-",
		"if", "while", "for", "until", "case", "then", "do", "esac", "fi",
		"done", "elif", "else"};
	int			value;
	int			i;
	char		*s;

	value = 265;
	i = -1;
	while (++value < 297)
	{
		++i;
		if (value == token)
			break ;
	}
	if (value == 297)
	{
		if (token == 261) s = "WORD";
		else if (token == 262) s = "ASSIGNEMENT_WORD";
		else if (token == 263) s = "NAME";
		else if (token == 264) s = "NEWLINE";
		else if (token == 265) s = "IO_NUMBER";
		else s = "TOKEN";
	}
	return (value == 297 ? s : tkname[i]);
}

void				ft_watch_result(char *line, t_lex lex, t_seq *n_seq)
{
	int				i = -1;
	t_op			*n_op;
	t_redirect		*n_redirect;

	printf("\n\n-------------- ANALYSE ---------------\n\n");
	printf("%sLINE :%s\n.%s.\n\n", RED, END, line);
	printf("%sLEXER :%s\n", RED, END);
//	while (lex.name[++i])
//		printf(".%s. .%s.\n", lex.name[i], ft_convert_token_to_string(lex.token[i]));
	printf("\n%sPARSER :%s\n", RED, END);
	while (n_seq)
	{
	//	printf("n_seq->token == %s\n", cv(n_seq->token));
		n_op = n_seq->op;
		while (n_op)
		{
		//	printf("\tn_op->token == %s\n", cv(n_op->token));
			if (n_op->cmd)
			{
				i = -1;
				while (n_op->cmd[++i])
					printf("\t\tCMD[%d] == %s\n", i, n_op->cmd[i]);
			}
			n_redirect = n_op->redirect;
			while (n_redirect)
			{
			//	printf("\t\t\tFD == %d, redirect == %s FILE == %s\n", n_redirect->fd, cv(n_redirect->redirect), n_redirect->file);
				n_redirect = n_redirect->next;
			}
			n_op = n_op->next;
		}
		ft_putchar('\n');
		n_seq = n_seq->next;
	}
	printf("--------------------------------------\n\n");

}


