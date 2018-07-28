/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 14:00:57 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/28 14:02:56 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		printout(t_out *arr)
{
	while (arr)
	{
		if (arr->i >= 0)
			ft_printf("L%i->%s%c", arr->ant_name,
				arr->route->route_nodes[arr->i]->name, arr->next ? ' ' : '\n');
		arr = arr->next;
	}
}

void		update_out(t_out *arr)
{
	while (arr)
	{
		if (arr->i > 0 && arr->i < arr->route->waylendth - 1)
			arr->i++;
		else
			arr->i = -1;
		arr = arr->next;
	}
}

void		push_back_out(t_out **arr, t_route *route)
{
	t_out	*new;
	t_out	*tmp;

	new = malloc(sizeof(t_out));
	new->route = route;
	new->next = 0;
	new->i = 1;
	tmp = *arr;
	new->ant_name = 1;
	if (!tmp)
	{
		*arr = new;
		return ;
	}
	while (tmp && (tmp)->next)
		tmp = (tmp)->next;
	new->ant_name = (tmp)->ant_name + 1;
	(tmp)->next = new;
}

void		free_out_struct(t_out **arr)
{
	t_out *tmp;

	while (*arr)
	{
		tmp = (*arr)->next;
		free(*arr);
		*arr = tmp;
	}
}

void		create_out(t_table *routes, int lemins)
{
	unsigned int	steps;
	int				u;
	t_out			*arr;
	int				j;
	int				global;

	arr = 0;
	u = used_routes(routes, lemins, &steps);
	global = 0;
	while (steps)
	{
		update_out(arr);
		j = -1;
		while (++j < u)
			if ((unsigned)routes->table[j]->waylendth - 1 <= steps
				&& global < lemins)
			{
				push_back_out(&arr, routes->table[j]);
				global++;
			}
		printout(arr);
		steps--;
	}
	free_out_struct(&arr);
}
