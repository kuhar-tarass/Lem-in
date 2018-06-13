#include "./include/header.h"
int recurs = 0;
int fd;

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

	room = (t_node *)malloc(sizeof(t_node));
	i = 0;
	while (s[i] != ' ' && s[i] && s[i] != '-')
		i++;
	room->name = ft_strsub(s, 0, i);
	if (s[i] != ' ' )
		return (0);
	room->x = 0;
	while(s[i] && s[i] != ' ' && s[i] <= '9' && s[i] >= '0')
		room->x += (s[i++] - 48);
	if (s[i] != ' ')
		return (0);
	room->y = 0;
	while(s[i] && s[i] != ' ' && s[i] <= '9' && s[i] >= '0')
		room->y += (s[i++] - 48);
	room->next = 0;
	room->end = 0;
	room->nedg = 0;
	room->nways = 0;
	room->edge = 0;
	room->ways = 0;
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

	room = 0;
	while (get_next_line(fd, &s) > 0)
	{
		if (!ft_strcmp(s, "##start"))
		{
			get_next_line(fd, &s);
			tmpr = crateroom(s);
			pushfront(&room, tmpr);
		}
		if(!ft_strcmp(s, "##end"))
		{
			get_next_line(fd, &s);
			tmpr = crateroom(s);
			tmpr ? tmpr->end = 1 : 0; 
			pushback(&room, tmpr);
		}
		if (!ft_strchr(s, '#'))
		{
			tmpr = crateroom(s);
			pushback(&room, tmpr);
		}
		if (tmpr == 0)
			break;
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

	new = malloc(sizeof(t_node *) * (cur->nedg + 2));
	cur->nedg++;
	i = 0;
	if (cur->edge)
		while(cur->edge[i])
		{
			new[i] = cur->edge[i];
			i++;
		}
	new[i] = room;
	new[i + 1] = 0;
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


// void	printwhays(t_node *n)
// {
// 	int i;

// 	i = 0;
	
// 	while (n->edge && n->edge[i])
// 	{
// 		printf("%s : %s\n",n->name, (n->edge[i])->name);
// 		i++;
// 	}
// }



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

void	freeways(t_node *n)
{
	int i; 

	i = -1;
	while(n->ways && ++i < n->nways)
		free((n->ways)[i]);
	if (n->ways)
		free(n->ways);
}

int		addway(t_node *prev, t_node *n)
{
	int i;
	int i2;
	int jnew;
	int j;
	t_node	***newroute;

	newroute = (t_node ***)malloc(sizeof(t_node **) * (prev->nways > 1 ? prev->nways : 1 + n->nways + 1));
	newroute[prev->nways ? prev->nways : 1 + n->nways] = 0;
	jnew = 0;
	j = 0;
	while (n->end && j < n->nways)
	{
		i = countwaylength(n->ways[j]);
		newroute[jnew] = (t_node **)malloc(sizeof(t_node *) * (i + 1));
		newroute[jnew][i] = 0;
		i2 = -1;
		while (++i2 < i)
			newroute[jnew][i2] = n->ways[j][i2];
		j++;
		jnew++;
	}
	j = 0;
	while(j < prev->nways)
	{
		i = countwaylength(prev->ways[j]);
		newroute[jnew] = (t_node **)malloc(sizeof(t_node) * (i + 2));
		newroute[jnew][i + 1] = 0;
		newroute[jnew][i] = prev;
		i2 = -1;
		while (++i2 < i)
			newroute[jnew][i2] = prev->ways[j][i2];
		j++;
		jnew++;
	}
	if (!(prev->nways))//														 !leaks can be here
	{
		newroute[jnew] = (t_node **)malloc(sizeof(t_node *) * 2);
		newroute[jnew][0] = prev;
		newroute[jnew][1] = 0;
		jnew++;
	}
	n->nways = jnew;
/*
		// j2 = 0;
		// while (j2 < n->nways)
		// {
		// 	i = countwaylength((n->ways)[j2]);
		// 	newroute[j] = (t_node **)malloc(sizeof(t_node *) * (i + 1));
		// 	newroute[j][i] = 0;
		// 	while (i--)
		// 		newroute[j][i] = (n->ways)[j2][i];
		// 	j2++;
		// 	j++;
		// }
		// i = 0;
		// while (prev && i < prev->nways)
		// {
		// 	i = countwaylength((prev->ways)[j]);
		// 	newroute[j] = (t_node **)malloc(sizeof(t_node *) * (i + 2));
		// 	newroute[j][i] = prev;
		// 	newroute[j][i + 1] = 0;
		// 	while (i--)
		// 		newroute[j][i] = (prev->ways)[j][i];
		// 	j++;
		// }
*/
//	freeways(n);
	// if (!n->end)
	// 	printf("%i", jnew);
	n->ways = newroute;
	return (1);
}

int		checkroute(t_node *prev, t_node *next)
{
	int i;
	int j;

	if (!next || next == prev || (prev && prev->end == 1))
		return (1);
	j = 0;
	while (prev && prev->ways && j < prev->nways)
	{
		i = 0;
		while ((prev->ways)[j][i])
		{
			if (prev->ways[j][i] == next)
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}


int	route(t_node *prev, t_node *n)
{
	int i;

	i = -1;
	if (prev)
		addway(prev, n);
	// if (n)
	// {
	// 	printf ("\nstep:	%d___________________________\n", recurs++);
		
	// 	printf("n->name :	%s\n", n->name);
	// 	int x1;
	// 	int x2;

	// 	x1 = 0;
	// 	while (n->ways && x1 < n->nways && n->ways[x1])
	// 	{
	// 		x2 = 0;
	// 	 	while(n->ways[x1][x2])
	// 		{
	// 			printf ("%s->", n->ways[x1][x2]->name);
	// 			x2++;
	// 		}
	// 		x1++;
	// 		n->end ? printf("end\n"): printf("\n");
	// 	}
	// 	printf ("________________________________________\n\n\n");
	// }
	while (!n->end && n->edge[++i])
	{
		if (checkroute(prev, (n->edge)[i]))
			continue;
		route(n, n->edge[i]);
	}
	return (1);
}

int	main(int argc, char const *argv[])
{
	int num_ants;
	t_node	*room;
	char	*tmp;

	fd = open ("./1", O_RDONLY);
//	printf("fd == %d\n\n\n", fd);
	num_ants = number_of_ants();
	room = readroom();
	route(0, room);

	// printf ("%p\n",(room->edge));
	t_node *tmproom;
	tmproom = room;
	int x1;
	int x2;
	while(tmproom)
	{
		if (tmproom->end)
		{
			x1 = 0;
			while (tmproom->ways && x1 < tmproom->nways)
			{
				x2 = 0;
				while(tmproom->ways[x1][x2])
				{
					printf ("%s->", tmproom->ways[x1][x2]->name);
					x2++;
				}
				x1++;
			printf("end\n");
			}
			break ;
		}
		tmproom = tmproom->next;	
	}
	close(fd);
	return (0);
}