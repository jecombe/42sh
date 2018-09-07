/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dewalter <dewalter@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/22 21:41:56 by dewalter     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 02:08:41 by dewalter    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t n);
int					ft_putchar(int c);
int					ft_putstr(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(const char *dst, const char *src);
char				*ft_strdup(const char *src);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_islower(int c);
int					ft_isupper(int c);
void				*ft_memalloc(size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_memdel(void **ap);
int					ft_putchar_fd(int c, int fd);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putstr_fd(char const *s, int fd);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *big, const char *little,
					size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char const *s, int fd);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_strtrim(char const *s);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strmap(char const *s, char (*f) (char));
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
char				*ft_itoa_base(int value, int base);
char				*ft_ltoa(long value);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_sort_integer_table(int *tab, int size);
int					*ft_range(int min, int max);
int					get_next_line(const int fd, char **line);
int					ft_tablen(char **tab);
char				**ft_tabdup(char **tab);
int					ft_putc(int c);
char				*ft_strjoin_free(char *s1, char *s2);
int					ft_nbrlen(int nbr);
int					ft_malloc_cmd(char ***cmd, char *new_arg);
char				*ft_strrev(char *str);
void				ft_tabdel(char ***tab);

#endif
