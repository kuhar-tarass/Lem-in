#include "./include/header.h"

int fd = 0; 
t_cache		*g_input;

void		print_cache(void)
{
	t_cache  *tmp;
	
	while(g_input)
	{
		ft_printf("%s\n",g_input->s);
		tmp = g_input;
		g_input = g_input->next;
		if(tmp->s)
			free(tmp->s);
		free(tmp);
	}
	write(1,"\n",1);
}

void		add_cache(char *s)
{
	int		len_s;
	t_cache *tmp;
	t_cache *new;
	int		i;

	tmp = g_input;
	while(tmp && tmp->next)
		tmp = tmp->next;
	if (!(new = malloc(sizeof(t_cache))))
		exit(0);
	len_s = ft_strlen(s);
	if (!(new->s = malloc(sizeof(char) * (len_s + 1))))
		exit(0);
	new->next = 0;
	new->s[len_s] = 0;
	i = -1;
	while(++i < len_s)
		new->s[i] = s[i];
	if(!tmp)
		g_input = new;
	else
		tmp->next = new;
}

void	printroutes(t_table *routes)
{
	int i;
	int j;

	i = -1;
	while (++i < routes->n)
	{
		j = 0;
		while( ++j < (routes->table[i])->waylendth)
			printf("|%3s|->", routes->table[i]->route_nodes[j]->name);
		printf("\n");
	}
	printf("total:	%i\n", routes->n); 
}

void	print_map(t_map *map , t_table *routes)
{
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
	ft_printf("ERROR:	%s\n", s);
	exit(0);
	return(1);
}


void		check_room(t_node *rooms, t_node *n)
{
	while(rooms)
	{
		if (!ft_strcmp(rooms->name, n->name))
			errorr("redefinition room");
		if (rooms->x == n->x && rooms->y == n->y)
			errorr("double definition");
		rooms = rooms->next;
	}
}


void	pushf(t_node **rooms, t_node *n)
{
	check_room(*rooms, n);
	n->next = *rooms;
	*rooms = n;
}

void	add_edge(t_node *room1, t_node *room2)
{
	int			i;
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
	char		*tmp;

	tmp = ft_strchr(s, ' ');
	i = tmp ? tmp - s : errorr("rooms position");
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

void	readlinks(t_node *rooms, char *s)
{
	char	*name1;
	char	*name2;
	t_node	*room1;
	t_node	*room2;

	while(1)
	{
		add_cache(s);
		if(s[0] != '#' && (name2 = ft_strchr(s, '-')))
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
			break;
		}
		free(s);
		if(get_next_line(fd, &s) <= 0)
			break;
	}
}

void	read_rooms(t_node	**rooms)
{
	char	*s;
	char	es;

	es = 0;
	while (get_next_line(fd, &s) && !ft_strchr(s, '-'))
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

int		countlemins()
{
	char *s;
	int lemins;
	int i;

	lemins = 0; 
	i = 0;
	while(get_next_line(fd, &s) > 0)
	{
		add_cache(s);
		if (s[i] != '#')
			break;
		free(s);
	}
	while (s[i] && (s[i] >= '0' && s[i] <='9'))
		lemins = lemins * 10 + s[i++] - 48;
	if (s[i]!= '\0')
	{
		errorr("count lemins");
	}
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
		{
			add_to_route_table(route, queue->route);
			tmp = queue->next;
			free(queue);
			queue = tmp;
			continue ;
		}
		else if (queue->room->es != 1 && !is_visited(queue) && (i = -1))
			while(++i < queue->room->nedges)
				if (check_next(queue->room->edges[i], queue->route))
					queue_pushback(&queue, queue->room->edges[i], queue->route);
		free(queue->route->route_nodes);
		free(queue->route);
		tmp = queue->next;
		free(queue);
		queue = tmp;
	}
}

void	valid(t_node *rooms)
{
	int count_start;
	int count_end;

	count_start = 0;
	count_end = 0;
	while(rooms)
	{
		if (rooms->es == -1)
			count_start++;
		if (rooms->es == 1)
			count_end++;
		rooms = rooms->next;
	}
	if (count_end != 1)
		errorr("multiply end");
	if (count_start != 1)
		errorr("multiply start");
}

int		used_routes(t_table *routes, int lemins,  unsigned int *steps)
{
	int				used;
	int				i;
	unsigned int	tmp;

	*steps = 2147483647;
	used = 1;
	while(used <= routes->n)
	{
		tmp = 0;
		i = -1;
		while (++i < used)
			tmp += routes->table[i]->waylendth - 1;
		tmp += lemins - 1;
		tmp = tmp / used + (tmp % used ? 1 : 0);
		if (tmp > *steps)
			return (used - 1);
		*steps = tmp;
		used++;
	}
	return (used - 1);
}

void	printout(t_out *arr)
{
	while (arr)
	{
		if (arr->i >= 0)
			printf("L%i->%s ",arr->ant_name, arr->route->route_nodes[arr->i]->name);
		arr = arr->next;
	}
	printf("\n");
}

void	update_out(t_out *arr)
{
	while(arr)
	{
		if (arr->i < arr->route->waylendth - 1)
			arr->i++;
		else
			arr->i = -1;
		arr = arr->next;
	}
}


void	push_back_out(t_out **arr, t_route *route)
{
	t_out	*new;
	t_out	*tmp;

	new = malloc(sizeof(t_out));
	new->route = route;
	new->next = 0 ;
	new->i = 1;
	tmp  = *arr;
	new->ant_name = 1;
	if (!tmp)
	{
		*arr = new;
		return; 
	}
	while (tmp && (tmp)->next)
		tmp = (tmp)->next;
	new->ant_name = (tmp)->ant_name + 1;
	(tmp)->next = new;
}

void	free_out_struct(t_out **arr)
{
	t_out *tmp;

	while(*arr)
	{
		tmp = (*arr)->next;
		free(*arr);
		*arr = tmp;
	}
}


void	createout(t_table *routes, int lemins)
{
	unsigned int	steps;
	int				u;
	t_out			*arr;
	int				j;
	int				global;

	arr = 0;
	u = used_routes(routes, lemins, &steps);
	global = 0;
	while(steps)
	{
		update_out(arr);
		j = -1;
		while(++j < u)
			if ((unsigned)routes->table[j]->waylendth - 1 <= steps && global < lemins)
			{
				push_back_out(&arr, routes->table[j]);
				global++;
			}
		printout(arr);
		steps--;
	}
	free_out_struct(&arr);
}

int		main(int argc, char **argv)
{
	int		lemins;
	t_node	*rooms;
	t_table *routes;
	t_queue *queue;

	fd = open(argv[1], O_RDONLY);
	if (read(fd,0,0) < 0)
		errorr("bad fd");
	g_input = 0;
	lemins = countlemins();
	read_rooms(&rooms);
	valid(rooms);
	routes = (t_table *)malloc(sizeof(t_table));
	routes->table = 0;
	routes->n = 0;
	queue = 0;
	queue_pushback(&queue,find_start(rooms),0);
	print_cache();
	breadth_search(queue, routes);
	createout(routes, lemins);
	system("leaks a.out");
	// printroutes(routes);
	close(fd);
	return (argc * 0);
}


