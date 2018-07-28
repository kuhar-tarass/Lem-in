/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 22:20:27 by tkuhar            #+#    #+#             */
/*   Updated: 2018/03/25 22:20:28 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nsize(int n)
{
	int		size;

	size = n <= 0 ? 1 : 0;
	while (n != n / 10)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(int n)
{
	int		size;
	char	*new;

	size = nsize(n);
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (0);
	if (n == 0)
		new[0] = 48;
	new[size] = '\0';
	if (n < 0)
	{
		new[0] = '-';
		new[size - 1] = (n % 10) * (-1) + 48;
		n = (-1) * (n / 10);
		size -= 1;
	}
	while (n)
	{
		size--;
		new[size] = n % 10 + 48;
		n = n / 10;
	}
	return (new);
}
