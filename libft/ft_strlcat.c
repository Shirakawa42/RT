/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:21:46 by rmenegau          #+#    #+#             */
/*   Updated: 2015/12/04 14:17:37 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	while (i + j < size - 1 && src[j])
	{
		dst[i + j] = src[j];
		if (i + j++ + 1 == size - 1)
			dst[i + j] = '\0';
	}
	return (i + ft_strlen(src));
}
