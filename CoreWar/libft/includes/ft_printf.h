/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <mconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:48:13 by mconti            #+#    #+#             */
/*   Updated: 2018/06/19 20:26:36 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"
# include "wchar.h"
# define BUFF_SIZE 2048
# define PARAM_SIZE 2048

typedef struct		s_param
{
	char			mlg;
	char			flag;
	int				lg;
	int				pc;
	char			cast;
	char			tr;
	char			str[BUFF_SIZE + 1];
	char			strparam[PARAM_SIZE + 1];
	int				lr;
	int				lp;
	intmax_t		param;
	va_list			ap;
}					t_param;

typedef struct		s_cast
{
	intmax_t		(*cast)(va_list*);
	void			(*tr)(t_param*);
}					t_cast;

unsigned int		ft_abs(int const nb);
int					ft_printf(char *str, ...);
int					ft_wstos(wchar_t *src, char *dest);
int					ft_wctos(wchar_t c, char *dest);
int					ft_isupper(int c);
int					ft_memindex(const char *tab, char c, int len);
unsigned int		ft_log(unsigned long long nb, unsigned int const base);
unsigned int		ft_indendpar(char *str, t_param *p);
char				*ft_chflag(char *str, t_param *p, unsigned int end);
int					ft_setflag(t_param *p, int flag, char c);
void				ft_setcast(t_param *p);
int					ft_setzero(t_param *p);
void				ft_start(t_param *p);
int					ft_ltos(t_param *p);
int					ft_ltos_base(t_param *p, char *base);
void				ft_addtoprint(t_param *p, char c, int n);
void				ft_strtoprint(t_param *p, char *str, int n);
void				ft_toprint(t_param *p);
void				ft_tr_null(t_param *p);
void				ft_tr_i(t_param *p);
void				ft_tr_u(t_param *p);
void				ft_tr_o(t_param *p);
void				ft_tr_x(t_param *p);
void				ft_tr_c(t_param *p);
void				ft_tr_s(t_param *p);
void				ft_tr_p(t_param *p);
void				ft_tr_lx(t_param *p);
void				ft_tr_lc(t_param *p);
void				ft_tr_ls(t_param *p);
void				ft_tr_percent(t_param *p);
void				ft_tr_ln(t_param *p);
intmax_t			ft_cast_si(va_list *ap);
intmax_t			ft_cast_sh(va_list *ap);
intmax_t			ft_cast_sl(va_list *ap);
intmax_t			ft_cast_sj(va_list *ap);
intmax_t			ft_cast_sz(va_list *ap);
intmax_t			ft_cast_shh(va_list *ap);
intmax_t			ft_cast_sll(va_list *ap);
intmax_t			ft_cast_ui(va_list *ap);
intmax_t			ft_cast_uh(va_list *ap);
intmax_t			ft_cast_ul(va_list *ap);
intmax_t			ft_cast_uj(va_list *ap);
intmax_t			ft_cast_uz(va_list *ap);
intmax_t			ft_cast_uhh(va_list *ap);
intmax_t			ft_cast_ull(va_list *ap);
intmax_t			ft_cast_c(va_list *ap);
intmax_t			ft_cast_wc(va_list *ap);
intmax_t			ft_cast_s(va_list *ap);
intmax_t			ft_cast_ws(va_list *ap);
intmax_t			ft_cast_wild(va_list *ap);
unsigned int		ft_setlargeur(char *str, t_param *p, unsigned int i);

#endif
