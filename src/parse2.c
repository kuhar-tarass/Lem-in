/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 14:06:17 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/28 14:13:47 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_node		*create_room(char *s, char es)
{
	int			i;
	t_node		*newroom;
	char		*tmp;

	tmp = ft_strchr(s, ' ');
	i = tmp ? tmp - s : errorr("rooms position");
	newroom = malloc(sizeof(t_node));
	newroom->name = ft_strsub(s, 0, i);
	newroom->x = 0;
	while (s[++i] && s[i] >= '0' && s[i] <= '9')
		newroom->x = newroom->x * 10 + s[i] - 48;
	s[i] == ' ' ? 0 : errorr("rooms position");
	while (s[++i] && s[i] >= '0' && s[i] <= '9')
		newroom->y = newroom->y * 10 + s[i] - 48;
	s[i] == 0 ? 0 : errorr("rooms position");
	newroom->es = es;
	newroom->next = 0;
	newroom->edges = 0;
	newroom->nedges = 0;
	newroom->visited = 0;
	newroom->name[0] == 'L' ? errorr("room`s name can`t start with L") : 0;
	return (newroom);
}

void		add_edge(t_node *room1, t_node *room2)
{
	int			i;
	t_node		**newedges;

	newedges = (t_node **)malloc(sizeof(t_node *) * (room1->nedges + 2));
	newedges[room1->nedges + 1] = 0;
	newedges[room1->nedges] = room2;
	i = -1;
	while (room1->edges && ++i < room1->nedges)
		newedges[i] = room1->edges[i];
	if (room1->edges)
		free(room1->edges);
	room1->edges = newedges;
	room1->nedges++;
	newedges = (t_node **)malloc(sizeof(t_node *) * (room2->nedges + 2));
	newedges[room2->nedges + 1] = 0;
	newedges[room2->nedges] = room1;
	i = -1;
	while (room1->edges && ++i < room2->nedges)
		newedges[i] = room2->edges[i];
	if (room2->edges)
		free(room2->edges);
	room2->edges = newedges;
	room2->nedges++;
}


