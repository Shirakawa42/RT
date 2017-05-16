/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:56:29 by lvasseur          #+#    #+#             */
/*   Updated: 2016/11/16 16:30:48 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	const unsigned char	*s1;
	unsigned char		*s2;
	unsigned char		h;

	h = (unsigned char)c;
	s1 = (const unsigned char*)src;
	s2 = (unsigned char*)dest;
	while (n > 0)
	{
		if (*s1 == h)
		{
			*s2 = *s1;
			dest++;
			return (dest);
		}
		*s2 = *s1;
		s1++;
		s2++;
		n--;
		dest++;
	}
	return (NULL);
}
