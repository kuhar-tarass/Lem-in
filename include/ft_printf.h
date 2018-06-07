/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 20:48:24 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/23 19:15:08 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define CONV		k->typedata
# define WIDTH		k->width
# define PREC		k->precision
# define SPACE		k->space
# define ZERO		k->zero
# define LEFT		k->minus
# define SIGN		k->plus
# define HASH		k->hash
# define SMOD		k->size
# define DSIZE		k->sizex2
# define SKIP		k->skip
# include <stdio.h>
# include <stdarg.h>
# include <stdio.h>
# include "libft.h"

typedef struct		s_key
{
	char			typedata;
	int				width;
	int				precision;
	int				skip;
	char			space;
	char			zero;
	char			minus;
	char			plus;
	char			hash;
	char			sizex2;
	char			size;
}					t_key;

char				*ft_itoa_base(unsigned long int n, int base);
unsigned char		*ft_getcharw(wchar_t c);
char				*ft_getstrw(wchar_t const *s);
char				*ft_strinsert(char **dst, char *src, int index);

int					cccall(va_list ap, t_key *k);
int					ddicall(va_list ap, t_key *k);
int					uucall(va_list ap, t_key *k);
int					xopcall(va_list ap, t_key *k);

int					print_cc(int wchr, t_key *k);
int					print_ss(int *ws, t_key *k);
int					print_xo(unsigned long n, t_key *k);
int					print_di(long num, t_key *k);
int					print_u(unsigned long n, t_key *k);

void				spaaacesorzeeeros(char **s, t_key *k);
void				left(char **s, t_key *k);
void				addzero(char **s, t_key *k);

int					ft_printf(char *s, ...);

#endif
