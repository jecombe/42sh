/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/27 05:17:53 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 05:27:01 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tabulator.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/01 10:16:39 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 05:17:49 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/stdin.h"

char	**recup_files(DIR *dir)
{
	char **files;
	t_dirent *rep;

	files = NULL;
	while ((rep = readdir(dir)))
	{
		if (ft_strcmp(rep->d_name, "..") && ft_strcmp(rep->d_name, "."))
		{
			ft_malloc_cmd(&files, rep->d_name);
		}
	}
	return (files);
}

void	tabulator(t_editor *ed)
{
	int nb_line;
	int line_end;
	int line_end_save;
	DIR *dir;
//	t_dirent *rep;
//	char dir_cur[4096];
	int pos[2];

	line_end = ed->cursor_str_pos;
	pos[0] = get_cursor_position(0);
	pos[1] = get_cursor_position(1);
	if ((ed->last_row - get_cursor_position(1)) != 0)
		tputs(tgoto(tgetstr("DO", NULL), 0,
		ed->last_row - get_cursor_position(1)), 1, ft_putchar);
	//printf("line_end: %d", line_end);
	line_end_save = line_end;
	if (line_end)
		while (line_end >= 0)
		{
			if ((ed->line[line_end] || !ed->line[line_end]) && ed->line[line_end - 1] == ' ')
			{
				dir = opendir(".");
				ft_select(recup_files(dir), &nb_line, pos);
				/*
				while ((rep = readdir(dir)))
				{
					if (ft_strcmp(rep->d_name, "..") && ft_strcmp(rep->d_name, "."))
					printf("name1: [%s]\n", rep->d_name);
				}*/
				closedir(dir);
				return ;
			}
			/*
			else if (ed->line[line_end] && ed->line[line_end - 1] == ' ')
			{
				printf("edOK\n");
				if ((dir = opendir(ed->line + line_end)))
				while ((rep = readdir(dir)))
				{
					if (ft_strcmp(rep->d_name, "..") && ft_strcmp(rep->d_name, "."))
					printf("name2: [%s]\n", rep->d_name);
				}
				else
					while (line_end_save >= line_end)
					{
						ft_bzero(dir_cur, sizeof dir_cur);
						ft_strncpy(dir_cur, ed->line + line_end, line_end_save - line_end);
						if ((dir = opendir(dir_cur)))
						{
							ft_strcpy(dir_cur, ed->line + line_end_save);
							while ((rep = readdir(dir)))
							{
								if (!ft_strncmp(dir_cur, rep->d_name, ft_strlen(dir_cur)))
								printf("name3: [%s]\n", rep->d_name);
							}
							closedir(dir);
							return ;
						}
						else if (line_end_save == line_end)
						{
							dir = opendir(".");
							while ((rep = readdir(dir)))
							{
								if (!ft_strncmp(ed->line + line_end, rep->d_name, ft_strlen(ed->line + line_end)))
								printf("name4: [%s]\n", rep->d_name);
							}
						}
						line_end_save--;
					}
				return ;
			}
			if (!line_end)
			{
				while (line_end_save >= 0)
				{
					ft_bzero(dir_cur, sizeof dir_cur);
					ft_strncpy(dir_cur, ed->line + line_end, line_end_save - line_end);
						printf("dir: [%s]\n", ed->line + line_end_save );
					if ((dir = opendir(dir_cur)))
					{
						ft_strcpy(dir_cur, ed->line + line_end_save);
						while ((rep = readdir(dir)))
						{
							if (((int)ft_strlen(ed->line) == line_end_save - line_end ? !ft_strncmp(rep->d_name, dir_cur, ft_strlen(dir_cur)) : !ft_strncmp(dir_cur, rep->d_name, ft_strlen(dir_cur))) && rep->d_type == 4)
								printf("name5: [%s]\n", rep->d_name);
						}
						closedir(dir);
						return ;
					}
					else if (line_end_save == line_end)
					{
						dir = opendir(".");
						while ((rep = readdir(dir)))
						{
							if (!ft_strncmp(ed->line + line_end, rep->d_name, ft_strlen(ed->line + line_end)))
								printf("name6: [%s]\n", rep->d_name);
						}
					}
					line_end_save--;
				}
			}*/
			line_end--;
		}
}
