/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 19:02:58 by tkuhar            #+#    #+#             */
/*   Updated: 2018/03/29 19:03:00 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*lstfree(t_list **l)
{
	t_list		*tmp;

	while (*l)
	{
		tmp = (*l)->next;
		free((void *)(*l)->content);
		free((void *)(*l)->content_size);
		(*l) = tmp;
	}
	*l = 0;
	return (0);
}

t_list			*ft_strsplit_lst(char const *s, char c)
{
	t_list		*words;
	int			start;
	int			i;
	char		*str;

	words = 0;
	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			continue;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (!!(str = ft_strsub(s, start, i - start)))
			ft_lstpush_back(&words, str, i - start);
		else
			return (lstfree(&words));
	}
	return (words);
}
