/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:18:10 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/12 14:20:15 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush_back(t_list **begin_list, void const *content,
	size_t content_size)
{
	t_list	*tmp;

	if (!*begin_list)
	{
		*begin_list = ft_lstnew(content, content_size);
		return ;
	}
	tmp = *begin_list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = ft_lstnew(content, content_size);
}
