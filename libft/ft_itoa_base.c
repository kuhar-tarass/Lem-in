/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 16:44:34 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/11 16:00:03 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_base(unsigned long int n, int base)
{
	char	buf[65];
	char	*ret;
	int		i;
	int		j;

	ft_bzero(buf, 65);
	j = 0;
	*buf = n == 0 ? 48 : 0;
	while (n > 0)
	{
		buf[j++] = (n % base < 10 ? n % base : n % base + 39) + 48;
		n /= base;
	}
	i = ft_strlen(buf);
	j = i;
	if ((ret = malloc(sizeof(char) * (i + 1))))
	{
		ft_bzero(ret, i + 1);
		while (i--)
			ret[j - i - 1] = buf[i];
	}
	return (ret);
}
