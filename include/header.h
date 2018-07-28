/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 21:46:51 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/28 14:19:39 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "get_next_line.h"
# include "libft.h"

typedef struct			s_node
{
	char				*name;
	int					x;
	int					y;
	struct s_node		*next;
	struct s_node		**edges;

	int					nedges;
	char				es;
	int					visited;
}						t_node;

typedef struct			s_cache
{
	char				*s;
	struct s_cache		*next;
}						t_cache;

typedef struct			s_route
{
	struct s_node		**route_nodes;
	int					waylendth;
}						t_route;

typedef struct			s_table
{
	t_route				**table;
	int					n;
}						t_table;

typedef struct			s_queue
{
	struct s_node		*room;
	struct s_route		*route;
	struct s_queue		*next;

}						t_queue;

typedef struct			s_used_rooms
{
	struct s_node		*room;
	struct s_used_rooms	*next;
}						t_used_rooms;

typedef struct			s_map
{
	int					wayid;
	struct s_map		*next;
	int					map_score;
	int					lemins;
}						t_map;

typedef struct			s_out
{
	int					ant_name;
	int					i;
	struct s_route		*route;
	struct s_out		*next;
}						t_out;

t_cache		*g_input;
t_node		*find_room(t_node *room, char *name);
int			errorr(char *s);

void		print_cache(void);
void		add_cache(char *s);
void		printout(t_out *arr);
void		update_out(t_out *arr);
void		push_back_out(t_out **arr, t_route *route);
void		free_out_struct(t_out **arr);
void		create_out(t_table *routes, int lemins);
int			countlemins(void);
void		read_rooms(t_node **rooms);
void		readlinks(t_node *rooms, char *s);
t_node		*create_room(char *s, char es);
void		pushf(t_node **rooms, t_node *n);
void		valid(t_node *rooms);
void		check_room(t_node *rooms, t_node *n);
void		queue_pushback(t_queue **queue, t_node *room, t_route *route);
void		breadth_search(t_queue *queue, t_table *route);
int			check_next(t_node *next, t_route *way);
int			is_visited(t_queue *elem);
t_route		*update_way(t_node *cur, t_route *way);
void		add_to_route_table(t_table *routes, t_route *way);
int			used_routes(t_table *routes, int lemins, unsigned int *steps);
t_node		*find_start(t_node *room);
void		kostyl(t_route *route, int lemins);

#endif
