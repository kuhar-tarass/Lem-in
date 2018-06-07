/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:44:43 by tkuhar            #+#    #+#             */
/*   Updated: 2018/03/29 18:44:44 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush_front(t_list **begin_list, void const *content,
	size_t content_size)
{
	t_list *new;

	new = ft_lstnew(content, content_size);
	new->next = *begin_list;
	*begin_list = new;
}
