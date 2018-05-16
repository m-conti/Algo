/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 18:05:33 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/03 18:25:48 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_whitespaces(char const *str)
{
	unsigned int	ret;
	size_t			i;

	ret = 0;
	i = 0;
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			&& str[i] != '\0')
		i++;
	ret += i;
	if (str[i] != '\0')
	{
		i = ft_strlen(str) - 1;
		while (i > ret && (str[i] == ' ' ||
			str[i] == '\n' || str[i] == '\t'))
		{
			i--;
			ret++;
		}
	}
	return (ret);
}

char				*ft_strtrim(char const *str)
{
	char			*ret;
	size_t			i;
	size_t			j;
	unsigned int	nb_whitespaces;

	if (!str)
		return (NULL);
	nb_whitespaces = count_whitespaces(str);
	ret = ft_strnew(ft_strlen(str) - nb_whitespaces);
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			&& str[i] != '\0')
		i++;
	while (j < (ft_strlen(str) - nb_whitespaces))
	{
		ret[j] = str[i + j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
