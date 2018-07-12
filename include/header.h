/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 21:46:51 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/12 13:21:33 by tkuhar           ###   ########.fr       */
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

	char 				es;
	int					nedges;

}						t_node;

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

// typedef struct			s_queue
// {
// 	struct s_node		*room;
// 	struct s_route		*route;
// 	struct s_queue		*next;

// }						t_queue;

#endif