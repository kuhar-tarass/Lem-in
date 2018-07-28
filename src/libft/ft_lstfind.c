/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 15:23:12 by tkuhar            #+#    #+#             */
/*   Updated: 2018/03/30 15:23:13 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list **begin, void *content, size_t n)
{
	t_list *tmp;

	tmp = *begin;
	while (tmp)
	{
		if (!ft_memcmp(tmp->content, content, n))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}
