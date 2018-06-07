/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstrw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 20:55:45 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/12 17:43:56 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_getstrw(wchar_t const *s)
{
	int		i;
	char	*result;
	char	*tmp;

	result = ft_strjoin("", 0);
	i = 0;
	tmp = 0;
	if (s)
		while (s[i])
		{
			tmp = (char *)ft_getcharw(s[i++]);
			if (tmp)
				result = ft_strinsert(&result, tmp, ft_strlen(result));
			else
			{
				free(result);
				return (0);
			}
			free(tmp);
		}
	return (result);
}
