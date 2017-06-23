/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utf8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 02:27:32 by rmenegau          #+#    #+#             */
/*   Updated: 2016/05/10 16:42:25 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				a_len(unsigned int const c)
{
	if (c >= 0x80000000)
		return (0);
	return (1 + (c >= 0x80) + (c >= 0x800) + (c >= 0x10000) +
			(c >= 0x200000) + (c >= 0x4000000));
}

static unsigned char	a_octet(unsigned len, unsigned pos)
{
	if (pos & 0xfffffff8)
		return (0);
	if (8 - pos < len)
		len = 8 - pos;
	return (0xff >> (8 - len)) << (8 - len - pos);
}

static void				a_split(char *ret, unsigned int c, int len)
{
	int	i;

	i = len - 1;
	while (i > 0)
	{
		ret[i] = 0x80 + (c & 0x3f);
		c >>= 6;
		i--;
	}
	ret[i] = a_octet(len, 0) + (c & a_octet(8 - len - 1, len + 1));
}

char					*split_utf8(unsigned int c)
{
	char	*ret;
	int		len;

	len = a_len(c);
	ret = len ? ft_strnew(len) : NULL;
	if (len == 1)
		ret[0] = c & 0x7f;
	else if (len)
		a_split(ret, c, len);
	return (ret);
}
