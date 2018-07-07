#include "./include/header.h"
int recurs = 0;
int fd; 

int		errorr(char *s)
{
	ft_printf("%s", s);
	exit(0);
	return(1);
}

void	pushf(t_node **rooms, t_node *n)
{
	n->next = *rooms;
	*rooms = n;
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
	errorr("links room not found");
}


t_node		*create_room(char *s, char es)
{
	int			i;
	t_node		*newroom;

	i = ft_strchr(s, ' ') - s;
	newroom = malloc(sizeof(t_node));
	newroom->name = ft_strsub(s, 0, i);
	newroom->x = 0;
	while(s[i] && s[i] >= '0' && s[i] <= '9')
		newroom->x = newroom->x * 10 + s[i++] - 48;
	s[i] == ' ' ? 0 : errorr("rooms position");
	while(s[i] && s[i] >= '0' && s[i] <= '9')
		newroom->y = newroom->y * 10 + s[i++] - 48;
	s[i] == 0 ? 0 : errorr("rooms position");
	newroom->next = 0;
	newroom->es = 0;
	newroom->edges = 0;
	newroom->nedges = 0;
	return (newroom);
}

void		readlinks(t_node *rooms, char *s)
{
	char *name1;
	char *name2;

	name2 = ft_strchr(s, '-') + 1;
	*(name2 - 1) = 0;
	name1 = s;


}



void	*read_rooms(t_node	**rooms)
{
	char	*s;
	char	es;
	t_node	*tmp;

	es = 0;
	while (get_next_line(fd, &s))
	{
		if (s[0] == '#' && !ft_strcmp(s, "##start"))
			es = !es ? -1 : errorr("start room error");
		else if (s[0] == '#' && !ft_strcmp(s, "##end"))
			es = !es ? 1 : errorr("end room error");
		else if (s[0] == '#')
			continue ;
		if (!ft_strchr(&s, '-'))
			pushf(rooms, createroom(s, es));
		else
		{

		}

		
	}

		
		
		
}

int		countlemins()
{
	char *s;
	int lemins;
	int i;

	lemins = 0; 
	get_next_line(fd, &s);
	while (s[i] && (s[i] >= '0' && s[i] <='9'))
		lemins = lemins * 10 + s[i] - 48;
	if (s[i]!= '\0')
		errorr("countlemins");
	free(s);
	return (lemins);
}


int		main(int argc, char **argv)
{
	int lemins;
	t_node	*rooms;

	lemins = countlemins();
	rooms = 


}












































































































































































