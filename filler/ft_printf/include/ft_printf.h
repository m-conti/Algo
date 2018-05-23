/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:34:03 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/18 16:08:43 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <wchar.h>
# include <limits.h>
# include "libft.h"

# define BUFF_SIZE 64
# define HASH_FLAG 2
# define ZERO_FLAG 4
# define MINUS_FLAG 8
# define SPACE_FLAG 16
# define PLUS_FLAG 32
# define FIELD_WIDTH_FLAG 64
# define DOT_FLAG 128
# define L_FLAG 256
# define LL_FLAG 512
# define H_FLAG 1024
# define HH_FLAG 2048
# define J_FLAG 4096
# define Z_FLAG 8192
# define CONVERSIONS "sSpdDioOuUxXcCb%"
# define UNDEFINED -66
# define SIX_RIGHTEST_BITS 0x3f
# define FIVE_RIGHTEST_BITS 0x1f
# define FOUR_RIGHTEST_BITS 0x0f
# define THREE_RIGHTEST_BITS 0x07
# define LEFT_BIT 128
# define FOUR_LEFTEST_BITS 240
# define THREE_LEFTEST_BITS 224
# define TWO_LEFTEST_BITS 192
# define MALLOC_ERROR 1
# define INVALID_CHAR_ERROR 2
# define MAX_UNICODE_VAL 0x10ffff

typedef enum		e_position
{
	LEFT,
	RIGHT
}					t_position;

typedef struct		s_padding_spec
{
	int				size;
	char			filler;
	t_position		position;
}					t_padding_spec;

typedef struct		s_conv_spec
{
	unsigned int	flags;
	char			prefix[3];
	char			conversion;
	int				field_width;
	int				precision;
	int				len;
	int				nb_zeros_precision;
	int				error;
	t_padding_spec	padd;
}					t_conv_spec;

typedef struct		s_writer
{
	char			buf[BUFF_SIZE];
	size_t			buf_i;
	size_t			len;
}					t_writer;

int					parse_length_modifier(t_conv_spec *cs, char *str);
int					parse_precision(t_conv_spec *cs, char *str);
int					parse_field_width(t_conv_spec *cs, char *str);
int					parse_flag_field(t_conv_spec *cs, char *str);
void				*init_writer(t_writer *w);
void				print_and_empty_buf(t_writer *w);
void				memset_padding_buf(t_writer *w, t_conv_spec *cs);
void				putstr_buf(t_writer *w, char *s, int len);
void				putchar_buf(t_writer *w, char c);
void				put_precision_buf(t_writer *w, t_conv_spec *cs);
int					build_conv_spec(t_conv_spec *cs, char *str);
int					ft_printf(const char *format, ...);
void				init_conv_spec(t_conv_spec *cs);
void				build_tab_conv(void (*conversion[128])
						(t_writer*, t_conv_spec*, va_list));
void				conversion_s(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_ss(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_p(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_d_i(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_dd(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_d_i(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_o(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_oo(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_u(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_uu(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_x(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_xx(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_c(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_cc(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_b(t_writer *w, t_conv_spec *cs, va_list ap);
void				conversion_perc(t_writer *w, t_conv_spec *cs, va_list ap);
void				find_prefix(char **to_w, t_conv_spec *cs);
void				manage_precision(char **to_w, t_conv_spec *cs);
void				set_padding_spec(t_conv_spec *c);
void				print_number_and_padding(t_writer *w,
											char *to_w, t_conv_spec *cs);
void				print_nb_padd_space(t_writer *w,
											char *to_w, t_conv_spec *cs);
int					check_strong_bit(unsigned int val);
int					putwchar_str(char *to_w, wchar_t c,
											int *i_to_w, t_conv_spec *cs);
int					two_bytes(char *to_w, wchar_t c,
											int *i_to_w, int max_i_to_w);
int					three_bytes(char *to_w, wchar_t c,
											int *i_to_w, int max_i_to_w);
int					four_bytes(char *to_w, wchar_t c,
											int *i_to_w, int max_i_to_w);
char				*nullify(void);
void				putbuf_and_free(t_writer *w, char *to_w, t_conv_spec *cs);
char				*conv_s_build_to_w(t_conv_spec *cs, va_list ap);
char				*conv_ss_build_to_w(t_conv_spec *cs, va_list ap);

#endif
