#include "./include/header.h"
int recurs = 0;
int fd; 


void	add_to_chache(t_chahce *cache, char *s)
{
	


}

void	printroutes(t_table *routes)
{
	int i;
	int j;

	i = -1;
	while (++i < routes->n)
	{
		j = 0;
		while( ++j < (routes->table[i])->waylendth - 1)
			printf("|%3s|->", routes->table[i]->route_nodes[j]->name);
		printf("\n");
	}
	printf("total:	%i\n", routes->n); 
}

void	print_map(t_map *map , t_table *routes)
{
	int		i;
	int		j;

	printf("123123\n\n");
	while(map)
	{
		j = 0;
		while( ++j < (routes->table[map->wayid])->waylendth - 1)
			printf("|%3s|->", routes->table[map->wayid]->route_nodes[j]->name);
		printf("\n");
		map = map->next;
	}
}



int		errorr(char *s)
{
	ft_printf("%s\n", s);
	exit(0);
	return(1);
}

void	pushf(t_node **rooms, t_node *n)
{
	n->next = *rooms;
	*rooms = n;
}

void	add_edge(t_node *room1, t_node *room2)
{
	int			i;
	int			j;
	t_node		**newedges;

	newedges = (t_node **)malloc(sizeof(t_node *) * (room1->nedges + 2));
	newedges[room1->nedges + 1] = 0;
	newedges[room1->nedges] = room2;
	i = -1;
	while(room1->edges && ++i < room1->nedges)
		newedges[i] = room1->edges[i];
	if (room1->edges)
		free(room1->edges);
	room1->edges = newedges;
	room1->nedges++;
	newedges = (t_node **)malloc(sizeof(t_node *) * (room2->nedges + 2));
	newedges[room2->nedges + 1] = 0;
	newedges[room2->nedges] = room1;
	i = -1;
	while(room1->edges && ++i < room2->nedges)
		newedges[i] = room2->edges[i];
	if (room2->edges)
		free(room2->edges);
	room2->edges = newedges;
	room2->nedges++;
}

t_node	*find_room(t_node *room, char *name)
{
	while(1)
	{
		if (room && room->name && !ft_strcmp(room->name, name))
			return(room);
		if (!room->next)
			break ;
		room = room->next;
	}
	errorr("links: room not found");
	return (0);
}


t_node		*create_room(char *s, char es)
{
	int			i;
	t_node		*newroom;

	i = ft_strchr(s, ' ') - s;
	newroom = malloc(sizeof(t_node));
	newroom->name = ft_strsub(s, 0, i);
	newroom->x = 0;
	while(s[++i] && s[i] >= '0' && s[i] <= '9')
		newroom->x = newroom->x * 10 + s[i] - 48;
	s[i] == ' ' ? 0 : errorr("rooms position");
	while(s[++i] && s[i] >= '0' && s[i] <= '9')
		newroom->y = newroom->y * 10 + s[i] - 48;
	s[i] == 0 ? 0 : errorr("rooms position");
	newroom->es = es;
	newroom->next = 0;
	newroom->edges = 0;
	newroom->nedges = 0;
	newroom->visited = 0;
	return (newroom);
}

void		readlinks(t_node *rooms, char *s ,char *cache)
{
	char	*name1;
	char	*name2;
	t_node	*room1;
	t_node	*room2;

	while(1)
	{
		if((name2 = ft_strchr(s, '-')))
		{
			*name2++ = 0;
			name1 = s;
			room1 = find_room(rooms, name1);
			room2 = find_room(rooms, name2);
			add_edge(room1, room2);
		}
		else if (s[0] == '#')

		else
			break ;
		free(s);
		if(get_next_line(fd, &s) <= 0)
			break;
	}
}

void	read_rooms(t_node	**rooms)
{
	char	*s;
	char	es;
	t_node	*tmp;

	es = 0;
	while (get_next_line(fd, &s) && !ft_strchr(s, '-'))
	{
		if (s[0] == '#' && !ft_strcmp(s, "##start"))
			es = !es ? -1 : errorr("start room error");
		else if (s[0] == '#' && !ft_strcmp(s, "##end"))
			es = !es ? 1 : errorr("end room error");
		if (s[0] != '#')
		{
			pushf(rooms, create_room(s, es));
			es = 0;
		}
		free(s);
	}
	if (*rooms == 0)
		errorr("no_rooms");
	readlinks(*rooms, s);
}

