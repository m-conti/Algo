/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 04:15:08 by mconti            #+#    #+#             */
/*   Updated: 2018/04/05 04:15:09 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef	uint8_t		t_byte;

int					ft_atoi(char *str);
void				ft_bzero(void *s, size_t n);
unsigned int		ft_countsep(char const *s, char c);
int					ft_index(const char *s, int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_islower(int c);
int					ft_isprint(int c);
int					ft_isupper(int c);
char				*ft_itoa(long long nbr);
char				*ft_itoabase(unsigned long long nb, char *base);
void				*ft_memalloc(size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_memdel(void **ap);
void				*ft_memdup(void const *src, size_t len);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putwchar(wchar_t c);
void				ft_putwstr(const wchar_t *str);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strccpy(char *dest, const char *src, char c);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dest, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *src);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
unsigned int		ft_strlcat(char *dest, char *src, unsigned int size);
size_t				ft_strlen(char const *str);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *dest, const char *src, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strndup(const char *src, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t n);
char				*ft_strnstr(const char *src, const char *str, size_t n);
char				*ft_strrchr(const char *s, int c);
void				ft_strrev(char *str);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *src, const char *str);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
void				ft_swap(int *a, int *b);
int					ft_tolower(int c);
int					ft_toupper(int c);
unsigned int		ft_log(unsigned long long nb, unsigned int const base);
unsigned int		ft_abs(int const nb);
int					ft_power(int const nb, unsigned int const pow);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstradd(t_list *alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				**ft_tabdel(void **tab, int y);
char				*ft_strjoinfree(char *s1, char *s2, t_byte opt);
char				*ft_strcdup(char *src, char c);
char				*ft_strcut(char *src, int n);
void				ft_error(void);
int					ft_memindex(const char *tab, char c, int len);
int					ft_putcstr(char const *s, char c);
char				*ft_straddc(char *str, char c, size_t nb);
char				*ft_strcadd(char *str, char c, size_t nb);
int					ft_wctos(wchar_t c, char *dest);
int					ft_wstos(wchar_t *src, char *dest);
int					ft_wsntos(wchar_t *src, char *dest, size_t n);
size_t				ft_wstrlen(wchar_t const *str);
int					get_next_line(const int fd, char **line);

#endif
