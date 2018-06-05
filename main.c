#include "header.h"

int	main(int argc, char const *argv[])
{
	
	return 0;
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
	if (next == n)
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