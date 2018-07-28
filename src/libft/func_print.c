/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 17:35:23 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/12 21:54:31 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_cc(int wchr, t_key *k)
{
	char	*tmp;
	int		out;

	if (wchr == 0)
		WIDTH = WIDTH ? WIDTH - 1 : WIDTH;
	if (CONV == 'C' && MB_CUR_MAX > 1)
		tmp = (char *)ft_getcharw(wchr);
	else if (CONV == 'c' || (wchr < 255 && MB_CUR_MAX == 1))
	{
		tmp = ft_strnew(1);
		*tmp = wchr;
	}
	else
		return (-1);
	if (WIDTH)
		spaaacesorzeeeros(&tmp, k);
	if (LEFT)
		left(&tmp, k);
	if (CONV == 'c' || wchr == 0)
		out = write(1, tmp, (ft_strlen(tmp) + (wchr ? 0 : 1)));
	else
		out = write(1, tmp, ft_strlen(tmp));
	free(tmp);
	return (out);
}

int			print_ss(int *ws, t_key *k)
{
	char	*tmp;
	int		size;
	int		lens;
	char	*s;
	int		out;

	if (ws == 0)
		s = ft_strjoin(0, "(null)");
	else
		s = CONV == 'S' || SMOD == 'l' ? (char *)ft_getstrw(ws) :
			ft_strjoin(0, (char *)ws);
	if (s == 0)
		return (-1);
	lens = (int)ft_strlen(s);
	size = lens;
	if (PREC >= 0)
		size = ((lens - PREC) >= 0) ? PREC : lens;
	tmp = ft_strsub(s, 0, size);
	spaaacesorzeeeros(&tmp, k);
	if (LEFT)
		left(&tmp, k);
	out = write(1, tmp, ft_strlen(tmp));
	free(s);
	free(tmp);
	return (out);
}

int			print_xo(unsigned long n, t_key *k)
{
	char	*tmp;
	int		fuckzero;
	int		out;

	tmp = ft_itoa_base(n, CONV == 'o' || CONV == 'O' ? 8 : 16);
	fuckzero = (int)ft_strlen(tmp);
	if (PREC > fuckzero)
		addzero(&tmp, k);
	if (!PREC && !n)
		*tmp = 0;
	if ((HASH && ((PREC <= fuckzero && n) ||
		(!n && !PREC))) && (CONV == 'O' || CONV == 'o'))
		tmp = ft_strinsert(&tmp, "0", 0);
	if ((HASH && n && CONV != 'O' && CONV != 'o') || CONV == 'p')
		tmp = ft_strinsert(&tmp, "0x", 0);
	if (WIDTH - (int)ft_strlen(tmp) > 0)
		spaaacesorzeeeros(&tmp, k);
	if (LEFT == 1)
		left(&tmp, k);
	fuckzero = -1;
	while (tmp[++fuckzero] && CONV == 'X')
		tmp[fuckzero] = ft_toupper(tmp[fuckzero]);
	out = write(1, tmp, ft_strlen(tmp));
	free(tmp);
	return (out);
}

int			print_di(long num, t_key *k)
{
	char			*tmp;
	char			sign;
	unsigned long	n;
	int				out;

	n = num < 0 ? ~num + 1 : num;
	sign = num < 0 ? '-' : '+';
	SPACE = sign == '-' ? 0 : SPACE;
	tmp = ft_itoa_base(n, 10);
	if (PREC > (int)ft_strlen(tmp))
		addzero(&tmp, k);
	if (!PREC && n == 0)
		*tmp = 0;
	if (SIGN || sign == '-')
		tmp = ft_strinsert(&tmp, sign == '-' ? "-" : "+", 0);
	else if (SPACE == 1)
		tmp = ft_strinsert(&tmp, " ", 0);
	if (WIDTH - (int)ft_strlen(tmp) > 0)
		spaaacesorzeeeros(&tmp, k);
	if (LEFT == 1)
		left(&tmp, k);
	out = write(1, tmp, ft_strlen(tmp));
	free(tmp);
	return (out);
}

int			print_u(unsigned long n, t_key *k)
{
	char	*tmp;
	int		out;

	tmp = ft_itoa_base(n, 10);
	if (PREC > (int)ft_strlen(tmp))
		addzero(&tmp, k);
	if (!PREC && n == 0)
		*tmp = 0;
	if (WIDTH - (int)ft_strlen(tmp) > 0)
		spaaacesorzeeeros(&tmp, k);
	if (LEFT == 1)
		left(&tmp, k);
	out = write(1, tmp, ft_strlen(tmp));
	free(tmp);
	return (out);
}
