/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 21:46:51 by tkuhar            #+#    #+#             */
/*   Updated: 2018/06/09 17:15:18 by tkuhar           ###   ########.fr       */
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

typedef struct	s_node
{
	char			*name;
	int				x;
	int				y;
	struct	s_node	*next;
	struct	s_node	**edge;
	int				nedg;
	struct	s_node	***ways;
	int				nways;
	char			end;
}				t_node;

# define ERROR_NONEX_ROOM()	exit(0);

#endif