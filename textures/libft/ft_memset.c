/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:18:35 by lvasseur          #+#    #+#             */
/*   Updated: 2016/11/09 13:13:21 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*truc;
	size_t				i;

	i = 0;
	truc = (unsigned char*)s;
	while (i < n)
		truc[i++] = (unsigned char)c;
	return (s);
}
