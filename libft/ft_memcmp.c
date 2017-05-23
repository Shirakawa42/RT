/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 09:37:41 by rmenegau          #+#    #+#             */
/*   Updated: 2015/12/04 14:16:46 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (((char *)s1)[i] == ((char *)s2)[i] && i < n)
		i++;
	i = i == n ? i - 1 : i;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
