/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 19:13:44 by tbehra            #+#    #+#             */
/*   Updated: 2018/06/06 19:46:55 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_to_queue(t_queue *q, int content)
{
	t_queue *queue;

	queue = q;
	while (queue->next)
		queue = queue->next;
	if (!(queue->next = (t_queue*)malloc(sizeof(t_queue))))
		error(MALLOC_ERROR);
	queue->next->room = content;
	queue->next->next = NULL;
}

t_queue	*next_element(t_queue *q)
{
	t_queue	*tmp;

	tmp = q->next;
	free(q);
	return (tmp);
}

t_queue	*create_queue(int content)
{
	t_queue	*queue;

	if (!(queue = (t_queue*)malloc(sizeof(t_queue))))
		error(MALLOC_ERROR);
	queue->room = content;
	queue->next = NULL;
	return (queue);
}

void	*free_all_queue(t_queue *queue)
{
	t_queue	*tmp;

	while (queue)
	{
		tmp = queue->next;
		free(queue);
		queue = tmp;
	}
	return (NULL);
}
