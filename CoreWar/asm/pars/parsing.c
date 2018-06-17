/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:45:52 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/14 17:39:22 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_comment_delete(char *line)
{
	char	*s;
	int		i;

	i = 0;
	if (!line)
		return (line);
	if ((s = ft_strchr(line, COMMENT_CHAR)) != NULL || \
	(s = ft_strchr(line, ';')) != NULL)
		while (s[i])
			s[i++] = ' ';
	return (line);
}

int		ft_hd_name(char *line, header_t **head, int cnt)
{
	char	*s;
	int		len;

	if ((s = ft_strstr(line, NAME_CMD_STRING)) != NULL)
	{
		if ((*head)->prog_name[0])
			ft_exit("Already a .Name", cnt);
		if ((s = ft_strchr(line, 34)) != NULL)
		{
			s++;
			if ((ft_strchr(s, 34)) != NULL)
			{
				len = 0;
				while (s[len] && s[len] != 34)
					len++;
				if (len > PROG_NAME_LENGTH)
					ft_exit("Error .Name too long", cnt);
				ft_strncpy((*head)->prog_name, s, len);
				ft_error_head_name(line, NAME_CMD_STRING, *head);
				return (1);
			}
		}
		ft_exit("Error in the .Name", cnt);
	}
	return (0);
}

int		copy_comment(header_t **head, char *s, char *line, int cnt)
{
	int	len;

	len = ft_strlen(s);
	while (s[len] && s[len] != 34)
		len++;
	(s[len] || s[len] == 34) ? len -= 1 : len;
	(len > COMMENT_LENGTH) ? ft_exit(".Comment too long", cnt) : 0;
	if (!(*head)->comment[0])
		ft_error_head_name(line, COMMENT_CMD_STRING, *head);
	ft_strncat((*head)->comment, s, len);
	if ((*head)->magic == 0)
		ft_strcat((*head)->comment, "\n");
	return (len);
}

int		save_the_comment(char *line, char *s, header_t **head, int cnt)
{
	if (s && (ft_strchr(s, 34)) != NULL)
	{
		(*head)->comment[0] ? s = line : s;
		(*head)->magic = COREWAR_EXEC_MAGIC;
		copy_comment(head, s, line, cnt);
		(*head)->comment[ft_strlen((*head)->comment) - 1] = '\0';
		return (1);
	}
	else
	{
		(!s) ? s = line : s;
		(*head)->magic = 0;
		copy_comment(head, s, line, cnt);
		return (1);
	}
	return (0);
}

int		ft_hd_com(char *line, header_t **head, int cnt, int len)
{
	char	*s;

	if ((s = ft_strstr(line, COMMENT_CMD_STRING)) != NULL || \
	((*head)->magic == 0 && (*head)->comment[0]))
	{
		if ((s = ft_strchr(line, 34)) != NULL || (*head)->magic == 0)
		{
			(s && !(*head)->comment[0]) ? s++ : s;
			return (save_the_comment(line, s, head, cnt));
		}
		ft_exit("Error in the .Comment can't find a comment", cnt);
	}
	return (0);
}
