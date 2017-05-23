/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 06:12:16 by rmenegau          #+#    #+#             */
/*   Updated: 2016/02/25 19:51:29 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_realloc(void **ptr, size_t size, size_t new_size)
{
	void	*ret;

	ret = (char *)ft_memalloc(sizeof(char) * new_size);
	ft_memcpy(ret, *ptr, size < new_size ? size : new_size);
	if (*ptr)
		free(*ptr);
	*ptr = ret;
}
