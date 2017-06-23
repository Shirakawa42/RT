/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 17:25:47 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/10 11:15:22 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <inttypes.h>

# define BUFF_SIZE 64

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

int				ft_atoi(const char *str);
int				ft_atoi_b(const char *str, int b);
long			ft_atol(const char *str);
int				ft_getnbr(char const *s);
void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
char			*ft_itoa(int n);
char			*ft_itoa_b(int n, int b);
void			ft_lstadd(t_list **alst, t_list *new);
t_list			*ft_lstaddl(t_list **begin, t_list *elem);
size_t			ft_lstcount(t_list *lst);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone_i(t_list **lst);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(void const *content, size_t content_size);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t ni);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_memdel(void **ap);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
long			ft_power(int nb, char p);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
void			ft_realloc(void **ptr, size_t size, size_t new_size);
char			*ft_realloc_p(char **s, size_t new_size);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
void			ft_strclr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
void			ft_strdel(char **as);
char			*ft_strdup(const char *s1);
int				ft_strequ(char const *s1, char const *s2);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t n);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
char			*ft_strrchr(const char *s, int c);
char			**ft_strsplit(char const *s, char c);
char			*ft_strstr(const char *s1, const char *s2);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				get_next_line(int const fd, char **line);

typedef struct	s_flag
{
	char	conv;
	int		type;
	int		prec;
	int		chmp;
	char	*fflg;
	int		size;
}				t_flag;

t_flag			ptf_flag_parkour(char const *f, t_flag flag, va_list arg);
struct s_flag	split_flag(char const *f, va_list arg);
int				ptf_conv(t_list **b, va_list arg, t_flag flag);
char			*conv_di(va_list arg, t_flag flag);
char			*conv_oux(va_list arg, t_flag flag);
char			*conv_s(va_list arg, t_flag flag);
t_list			*conv_c(va_list arg, t_flag flag);
char			*conv_p(va_list arg, t_flag flag);
char			*conv_else(t_flag flag);
void			ptf_prec_nbr(char **ret, t_flag flag, int len, int sign);
void			ptf_chmp(char **ret, t_flag flag, int len, int sign);
char			*split_utf8(unsigned int c);
int				ft_printf(const char *restrict format, ...);

#endif
