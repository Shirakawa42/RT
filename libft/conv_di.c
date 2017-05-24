/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 13:57:02 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/10 17:21:02 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	a_digit_count(long long nbr)
{
	int	i;

	i = 0;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i ? i : 1);
}

static char	*a_conv_ll(long long nbr, t_flag flag)
{
	char		*ret;
	int			sign;
	int			digits;

	digits = a_digit_count(nbr);
	sign = nbr < 0 ? -1 : 1;
	if (nbr == 0 && flag.prec == 0)
		digits = 0;
	ret = ft_strnew(digits + (sign == -1));
	while (digits--)
	{
		ret[digits + (sign == -1)] = sign * (nbr % 10) + '0';
		nbr /= 10;
	}
	if (sign == -1)
		ret[0] = '-';
	return (ret);
}

static char	*a_conv_di(char *ret, t_flag flag)
{
	int		len;
	int		sign;
	char	p;

	sign = ret[0] == '-';
	len = ft_strlen(ret) - sign;
	if (len < flag.prec)
		ptf_prec_nbr(&ret, flag, len, sign);
	len = ft_strlen(ret);
	p = ft_strchr(flag.fflg, '+') ? '+' : 0;
	if (p == 0)
		p = ft_strchr(flag.fflg, ' ') ? ' ' : 0;
	if (p && !sign)
	{
		ft_realloc_p(&ret, 1);
		ft_memmove(ret + 1, ret, len);
		ret[0] = p;
		sign = 1;
	}
	len = ft_strlen(ret);
	if (len < flag.chmp)
		ptf_chmp(&ret, flag, len, sign);
	return (ret);
}

char		*conv_di(va_list arg, t_flag flag)
{
	char		*ret;

	if (flag.type & 0x20)
		ret = a_conv_ll(va_arg(arg, ssize_t), flag);
	else if (flag.type & 0x10)
		ret = a_conv_ll(va_arg(arg, intmax_t), flag);
	else if (flag.type & 0x8)
		ret = a_conv_ll(va_arg(arg, long long), flag);
	else if (flag.type & 0x4)
		ret = a_conv_ll(va_arg(arg, long), flag);
	else if (flag.type & 0x2)
		ret = a_conv_ll((short)va_arg(arg, int), flag);
	else if (flag.type & 0x1)
		ret = a_conv_ll((char)va_arg(arg, int), flag);
	else
		ret = a_conv_ll(va_arg(arg, int), flag);
	ret = a_conv_di(ret, flag);
	return (ret);
}
