/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcharw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:45:26 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/11 16:11:31 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <locale.h>

unsigned char	*ft_getcharw(wchar_t c)
{
	unsigned char symb[5];

	ft_bzero(symb, 5);
	if (c < 128)
		symb[0] = c;
	else if (c < 2048)
	{
		symb[0] = (c >> 6 & 31) | 192;
		symb[1] = (c & 63) | 128;
	}
	else if (c < 65536)
	{
		symb[0] = ((c >> 12) & 15) | 224;
		symb[1] = ((c >> 6) & 63) | 128;
		symb[2] = (c & 63) | 128;
	}
	else
	{
		symb[0] = (c >> 18 & 7) | 224;
		symb[1] = (c >> 12 & 63) | 128;
		symb[2] = (c >> 6 & 63) | 128;
		symb[3] = (c & 63) | 128;
	}
	return ((c > 255 && MB_CUR_MAX == 1) ? 0 :
		(unsigned char *)ft_strsub((char *)symb, 0, 4));
}
