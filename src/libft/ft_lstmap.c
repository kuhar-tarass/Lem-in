/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:55:24 by tkuhar            #+#    #+#             */
/*   Updated: 2018/03/28 15:55:25 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*fresh;
	t_list	*temp;

	if (!lst || !f)
		return (0);
	fresh = (t_list *)malloc(sizeof(t_list));
	if (!fresh)
		return (0);
	fresh = f(ft_lstnew(lst->content, lst->content_size));
	temp = fresh;
	while (lst->next)
	{
		fresh->next = f(ft_lstnew(lst->next->content, lst->next->content_size));
		fresh = fresh->next;
		lst = lst->next;
	}
	return (temp);
}
