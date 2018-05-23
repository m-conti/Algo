/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 22:10:30 by mconti            #+#    #+#             */
/*   Updated: 2018/04/12 22:10:32 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(char *src, char c)
{
	int i;

	i = ft_index(src, c) >= 0 ? ft_index(src, c) : ft_strlen(src);
	return (ft_strndup(src, i));
}
