/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 21:46:51 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/04 19:47:56 by tkuhar           ###   ########.fr       */
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


typedef struct						s_node
{
	char			*name;
	int				x;
	int				y;
	struct s_node	*next;
	struct s_node	**edge;
	int				nedg;
	struct s_node	**way;
	int				waylength;
	
	char			end;
	struct s_node	***ways;
	int				*wayslength;
	int				nways;
}									t_node;

// typedef struct						s_ways
// {
// 	struct s_node	***way;
// 	int				*waylendth;
// 	int				nways;
// }									t_ways;

// typedef struct						s_end
// {

// }

# define ERROR_NONEX_ROOM()	exit(0);

#endif