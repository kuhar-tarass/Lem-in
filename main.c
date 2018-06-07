#include "./include/header.h"

int	number_of_ants()
{
	char *s;

	get_next_line(0, &s);
	return(ft_atoi(s));
}

t_node	*readroom(char *s)
{
	t_node	*room;
	int		i;

	room = (t_node *)malloc(sizeof(t_node));
	i = 0;
	while (s[i] != ' ' && s[i])
		i++;
	room->name = ft_strsub(s, 0, i);
	if (s[i] != ' ')
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

void	addstartend(t_node **list, t_node *start, t_node *end)
{
	start->next = end;
	end->next = *list;
	*list = start;
}


int	main(int argc, char const *argv[])
{
	int num_ants;
	t_node	*room;
	char	*tmp;
	t_node	*start;
	t_node	*end;

	num_ants = number_of_ants();
	room = 0;
	while (get_next_line(0, &tmp) > 0)
	{
		if (ft_strstr(tmp, "##start"))
		{
			get_next_line(0, &tmp);
			start = readroom(tmp);
		}
		if (ft_strstr(tmp, "##end"))
		{
			get_next_line(0, &tmp);
			end = readroom(tmp);
			end->end = 1;
		}
		if (!ft_strchr(tmp, '#'))
			pushback(&room, readroom(tmp));
		free(tmp);
	}
	addstartend(&room, start, end);
	t_node	*tmproom = room;
	while(tmproom)
	{
		printf("%s\n", tmproom->name);
		tmproom = tmproom->next;
	}
	return (0);
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
	while (arr[i])
		i++;
	return (i);
}

void	freeways(t_node *n)
{
	int i; 

	i = -1;
	while(++i < n->nways)
		free((n->ways)[i]);
	free(n->ways);
}

int		addway(t_node *old, t_node *n)
{
	int i;
	int j;
	int j2;
	t_node	***newroute;

	newroute = (t_node ***)malloc(sizeof(t_node **) * (old->nways + n->nways + 1));
	newroute[old->nways + n->nways] = 0;
	while (j2 < n->nways)
	{
		i = countwaylength((n->ways)[j2]);
		newroute[j] = (t_node **)malloc(sizeof(t_node *) * (i + 2));
		newroute[j][i] = old;
		newroute[j][i + 1] = 0;
		while (i--)
			newroute[j][i] = (n->ways)[j2][i];
		j2++;
		j++;
	}
	while (j < old->nways)
	{
		i = countwaylength((old->ways)[j]);
		newroute[j] = (t_node **)malloc(sizeof(t_node *) * (i + 2));
		newroute[j][i] = old;
		newroute[j][i + 1] = 0;
		while (i--)
			newroute[j][i] = (old->ways)[j][i];
		j++;
	}
	freeways(n);
	n->ways = newroute;
	return (1);
}

int checkroute(t_node *n, t_node *next)
{
	int i;
	int j;

	i = 0;
	if (!next || next == n)
		return (1);
	while (i < n->nways)
	{
		j = 0;
		while (n->ways[i][j])
		{
			if (n->ways[i][j] == next)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}


int	route(t_node *prev, t_node *n)
{
	int i;

	i = 0;
	addway(prev, n);
	while (n->edge[i])
	{
		if (checkroute(n, (n->edge)[i]))
			continue;
		route(n, n->edge[i]);
		i++;
	}
	return (1);
}