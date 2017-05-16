/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:21:31 by lvasseur          #+#    #+#             */
/*   Updated: 2016/11/21 12:00:19 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (j < n && dest[j])
		j++;
	while (j + i < n - 1 && src[i] && n != 0)
	{
		dest[j + i] = src[i];
		i++;
	}
	if (j != n)
		dest[j + i] = '\0';
	return (j + ft_strlen(src));
}
