/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:56:34 by tkuhar            #+#    #+#             */
/*   Updated: 2018/06/01 15:23:23 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		truflag(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' ||
		c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U' ||
		c == 'x' || c == 'X' || c == 'c' || c == 'C' || c == '%')
		return (1);
	return (0);
}

static int		flag_parse(char *s, t_key *k)
{
	int	i;

	SPACE = 0;
	ZERO = 0;
	LEFT = 0;
	SIGN = 0;
	HASH = 0;
	i = 0;
	while (s[++i] == ' ' || s[i] == '0' || s[i] == '-' || s[i] == '+' || s[i] == '#')
	{
		SPACE = (SPACE || s[i] == ' ') ? 1 : 0;
		LEFT = (LEFT || s[i] == '-') ? 1 : 0;
		ZERO = (ZERO || s[i] == '0') && !LEFT ? 1 : 0;
		SIGN = SIGN || s[i] == '+' ? 1 : 0;
		HASH = HASH || s[i] == '#' ? 1 : 0;
	}
	return (i);
}

static t_key	*arg_parse(char *s)
{
	int		i;
	t_key	*k;

	k = malloc(sizeof(t_key));
	WIDTH = 0;
	PREC = -1;
	SMOD = 0;
	i = flag_parse(s, k);
	while (s[i] >= '0' && s[i] <= '9')
		WIDTH = WIDTH * 10 + s[i++] - 48;
	if (s[i] == '.' && !(PREC = 0))
		while (s[++i] >= '0' && s[i] <= '9')
			PREC = PREC * 10 + s[i] - 48;
	if (s[i] == 'h' || s[i] == 'l' || s[i] == 'z' || s[i] == 'j')
		SMOD = s[i++];
	DSIZE = (SMOD && s[i] == SMOD) ? 1 : 0;
	CONV = s[i + DSIZE];
	SKIP = i + (CONV ? 1 : 0) + DSIZE;
	return (k);
}

static int		outstring(va_list ap, t_key *k)
{
	int		tmp;
	char	other;

	tmp = 0;
	if (!truflag(CONV))
	{
		other = CONV;
		CONV = 'c';
		tmp = print_cc(other, k);
	}
	else if (CONV == 'S' || CONV == 's')
		tmp = print_ss(va_arg(ap, int *), k);
	else if (CONV == 'c' || CONV == 'C' || CONV == '%')
		tmp = cccall(ap, k);
	else if (CONV == 'x' || CONV == 'X' ||
		CONV == 'p' || CONV == 'o' || CONV == 'O')
		tmp = xopcall(ap, k);
	else if (CONV == 'i' || CONV == 'd' || CONV == 'D')
		tmp = ddicall(ap, k);
	else if (CONV == 'u' || CONV == 'U')
		tmp = uucall(ap, k);
	free(k);
	return (tmp);
}

int				ft_printf(char *s, ...)
{
	va_list			ap;
	int				i;
	char			*symb;
	int				count;
	t_key			*k;

	va_start(ap, s);
	count = 0;
	while (1)
	{
		symb = ft_strchr(s, '%');
		if (!symb)
			break ;
		count += write(1, s, symb - s);
		k = arg_parse(symb);
		s = symb + SKIP;
		if ((i = outstring(ap, k)) < 0)
			break ;
		count += i;
	}
	va_end(ap);
	if (i == -1)
		return (-1);
	count += write(1, s, ft_strlen((char*)s));
	return (count);
}