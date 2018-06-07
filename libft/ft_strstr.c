/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 19:43:45 by tkuhar            #+#    #+#             */
/*   Updated: 2018/03/21 19:43:47 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *haystack, char *needle)
{
	int i;
	int j;

	i = 0;
	if (needle[0] == '\0')
		return (haystack);
	while (haystack[i] != '\0')
	{
		j = 0;
		if (haystack[i] == needle[0])
			while (haystack[i + j] == needle[j])
			{
				if (needle[j + 1] == '\0')
					return (&haystack[i]);
				j++;
			}
		i++;
	}
	return (0);
}
