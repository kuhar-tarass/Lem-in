/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 22:14:21 by tkuhar            #+#    #+#             */
/*   Updated: 2018/03/27 22:14:23 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*new;

	new = malloc(sizeof(t_list) * 1);
	if (!new)
		return (0);
	new->content = malloc(1 * content_size);
	if (!new->content)
	{
		free(new);
		return (0);
	}
	if (content)
	{
		ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	else
	{
		new->content = 0;
		new->content_size = 0;
	}
	new->next = 0;
	return (new);
}
