#include "header.h"

int	main(int argc, char const *argv[])
{
	// t_node	*first;
	// t_node	*second;
	// t_node	*arr;

	// first = malloc(sizeof(t_node))
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

t_node	***addway(t_node *old, t_node *n)
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
	free (n->)
}

int	route(t_node *prev, t_node *n)
{
	


}