/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/12 20:16:54 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/23 07:00:07 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "get_next_line.h"
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define BLACKB    "\033[1;30m"
# define REDB      "\033[1;31m"
# define GREENB    "\033[1;32m"
# define YELLOWB   "\033[1;33m"
# define BLUEB     "\033[1;34m"
# define PURPLEB   "\033[1;35m"
# define CYANB     "\033[1;36m"
# define GREYB     "\033[1;37m"

# define BLACK    "\033[0;30m"
# define RED      "\033[0;31m"
# define GREEN    "\033[0;32m"
# define YELLOW   "\033[0;33m"
# define BLUE    "\033[0;34m"
# define PURPLE   "\033[0;35m"
# define CYAN     "\033[0;36m"
# define GREY     "\033[0;37m"

# define STOP "\033[0;m"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_bzero(void *s, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *s, int c, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
char				*ft_strdup_free(char *s1, char *to_free);
size_t				ft_strlen(const char *s);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needlee,
		size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isblank(int c);
int					ft_isspace(int c);
int					ft_atoi(const char *nptr);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t len);
int					ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *s));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(const char *s, char (*f)(char));
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char				*ft_strtrim(const char *s);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strjoin_free(char *s1, char *s2);
int					ft_putchar(int c);
void				ft_geoprintf(char *buff, const char *s, ...);
int					ft_putstr(const char *s);
void				ft_putendl(const char *s);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(const char *s, int fd);
int					ft_strequ(const char *s1, const char *s2);
int					ft_strnequ(const char *s1, const char *s2, size_t n);
char				**ft_strsplit(const char *s, char c);
size_t				ft_wordcount(const char *s, char c);
size_t				ft_wordlen(const char *s, char c, size_t i);
char				*ft_itoa(int n);
char				*ft_strrev(char *str);
t_list				*ft_lstnew(const void *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
size_t				ft_nbrlen(int n);
void				ft_stradel(char ***array);
int					ft_tabdel(char ***grid);
int					ft_malloc_cmd(char ***cmd, char *new_arg);
int					ft_tablen(char **grid);
char				**ft_tabdup(char **grid);
char				*ft_getenv(char *str, char **env);
int					ft_strdel_in_tab(char ***tablo, int index);
int					ft_str_isalnum(char *str);
int					ft_str_isblank(char *str);
void				ft_putstr_color(char const *s, int nb, int fd);
int					ft_isquote(char c);
int					ft_strreplace(char ***tablo, int index, char *by);
int					ft_add_str_at(char ***tablo, char *str, int at);
int					ft_insert_char_in_str(char **str, char c, int at);
int					ft_add_to_str(char **str, char c, int index);
int					ft_reverse_tab(char ***tablo);
int					ft_strisdigit(char *str);
int					ft_concat_tab_to_str(char **tablo, char **str);
int					ft_addstrtostrat(char **str, char *to_add, int at);
int					ft_chardel_at(char **str, int at);

#endif
