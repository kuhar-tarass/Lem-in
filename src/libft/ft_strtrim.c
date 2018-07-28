/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 20:13:30 by tkuhar            #+#    #+#             */
/*   Updated: 2018/03/25 20:13:31 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (s && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	while (s && (s[j + 1] != '\0'))
		j++;
	while (s && ((s[j] == ' ' || s[j] == '\n' || s[j] == '\t') && j >= i))
		j--;
	new = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!new || !s)
		return (0);
	while (j - i >= 0)
	{
		new[k] = s[i];
		i++;
		k++;
	}
	new[k] = '\0';
	return (new);
}
