#ifndef HEART_H
# define HEART_H

#include "./include/stdin.h"
#include "./include/init.h"
#include "./include/lexer.h"
//#include "./include/parsing.h"
#include "./include/execute.h"
#include "./include/extension.h"

int		hear_of_42sh(char *line, e_prompt *prompt, int fd_base);

#endif
