/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algoritm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 14:14:23 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/28 14:18:28 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_route		*update_way(t_node *cur, t_route *way)
{
	t_route		*newway;
	int			i;
	int			j;

	i = way ? way->waylendth : 0;
	newway = malloc(sizeof(t_route));
	newway->route_nodes = malloc(sizeof(t_node *) * (i + 2));
	newway->route_nodes[i + 1] = 0;
	newway->route_nodes[i] = cur;
	j = -1;
	while (++j < i)
		newway->route_nodes[j] = way->route_nodes[j];
	newway->waylendth = i + 1;
	return (newway);
}

void		add_to_route_table(t_table *routes, t_route *way)
{
	int			i;
	t_route		**newtable;

	newtable = malloc(sizeof(t_route *) * (routes->n + 2));
	newtable[routes->n + 1] = 0;
	newtable[routes->n] = way;
	i = -1;
	while (++i < routes->n)
		newtable[i] = routes->table[i];
	free(routes->table);
	routes->table = newtable;
	routes->n++;
	i = 0;
	while (++i < way->waylendth - 1)
		way->route_nodes[i]->visited = 1;
}

int			used_routes(t_table *routes, int lemins, unsigned int *steps)
{
	int				used;
	int				i;
	unsigned int	tmp;

	*steps = 2147483647;
	used = 1;
	while (used <= routes->n)
	{
		tmp = 0;
		i = -1;
		while (++i < used)
			tmp += routes->table[i]->waylendth - 1;
		tmp += lemins - 1;
		tmp = tmp / used + (tmp % used ? 1 : 0);
		if (tmp > *steps)
			return (used - 1);
		*steps = tmp;
		used++;
	}
	return (used - 1);
}

void		breadth_search(t_queue *queue, t_table *route)
{
	int			i;
	t_queue		*tmp;

	while (queue)
	{
		if (queue->room->es == 1 && !is_visited(queue))
		{
			add_to_route_table(route, queue->route);
			tmp = queue->next;
			free(queue);
			queue = tmp;
			continue ;
		}
		else if (queue->room->es != 1 && !is_visited(queue) && (i = -1))
			while (++i < queue->room->nedges)
				if (check_next(queue->room->edges[i], queue->route))
					queue_pushback(&queue, queue->room->edges[i], queue->route);
		free(queue->route->route_nodes);
		free(queue->route);
		tmp = queue->next;
		free(queue);
		queue = tmp;
	}
	if (route->n == 0)
		errorr("no solution");
}