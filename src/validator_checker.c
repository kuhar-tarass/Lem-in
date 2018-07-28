/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 14:10:55 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/28 14:47:28 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			check_next(t_node *next, t_route *way)
{
	int		i;

	i = -1;
	if (next->visited)
		return (0);
	while (way && ++i < way->waylendth)
		if (way->route_nodes[i] == next || way->route_nodes[i]->visited)
			return (0);
	return (1);
}

int			is_visited(t_queue *elem)
{
	int i;
	int j;

	j = elem->route->waylendth - 1;
	if (elem->room->visited == 1)
		return (1);
	i = 0;
	while (++i < j)
		if (elem->route->route_nodes[i]->visited)
			return (1);
	return (0);
}

void		valid(t_node *rooms)
{
	int count_start;
	int count_end;

	count_start = 0;
	count_end = 0;
	while (rooms)
	{
		if (rooms->es == -1)
			count_start++;
		if (rooms->es == 1)
			count_end++;
		rooms = rooms->next;
	}
	if (count_end != 1)
		errorr("multiply end");
	if (count_start != 1)
		errorr("multiply start");
}

void		check_room(t_node *rooms, t_node *n)
{
	while (rooms)
	{
		if (!ft_strcmp(rooms->name, n->name))
			errorr("redefinition room");
		if (rooms->x == n->x && rooms->y == n->y)
			errorr("double definition");
		rooms = rooms->next;
	}
}
