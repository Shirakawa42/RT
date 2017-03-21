/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 12:57:25 by lvasseur          #+#    #+#             */
/*   Updated: 2017/02/23 20:15:22 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;
	char	*mem2;

	if ((mem = (void*)malloc(sizeof(void) * size)) == NULL)
		return (NULL);
	mem2 = (char*)mem;
	size = size - 1;
	while (size != (size_t)-1)
		mem2[size--] = 0;
	return (mem);
}
