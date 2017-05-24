/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_oux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 04:37:17 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/08 15:51:56 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	a_conv_base(int n, int maj)
{
	if (n < 10)
		return (n + '0');
	return (maj ? n + 'A' - 10 : n + 'a' - 10);
}

static int	a_digit_count(unsigned long long nbr, int base)
{
	int	i;

	i = 0;
	while (nbr)
	{
		nbr /= base;
		i++;
	}
	return (i ? i : 1);
}

static char	*a_conv_ll(unsigned long long nbr, t_flag flag)
{
	char		*ret;
	int			base;
	int			digits;

	if (flag.conv == 'u' || flag.conv == 'b')
		base = flag.conv == 'b' ? 2 : 10;
	else
		base = flag.conv == 'o' ? 8 : 16;
	digits = a_digit_count(nbr, base);
	if (flag.prec == 0 && nbr == 0)
		digits = 0;
	ret = ft_strnew(digits);
	while (digits--)
	{
		ret[digits] = a_conv_base(nbr % base, flag.conv == 'X');
		nbr /= base;
	}
	return (ret);
}

static char	*a_conv_oux(char *ret, t_flag flag)
{
	int	len;
	int	tmp;

	len = ft_strlen(ret);
	tmp = ret[0] == '0';
	if (len < flag.prec)
		ptf_prec_nbr(&ret, flag, len, 0);
	len = ft_strlen(ret);
	if (ft_strchr(flag.fflg, '#') && flag.conv != 'u' && flag.conv != 'b' &&
			!tmp && (len || flag.conv == 'o'))
	{
		if (ret[0] != '0' || flag.conv != 'o')
		{
			tmp = flag.conv == 'o' ? 1 : 2;
			ft_realloc_p(&ret, tmp);
			ft_memmove(ret + tmp, ret, len);
			ft_strncpy(ret, "0x", tmp);
			if (flag.conv == 'X')
				ret[1] = 'X';
		}
	}
	tmp = ft_strlen(ret) - len;
	if (len + tmp < flag.chmp)
		ptf_chmp(&ret, flag, len + tmp, tmp);
	return (ret);
}

char		*conv_oux(va_list arg, t_flag flag)
{
	char		*ret;

	if (flag.type & 0x20)
		ret = a_conv_ll(va_arg(arg, size_t), flag);
	else if (flag.type & 0x10)
		ret = a_conv_ll(va_arg(arg, uintmax_t), flag);
	else if (flag.type & 0x8)
		ret = a_conv_ll(va_arg(arg, unsigned long long), flag);
	else if (flag.type & 0x4)
		ret = a_conv_ll(va_arg(arg, unsigned long), flag);
	else if (flag.type & 0x2)
		ret = a_conv_ll((unsigned short)va_arg(arg, int), flag);
	else if (flag.type & 0x1)
		ret = a_conv_ll((unsigned char)va_arg(arg, int), flag);
	else
		ret = a_conv_ll(va_arg(arg, unsigned int), flag);
	if (ret[0] == '0' && flag.prec == 0 && !ft_strchr(flag.fflg, '#'))
		ft_bzero(ret, 1);
	ret = a_conv_oux(ret, flag);
	return (ret);
}
