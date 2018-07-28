/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 14:09:44 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/28 16:13:48 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_node		*find_room(t_node *room, char *name)
{
	while (1)
	{
		if (room && room->name && !ft_strcmp(room->name, name))
			return (room);
		if (!room->next)
			break ;
		room = room->next;
	}
	return (0);
}

int			errorr(char *s)
{
	ft_printf("ERROR:	%s\n", s);
	exit(0);
	return (1);
}

void		pushf(t_node **rooms, t_node *n)
{
	check_room(*rooms, n);
	n->next = *rooms;
	*rooms = n;
}

t_node		*find_start(t_node *room)
{
	while (1)
	{
		if (room && room->es == -1)
			return (room);
		if (!room->next)
			break ;
		room = room->next;
	}
	errorr("no_start");
	return (0);
}

void		kostyl(t_route *route, int lemins)
{
	int i;

	i = 0;
	while (++i <= lemins)
		ft_printf("L%i->%s%c", i,
			route->route_nodes[1]->name, i < lemins ? ' ' : '\n');
}
