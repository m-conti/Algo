/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 17:01:01 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/04 13:19:06 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char*)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (ret)
		ft_strcpy(ret, src);
	return (ret);
}