/*
void		printarr(t_node *tmproom);
t_node	*readways(t_node	*room,char *s);

int		number_of_ants()
{
	char *s;

	get_next_line(fd, &s);
	return(ft_atoi(s));
}

t_node	*crateroom(char *s)
{
	t_node	*room;
	int		i;

	if (!(room = (t_node *)malloc(sizeof(t_node))))
		exit (0);
	i = 0;
	while (s[i] != ' ' && s[i] && s[i] != '-')
		i++;
	room->name = ft_strsub(s, 0, i);
	if (s[i] != ' ' )
		return (0);
	room->x = 0;
	while(s[i] && s[i] != ' ' && s[i] <= '9' && s[i] >= '0')
		room->x = room->x * 10  + (s[i++] - 48);
	if (s[i] != ' ')
		return (0);
	room->y = 0;
	while(s[i] && s[i] != ' ' && s[i] <= '9' && s[i] >= '0')
		room->y = room->y * 10  + (s[i++] - 48);
	room->next = 0;
	room->edge = 0;
	room->nedg = 0;
	room->way = 0;
	room->waylength = 0;
	room->end = 0;
	room->ways = 0;
	room->wayslength = 0;
	room->nways = 0;
	return (room);
}

void	pushback(t_node **list, t_node *new)
{
	t_node	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	pushfront(t_node **list, t_node *new)
{
	new->next = *list;
	*list = new;
}

t_node	*readroom()
{
	t_node	*room;
	t_node	*tmpr;
	char *s;
	char es;

	room = 0;
	es = 0;
	while (get_next_line(fd, &s) > 0)
	{
		if (!ft_strcmp(s, "##start"))
			es = -1; 
		else if(!ft_strcmp(s, "##end"))
			es = 1; 
		if (ft_strchr(s, '#'))
			continue;
		tmpr = crateroom(s);
		if (tmpr == 0)
			break;
		tmpr->end = es == 1 && !(es = 0) ? 1 : 0; 
		if (es == -1 && !(es = 0))
			pushfront(&room, tmpr);
		else
			pushback(&room, tmpr);
		free(s);
	}
	readways(room, s);
	return (room);
}

t_node	*findroom(t_node *room, char *name)
{
	while (room)
	{
		if (!ft_strcmp(room->name, name))
			return (room);
		room = room->next;
	}
	return (0);
}

void	addedge(t_node *cur, t_node *room)
{
	int i;
	t_node **new;

	if (!(new = malloc(sizeof(t_node *) * (cur->nedg + 2))))
		exit (0);
	i = -1;
	if (cur->edge)
		while(++i < cur->nedg)
			new[i] = cur->edge[i];
	new[cur->nedg] = room;
	new[cur->nedg + 1] = 0;
	cur->nedg++;
	if (cur->edge)
		free(cur->edge);
	cur->edge = new;
}

t_node	*readways(t_node	*room,char *s)
{
	char *name1;
	char *name2;
	t_node *cur;
	t_node *tmp;

	while(1)
	{
		name2 = ft_strchr(s, '-') + 1;
		name1 = ft_strsub(s, 0, name2 - s - 1);
		if (!(cur = findroom(room, name1)))
			ERROR_NONEX_ROOM();
		if (!(tmp = findroom(room, name2)))
			ERROR_NONEX_ROOM();
		addedge(cur, tmp);
		addedge(tmp, cur);
		free(name1);
		free (s);
		if (get_next_line(fd, &s) < 1)
			break ;
	}
	return (room);
}

int		countways(t_node ***arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int		countwaylength(t_node **arr)
{
	int i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

t_node	**news(t_node *prev, t_node *n)// ?										create new route (add to prev route cur element)
{
	t_node	**newroute;
	int		i;

	n->waylength = prev->waylength + 1;
	if(!(newroute = (t_node **)malloc(sizeof(t_node *) * (n->waylength + 1))))
		exit(0);
	newroute[n->waylength] = 0;
	newroute[prev->waylength] = prev;
	i = -1;
	while (++i < prev->waylength && prev->way)
		newroute[i] = (prev->way)[i];
	if (n->way)
		free (n->way);
	return (newroute);
}

t_node	***newways(t_node *prev, t_node *n)// ?									add to route table(only in end struct) new route
{
		t_node	***ways;
		int i;
		

		if (!(ways = malloc(sizeof(**ways) * (n->nways + 2))))
			exit (0);
		i = -1;
		while(++i < n->nways && n->ways)
			ways[i] = n->ways[i];
		ways[n->nways] = news(prev, n);
		ways[n->nways + 1] = 0;
		free(n->ways);
		return (ways);
}

int		*newwayslength(t_node *prev, t_node *n)// ?								add to routes length tabele info about new route
{
		int		*wayslength;
		int i;

		if (!(wayslength = malloc(sizeof(int) * n->nways + 2)))
			exit (0);
		i = -1;
		while(++i < n->nways && n->nways)
			wayslength[i] = n->wayslength[i];
		wayslength[n->nways] = prev->waylength + 1;
		wayslength[n->nways + 1] = 0;
		free(n->wayslength);
		return (wayslength);
}

int		addway(t_node *prev, t_node *n)
{
	if (n->end)
	{
		n->ways = newways(prev, n);
		n->wayslength = newwayslength(prev, n);
		n->nways++;
		printarr(n);
		return (0);
	}
	n->way = news(prev, n);
	n->waylength = prev->waylength + 1;
	return (1);
}

int		checkroute(t_node *prev, t_node *next)
{
	int i;

	if (!next || next == prev || (prev && prev->end == 1))
		return (1);
	i = -1;
	while (prev && prev->way && (prev->way)[++i])
		if (prev->way[i] == next)
			return (1);
	return (0);
}


int	route(t_node *prev, t_node *n)
{
	int i;

	
	if (prev)
		addway(prev, n);
	i = -1;
	while (!n->end && n->edge[++i])
	{
		if (checkroute(prev, (n->edge)[i]))
			continue;
		route(n, n->edge[i]);
	}
	return (1);
}

int		main(int argc, char const *argv[])
{
	int num_ants;
	t_node	*room;


	fd = open ("./2", O_RDONLY);
//	printf("fd==%d\n\n\n", fd);
	num_ants = number_of_ants();
	room = readroom();
	route(0, room);

	// printf ("%p\n",(room->edge));
	t_node	*tmproom;
	tmproom = room;
	while(tmproom)
	{
		if (tmproom->end)
		{
			printarr(tmproom);
			break ;
		}
		tmproom = tmproom->next;
	}
	close(fd);
	argv = 0;
	return (0*argc);
}





void		printarr(t_node *tmproom)
{
	int x1;
	int x2;

	printf("nways == %d\n\n", tmproom->nways);
			x1 = 0;
			
			while (x1 < tmproom->nways)
			{
				// printf ("%d", tmproom->wayslength[x1]);
				// printf("[%s]->", (tmproom->ways[x1][0])->name);
				// printf("[%s]->", tmproom->ways[1][1]->name);
				// printf("[%s]->", (tmproom->ways[x1][0])->name);
				x2 = 0;
				// while(x2 < 1 )
				while(x2 < tmproom->wayslength[x1])
				{
				// 	// if (tmproom->ways[x1][x2])
					printf("[%s]->", (tmproom->ways[x1][x2])->name);
					x2++;
				}
				x1++;
			printf("end\n");
			}
	printf("-------------------------stepstepstep--------------------------\n");
}

*/