/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:07:11 by tkuhar            #+#    #+#             */
/*   Updated: 2018/03/21 17:07:14 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	void *temp;

	temp = b;
	while (n-- > 0)
	{
		*(unsigned char *)b = (unsigned char)c;
		b++;
	}
	return (temp);
}
