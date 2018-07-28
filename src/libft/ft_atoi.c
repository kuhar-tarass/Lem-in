/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 19:31:58 by tkuhar            #+#    #+#             */
/*   Updated: 2018/03/21 19:32:00 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAX 922337203685477580

static int	check(unsigned long long int result, char c, int nega)
{
	if (((result > MAX && c) ||
		(result == MAX && c > '7')) && nega == 1)
		return (-1);
	if (((result > MAX && c) ||
			(result == MAX && c > '8')) && nega == -1)
		return (0);
	return (1);
}

int			ft_atoi(const char *str)
{
	unsigned long long int	result;
	int						i;
	int						nega;

	result = 0;
	i = 0;
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\n' ||
	str[i] == '\t' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	nega = str[i] == '-' ? -1 : 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check(result, str[i], nega) != 1)
			return (check(result, str[i], nega));
		result = result * 10 + str[i] - '0';
		i++;
	}
	return ((int)result * nega);
}
