/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:23:49 by lvasseur          #+#    #+#             */
/*   Updated: 2016/11/21 14:04:31 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	tmp;
	size_t	i;
	char	*dest2;
	char	*src2;

	dest2 = (char*)dest;
	src2 = (char*)src;
	i = 0;
	if (dest > src)
	{
		while (len)
		{
			len--;
			dest2[len] = src2[len];
		}
	}
	while (i < len)
	{
		tmp = src2[i];
		dest2[i] = tmp;
		i++;
	}
	return (dest2);
}
