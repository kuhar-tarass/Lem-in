/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 14:03:35 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/28 14:06:01 by tkuhar           ###   ########.fr       */
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
	if (s[i] != '\0')
	{
		errorr("count lemins");
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
	if (*rooms == 0)
		errorr("no_rooms");
	readlinks(*rooms, s);
}

void		readlinks(t_node *rooms, char *s)
{
	char	*name1;
	char	*name2;
	t_node	*room1;
	t_node	*room2;

	while (1)
	{
		add_cache(s);
		if (s[0] != '#' && (name2 = ft_strchr(s, '-')))
		{
			*name2++ = 0;
			name1 = s;
			room1 = find_room(rooms, name1);
			room2 = find_room(rooms, name2);
			add_edge(room1, room2);
		}
		else if (s[0] != '#')
		{
			free(s);
			break ;
		}
		free(s);
		if (get_next_line(0, &s) <= 0)
			break ;
	}
}
