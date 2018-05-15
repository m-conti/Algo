/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 18:29:41 by tbehra            #+#    #+#             */
/*   Updated: 2018/04/06 14:01:38 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	add_word(char *str, char **ret, int word_number, char c)
{
	int i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	if ((ret[word_number] = (char *)malloc(sizeof(char) * (i + 1))))
	{
		i = 0;
		while (str[i] != c && str[i] != '\0')
		{
			ret[word_number][i] = str[i];
			i++;
		}
		ret[word_number][i] = '\0';
		return (1);
	}
	else
		return (0);
}

static int	count_words(char *str, char c)
{
	int in_c;
	int word_number;
	int i;

	word_number = 0;
	in_c = 1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			in_c = 1;
		if (str[i] != c && in_c)
		{
			in_c = 0;
			word_number++;
		}
	}
	return (word_number);
}

static int	build_ret_array(char **ret, char *s_cp, char c)
{
	int i;
	int word_number;
	int	in_c;

	i = -1;
	word_number = 0;
	in_c = 1;
	while (s_cp[++i])
	{
		if (s_cp[i] == c)
			in_c = 1;
		if (s_cp[i] != c && in_c)
		{
			in_c = 0;
			if (!(add_word(&(s_cp[i]), ret, word_number, c)))
				return (0);
			word_number++;
		}
	}
	ret[word_number] = NULL;
	return (1);
}

char		**ft_strsplit(char const *s, char c)
{
	int		word_number;
	char	**ret;
	char	*s_cp;

	if (s == NULL || s[0] == '\0')
	{
		if (!(ret = (char **)malloc(sizeof(char *))))
			return (NULL);
		if (!(ret[0] = (char *)malloc(sizeof(char))))
			return (NULL);
		ret[0] = NULL;
		return (ret);
	}
	if (!(s_cp = ft_strnew(ft_strlen(s))))
		return (NULL);
	if (!(s_cp = ft_strcpy(s_cp, s)))
		return (NULL);
	word_number = count_words(s_cp, c);
	if (!(ret = (char **)malloc(sizeof(char *) * (word_number + 1))))
		return (NULL);
	if (!(build_ret_array(ret, s_cp, c)))
		return (NULL);
	return (ret);
}