int		countlemins()
{
	char *s;
	int lemins;
	int i;

	lemins = 0; 
	i = 0;
	while(1)
	{	get_next_line(fd, &s);
		if (s[i] != '#')
			break;
	}
	while (s[i] && (s[i] >= '0' && s[i] <='9'))
		lemins = lemins * 10 + s[i++] - 48;
	if (s[i]!= '\0')
		errorr("countlemins");
	free(s);
	return (lemins);
}

t_node	*find_start(t_node *room)
{
	while(1)
	{
		if (room && room->es == -1)
			return(room);
		if (!room->next)
			break ;
		room = room->next;
	}
	errorr ("no_start");
	return (0);
}

int		check_next(t_node *next, t_route *way)
{
	int		i;

	i = -1;
	if (next->visited)
		return (0);
	while(way && ++i < way->waylendth)
		if (way->route_nodes[i] == next || way->route_nodes[i]->visited)
			return (0);
	return (1);
}

t_route		*update_way(t_node *cur, t_route *way)
{
	t_route		*newway;
	int			i;
	int			j;

	i  = way ? way->waylendth : 0;
	newway = malloc(sizeof(t_route));
	newway->route_nodes = malloc(sizeof(t_node *) * (i + 2));
	newway->route_nodes[i + 1] = 0;
	newway->route_nodes[i] = cur;
	j = -1;
	while(++j < i)
		newway->route_nodes[j] = way->route_nodes[j];
	newway->waylendth = i + 1;
	return (newway);
}

void	add_to_route_table(t_table *routes, t_route *way)
{
	int			i;
	t_route		**newtable;
	int			*newlength;

	newtable = malloc(sizeof(t_route *) * (routes->n + 2));
	newtable[routes->n + 1] = 0;
	newtable[routes->n] = way;
	i = -1;
	while ( ++i < routes->n)
		newtable[i] = routes->table[i];
	free (routes->table);
	routes->table = newtable;
	routes->n++;
	i = 0;
	while(++i < way->waylendth - 1)
		way->route_nodes[i]->visited = 1;
}

void	queue_pushback(t_queue **queue, t_node *room, t_route *route)
{
	t_queue		*tmp;
	t_queue		*wtmp;

	tmp = malloc(sizeof(t_queue));
	tmp->room = room;
	tmp->route = update_way(room, route);
	tmp->next = 0;
	if (*queue == 0)
	{
		*queue = tmp;
		return ;
	}
	wtmp = *queue;
	while(wtmp && wtmp->next)
		wtmp = wtmp->next;
	wtmp->next = tmp;
}

int		is_visited(t_queue *elem)
{
	int i;
	int j;

	j = elem->route->waylendth - 1;
	if (elem->room->visited == 1)
		return (1);
	i = 0;
	while(++i < j)
		if (elem->route->route_nodes[i]->visited)
			return (1);
	return (0);
}


void	breadth_search(t_queue *queue, t_table *route)
{
	int			i;
	t_queue		*tmp;

	while(queue)
	{
		if (queue->room->es == 1 && !is_visited(queue))
			add_to_route_table(route, queue->route);
		else if (queue->room->es != 1 && !is_visited(queue) && (i = -1))
			while(++i < queue->room->nedges)
				if (check_next(queue->room->edges[i], queue->route))
					queue_pushback(&queue, queue->room->edges[i], queue->route);
		if (queue->route && queue->room->es != 1)
		{
			free(queue->route->route_nodes);
			free(queue->route);
		}
		tmp = queue->next;
		free(queue);
		queue = tmp;
	}
}

// ! function for check  valid start/end rooms...
// ! save read cache

void	valid()





int		main(int argc, char **argv)
{
	int lemins;
	t_node	*rooms;
	t_table *routes;

	fd = open(argv[1], O_RDONLY);
	lemins = countlemins();
	read_rooms(&rooms);
// ! validcheck function...
	t_node		*tmp = rooms;
	int			k;

	while(tmp)
	{
		printf("%s\n", tmp->name);
			// printf("edges :");
			// k = -1;
			// while(++k < tmp->nedges)
			// 	printf(">|%s|_", tmp->edges[k]->name);
			// printf("\n%i_________________________________\n", tmp->nedges);
		tmp = tmp->next;
	}
	routes = (t_table *)malloc(sizeof(t_table));
	routes->table = 0;
	routes->n = 0;
	t_queue *queue= malloc(sizeof(t_queue));
	queue->room = find_start(rooms);
	queue->next = 0;
	queue->route = update_way(queue->room,0);
	breadth_search(queue, routes);
	printroutes(routes);
	close(fd);
}



