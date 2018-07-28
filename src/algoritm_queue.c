/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algoritm_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 14:15:15 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/28 14:15:27 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		queue_pushback(t_queue **queue, t_node *room, t_route *route)
{
	t_queue		*tmp;
	t_queue		*wtmp;

	tmp = malloc(sizeof(t_queue));
	tmp->room = room;
	tmp->route = update_way(room, route);
	tmp->next = 0;
	if (*queue == 0)
	{
		*queue = tmp;
		return ;
	}
	wtmp = *queue;
	while (wtmp && wtmp->next)
		wtmp = wtmp->next;
	wtmp->next = tmp;
}
