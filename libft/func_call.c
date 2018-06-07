/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_call.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 17:29:03 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/12 21:55:57 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		cccall(va_list ap, t_key *k)
{
	int tmp;

	if (CONV == '%' && (CONV = 'c'))
		tmp = print_cc('%', k);
	else if (SMOD == 'h' && DSIZE && CONV == 'c')
		tmp = print_cc((char)va_arg(ap, int), k);
	else if (SMOD == 'h')
		tmp = print_cc((short)va_arg(ap, int), k);
	else
	{
		if (SMOD == 'l' && CONV == 'c')
			CONV = 'C';
		tmp = print_cc(va_arg(ap, int), k);
	}
	return (tmp);
}

int		ddicall(va_list ap, t_key *k)
{
	int	tmp;

	if (SMOD == 'l' || SMOD == 'z' || SMOD == 'j' || CONV == 'D')
		tmp = print_di(va_arg(ap, long), k);
	else if (SMOD == 'h' && DSIZE)
		tmp = print_di((char)va_arg(ap, int), k);
	else if (SMOD == 'h')
		tmp = print_di((short)va_arg(ap, int), k);
	else
		tmp = print_di((long)va_arg(ap, int), k);
	return (tmp);
}

int		uucall(va_list ap, t_key *k)
{
	int	tmp;

	if (SMOD == 'l' || SMOD == 'j' || CONV == 'U' || SMOD == 'z')
		tmp = print_u((unsigned long)va_arg(ap, size_t), k);
	else if (SMOD == 'h' && DSIZE)
		tmp = print_u((char unsigned)va_arg(ap, unsigned), k);
	else if (SMOD == 'h')
		tmp = print_u((short unsigned)va_arg(ap, unsigned), k);
	else
		tmp = print_u((unsigned)va_arg(ap, size_t), k);
	return (tmp);
}

int		xopcall(va_list ap, t_key *k)
{
	int	tmp;

	if (SMOD == 'l' || SMOD == 'z' || SMOD == 'j' || CONV == 'O' || CONV == 'p')
		tmp = print_xo(va_arg(ap, size_t), k);
	else if (SMOD == 'h' && DSIZE)
		tmp = print_xo((unsigned char)va_arg(ap, size_t), k);
	else if (SMOD == 'h')
		tmp = print_xo((unsigned short)va_arg(ap, size_t), k);
	else
		tmp = print_xo((unsigned long)va_arg(ap, unsigned int), k);
	return (tmp);
}
