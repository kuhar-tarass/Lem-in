/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:06:47 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/24 19:02:01 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include <stdio.h>
# include "libft.h"
# include "ft_printf.h"

typedef struct		s_map
{
	int		player;
	int		x;
	int		y;
	short	**map;
}					t_map;

typedef struct		s_pice
{
	int		x;
	int		y;
	short	**pice;
	int		x_ins;
	int		y_ins;
}					t_pice;

t_map				*readplayer(void);
t_map				*readparam(t_map *p);
t_map				*readmap(t_map *p);
t_pice				*readpiceparam(void);
t_pice				*readpice(t_pice *p);

#endif
