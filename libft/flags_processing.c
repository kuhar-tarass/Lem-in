/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 17:40:06 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/12 17:59:30 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		spaaacesorzeeeros(char **s, t_key *k)
{
	int		f;
	char	*buf;
	int		lens;

	lens = (int)ft_strlen(*s);
	f = (((WIDTH - lens) > 0) ? (WIDTH - lens) : 0);
	buf = ft_strnew(f + 1);
	buf = ft_memset(buf, (PREC == -1 && ZERO) ? '0' : ' ', f);
	if (CONV == 'x' || CONV == 'X' || CONV == 'p')
		*s = ft_strinsert(s, buf, ZERO && (HASH || CONV == 'p') ? 2 : 0);
	else if (CONV == 'o' || CONV == 'O')
		*s = ft_strinsert(s, buf, HASH && ZERO ? 1 : 0);
	else if (CONV == 'd' || CONV == 'i')
		*s = ft_strinsert(s, buf, (**s == ' ' || **s == '-' || **s == '+')
			&& ZERO ? 1 : 0);
	else
		*s = ft_strinsert(s, buf, 0);
	free(buf);
	return ;
}

void		left(char **s, t_key *k)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while ((*s)[i] == ' ')
		i++;
	if (SPACE == 1 && i && SIGN == 0 && CONV != '%')
		i--;
	tmp = ft_strsub(*s, i, ft_strlen(&(*s)[i]));
	tmp2 = ft_strsub(*s, 0, i);
	tmp = ft_strinsert(&tmp, tmp2, ft_strlen(tmp));
	free(tmp2);
	free(*s);
	*s = tmp;
}

void		addzero(char **s, t_key *k)
{
	int		size;
	char	*zeros;

	size = PREC - (int)ft_strlen(*s);
	zeros = ft_strnew(size + 1);
	zeros = ft_memset(zeros, '0', size);
	*s = ft_strinsert(s, zeros, 0);
	free(zeros);
}
