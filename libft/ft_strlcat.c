/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 14:14:17 by tkuhar            #+#    #+#             */
/*   Updated: 2018/03/24 14:14:18 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlength;
	size_t	slength;
	int		i;

	dlength = ft_strlen(dst);
	slength = ft_strlen(src);
	i = dstsize - dlength - 1;
	if (dstsize < dlength)
		return (ft_strlen(src) + dstsize);
	while (i > 0)
	{
		if (!src[dstsize - dlength - 1 - i])
			break ;
		dst[dstsize - 1 - i] = src[dstsize - dlength - 1 - i];
		i--;
	}
	dst[dstsize - 1 - i] = '\0';
	return (dlength + ft_strlen(src));
}
