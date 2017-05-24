/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 15:12:44 by rmenegau          #+#    #+#             */
/*   Updated: 2016/01/12 16:18:09 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	a_conv(int digit)
{
	return (ft_isdigit(digit + '0') ? digit + '0' : digit + 'A' - 10);
}

char		*ft_itoa_b(int n, int b)
{
	size_t	pow;
	char	*r;

	if (b > 16 || b < 2)
		return (0);
	pow = n == 0 ? 1 : 0;
	while (n / ft_power(b, pow) != 0)
		pow++;
	r = ft_memalloc(n < 0 ? pow + 2 : pow + 1);
	if (n < 0)
		r[0] = '-';
	while (pow-- != 0)
	{
		r[pow + (n < 0 ? 1 : 0)] = a_conv((n < 0 ? -(n % b) : n % b));
		n /= b;
	}
	return (r);
}
