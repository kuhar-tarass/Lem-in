/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 14:03:35 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/28 22:29:14 by tkuhar           ###   ########.fr       */
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
	while (s[i] && ft_isdigit(s[i]) && lemins >= 0)
		lemins = lemins * 10 + s[i++] - 48;
	if (s[i] != '\0' || lemins < 1)
		errorr("number of lemins");
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
		s = 0;
	}
	*rooms == 0 ? errorr("no_rooms") : 0;
	es != 0 ? errorr("bad value after comand") : 0;
	readlinks(*rooms, s);
}

int			link_rooms(t_node *rooms, char *s)
{
	char	*name1;
	char	*name2;
	t_node	*r1;
	t_node	*r2;

	name1 = s;
	if (s[0] == '#')
		return (0);
	if (!(name2 = ft_strchr(s, '-')))
		return (1);
	*name2++ = 0;
	r1 = find_room(rooms, name1);
	r2 = find_room(rooms, name2);
	r1 && r2 ? add_edge(r1, r2) : 0;
	*(--name2) = '-';
	if (!r1 || !r2 || r2 == r1)
		return (1);
	else
		return (0);
}

void		readlinks(t_node *rooms, char *s)
{
	while (s)
	{
		if (link_rooms(rooms, s))
		{
			free(s);
			break ;
		}
		if (!ft_strcmp(s, "##start") || !ft_strcmp(s, "##end"))
			errorr("wrong comand in links");
		add_cache(s);
		free(s);
		s = 0;
		if (get_next_line(0, &s) <= 0)
			break ;
	}
}
