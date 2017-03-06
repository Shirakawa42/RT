/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:12:51 by lvasseur          #+#    #+#             */
/*   Updated: 2016/11/16 16:55:44 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	g;

	g = (unsigned char)c;
	i = 0;
	str = (unsigned char*)s;
	while (i < n)
	{
		if (str[i] == g)
		{
			while (i > 0)
			{
				s++;
				i--;
			}
			return ((void*)s);
		}
		i++;
	}
	return (NULL);
}
