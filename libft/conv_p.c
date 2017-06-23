/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 14:50:50 by rmenegau          #+#    #+#             */
/*   Updated: 2016/05/10 16:41:14 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	a_conv(int n)
{
	return (n < 10 ? '0' + n : 'a' + n - 10);
}

static char	*a_conv_p(unsigned long long nbr, t_flag flag)
{
	char		*ret;

	ret = ft_strnew(0);
	if (flag.prec != 0 || nbr != 0)
	{
		ft_realloc_p(&ret, 1);
		ret[0] = a_conv(nbr & 0xf);
		nbr >>= 4;
	}
	while (nbr)
	{
		ft_realloc_p(&ret, 1);
		ft_memmove(ret + 1, ret, ft_strlen(ret));
		ret[0] = a_conv(nbr & 0xf);
		nbr >>= 4;
	}
	return (ret);
}

char		*conv_p(va_list arg, t_flag flag)
{
	char	*ret;
	int		len;

	ret = a_conv_p(va_arg(arg, unsigned long long), flag);
	len = ft_strlen(ret);
	if (len < flag.prec)
	{
		ft_realloc_p(&ret, flag.prec);
		ft_memmove(ret + flag.prec - len, ret, len);
		ft_memset(ret, '0', flag.prec - len);
	}
	len = ft_strlen(ret);
	ft_realloc_p(&ret, 2);
	ft_memmove(ret + 2, ret, len);
	ret[0] = '0';
	ret[1] = 'x';
	len += 2;
	if (len < flag.chmp)
		ptf_chmp(&ret, flag, len, 2);
	return (ret);
}
