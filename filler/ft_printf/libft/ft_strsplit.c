/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 23:05:16 by mconti            #+#    #+#             */
/*   Updated: 2018/04/04 23:05:18 by mconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	int				split;
	unsigned int	i;
	unsigned int	j;
	char			**tab;

	if (!s || !(tab = (char**)ft_memalloc(sizeof(char*) *
		(ft_countsep(s, c) + 2))))
		return (NULL);
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i] && s[i] != c)
		{
			if ((split = ft_index(&s[i], (int)c)) < 0)
				split = (int)ft_strlen(&s[i]);
			if (!(tab[j] = (char*)ft_memalloc(split + 1)))
				return (tab = (char**)ft_tabdel((void**)tab, j));
			ft_strccpy(tab[j++], &s[i], c);
			i += split;
		}
	}
	return (tab);
}
