/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 18:12:56 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/08 14:48:45 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *temp;

	temp = ft_memalloc(len);
	ft_memcpy(temp, src, len);
	ft_memcpy(dst, temp, len);
	ft_strdel(&temp);
	return (dst);
}
