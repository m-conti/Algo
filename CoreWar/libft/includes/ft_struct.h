/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 17:51:21 by mconti            #+#    #+#             */
/*   Updated: 2018/04/20 17:51:22 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCT_H
# define FT_STRUCT_H

# include "ft_printf.h"

t_cast g_ft[] =
{
	{&ft_cast_si, &ft_tr_null},
	{&ft_cast_sh, &ft_tr_i},
	{&ft_cast_sl, &ft_tr_i},
	{&ft_cast_sj, &ft_tr_u},
	{&ft_cast_sz, &ft_tr_o},
	{&ft_cast_shh, &ft_tr_x},
	{&ft_cast_sll, &ft_tr_c},
	{&ft_cast_ui, &ft_tr_s},
	{&ft_cast_uh, &ft_tr_p},
	{&ft_cast_ul, &ft_tr_ln},
	{&ft_cast_uj, &ft_tr_i},
	{&ft_cast_uz, &ft_tr_u},
	{&ft_cast_uhh, &ft_tr_o},
	{&ft_cast_ull, &ft_tr_lx},
	{&ft_cast_c, &ft_tr_lc},
	{&ft_cast_s, &ft_tr_ls},
	{&ft_cast_wc, &ft_tr_percent},
	{&ft_cast_ws, &ft_tr_null}
};

#endif
