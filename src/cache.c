/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 13:59:13 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/28 14:47:44 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		print_cache(void)
{
	t_cache	*tmp;

	while (g_input)
	{
		ft_printf("%s\n", g_input->s);
		tmp = g_input;
		g_input = g_input->next;
		if (tmp->s)
			free(tmp->s);
		free(tmp);
	}
	write(1, "\n", 1);
}

void		add_cache(char *s)
{
	int		len_s;
	t_cache *tmp;
	t_cache *new;
	int		i;

	tmp = g_input;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!(new = malloc(sizeof(t_cache))))
		exit(0);
	len_s = ft_strlen(s);
	if (!(new->s = malloc(sizeof(char) * (len_s + 1))))
		exit(0);
	new->next = 0;
	new->s[len_s] = 0;
	i = -1;
	while (++i < len_s)
		new->s[i] = s[i];
	if (!tmp)
		g_input = new;
	else
		tmp->next = new;
}
