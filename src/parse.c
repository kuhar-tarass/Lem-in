/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 14:03:35 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/28 17:41:33 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			countlemins(void)
{
	char	*s;
	int		lemins;
	int		i;

	lemins = 0;
	i = 0;
	while (get_next_line(0, &s) > 0)
	{
		add_cache(s);
		if (s[i] != '#')
			break ;
		free(s);
	}
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
		lemins = lemins * 10 + s[i++] - 48;
	if (s[i] != '\0' || lemins < 1)
	{
		errorr("number of lemins");
	}
	free(s);
	return (lemins);
}

void		read_rooms(t_node **rooms)
{
	char	*s;
	char	es;

	es = 0;
	while (get_next_line(0, &s) > 0 && !ft_strchr(s, '-'))
	{
		if (s[0] == '#' && !ft_strcmp(s, "##start"))
			es = !es ? -1 : errorr("start room");
		else if (s[0] == '#' && !ft_strcmp(s, "##end"))
			es = !es ? 1 : errorr("end room");
		if (s[0] != '#')
		{
			pushf(rooms, create_room(s, es));
			es = 0;
		}
		add_cache(s);
		free(s);
	}
	*rooms == 0 ? errorr("no_rooms") : 0;
	es != 0 ? errorr("bad value after comand") : 0;
	readlinks(*rooms, s);
}

void		readlinks(t_node *rooms, char *s)
{
	char	*name2;
	t_node	*room1;
	t_node	*room2;

	while (1 || (room1 = 0))
	{
		room2 = 0;
		if (s[0] != '#' && (name2 = ft_strchr(s, '-')))
		{
			*name2++ = 0;
			room1 = find_room(rooms, s);
			room2 = find_room(rooms, name2);
			room1 && room2 ? add_edge(room1, room2) : 0;
			*(--name2) ? 1 : (*name2 = '-');
		}
		if (!room1 || !room2 || (s[0] != '#' && *name2 != '-'))
		{
			free(s);
			break ;
		}
		add_cache(s);
		free(s);
		if (get_next_line(0, &s) <= 0)
			break ;
	}
}
