/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 20:10:07 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/28 14:57:41 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			main(void)
{
	int		lemins;
	t_node	*rooms;
	t_table	*routes;
	t_queue	*queue;

	if (read(0, 0, 0) < 0)
		errorr("bad fd");
	rooms = 0;
	g_input = 0;
	lemins = countlemins();
	read_rooms(&rooms);
	valid(rooms);
	routes = (t_table *)malloc(sizeof(t_table));
	routes->table = 0;
	routes->n = 0;
	queue = 0;
	queue_pushback(&queue, find_start(rooms), 0);
	breadth_search(queue, routes);
	print_cache();
	if (routes->table[0]->waylendth == 2)
		kostyl(routes->table[0], lemins);
	else
		create_out(routes, lemins);
	return (0);
}
