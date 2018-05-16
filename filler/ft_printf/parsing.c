/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 18:50:05 by tbehra            #+#    #+#             */
/*   Updated: 2018/05/10 10:46:00 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_length_modifier(t_conv_spec *cs, char *str)
{
	char *cp_starting_point;

	cp_starting_point = str;
	if (ft_strchr("lhjz", *str))
	{
		if (*str == 'l')
		{
			cs->flags = (*(str + 1) == 'l') ?
				cs->flags | LL_FLAG : cs->flags | L_FLAG;
			str = (*(str + 1) == 'l') ? str + 1 : str;
		}
		if (*str == 'h')
		{
			cs->flags = (*(str + 1) == 'h') ?
				cs->flags | HH_FLAG : cs->flags | H_FLAG;
			str = (*(str + 1) == 'h') ? str + 1 : str;
		}
		if (*str == 'j')
			cs->flags |= J_FLAG;
		if (*str == 'z')
			cs->flags |= Z_FLAG;
		str++;
	}
	return (str - cp_starting_point);
}

int	parse_precision(t_conv_spec *cs, char *str)
{
	char *cp_starting_point;

	cp_starting_point = str;
	if (*str == '.')
	{
		str++;
		if (ft_isdigit(*str))
		{
			while (ft_isdigit(*str))
				str++;
			cs->flags |= DOT_FLAG;
			cs->precision = ft_atoi(cp_starting_point + 1);
		}
		else
			cs->precision = 0;
	}
	return (str - cp_starting_point);
}

int	parse_field_width(t_conv_spec *cs, char *str)
{
	char *cp_starting_point;

	cp_starting_point = str;
	if (ft_isdigit(*str))
	{
		while (ft_isdigit(*str))
			str++;
		cs->flags |= FIELD_WIDTH_FLAG;
		cs->field_width = ft_atoi(cp_starting_point);
	}
	return (str - cp_starting_point);
}

int	parse_flag_field(t_conv_spec *cs, char *str)
{
	char *cp_starting_point;

	cp_starting_point = str;
	while (ft_strchr("#0- +", *str))
	{
		if (*str == '#')
			cs->flags |= HASH_FLAG;
		if (*str == '0')
			cs->flags |= ZERO_FLAG;
		if (*str == '-')
			cs->flags |= MINUS_FLAG;
		if (*str == ' ')
			cs->flags |= SPACE_FLAG;
		if (*str == '+')
			cs->flags |= PLUS_FLAG;
		str++;
	}
	return (str - cp_starting_point);
}

int	build_conv_spec(t_conv_spec *cs, char *str)
{
	char *cp_starting_point;

	if (!str)
		return (0);
	init_conv_spec(cs);
	cp_starting_point = str;
	str += parse_flag_field(cs, str);
	str += parse_field_width(cs, str);
	str += parse_precision(cs, str);
	str += parse_length_modifier(cs, str);
	cs->conversion = *str;
	return (str - cp_starting_point + 1);
}
