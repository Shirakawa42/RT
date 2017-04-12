/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:35:03 by lvasseur          #+#    #+#             */
/*   Updated: 2017/02/23 20:15:26 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbrlen(int n)
{
	int		len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		h;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if ((str = (char*)malloc(sizeof(char) * (ft_nbrlen(n) + 1))) == 0)
		return (NULL);
	h = ft_nbrlen(n);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
		i++;
	}
	str[h] = '\0';
	while (i < h)
	{
		h--;
		str[h] = ((n % 10) + 48);
		n = n / 10;
	}
	return (str);
}
