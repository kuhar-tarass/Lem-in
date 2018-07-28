/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 18:09:56 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/19 14:41:04 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*fresh;
	int		i;
	int		s1l;
	int		s2l;

	s1l = 0;
	s2l = 0;
	if (s1)
		s1l = ft_strlen(s1);
	if (s2)
		s2l = ft_strlen(s2);
	fresh = (char *)malloc(sizeof(char) * (s1l + s2l + 1));
	if (fresh == 0)
		return (0);
	i = 0;
	while (s1 && *s1 != '\0')
		fresh[i++] = *s1++;
	while (s2 && *s2 != '\0')
		fresh[i++] = *s2++;
	fresh[i] = '\0';
	return (fresh);
}
