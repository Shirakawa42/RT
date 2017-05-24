/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:47:36 by rmenegau          #+#    #+#             */
/*   Updated: 2015/11/25 13:37:59 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			temp = (char *)(s + i);
		i++;
	}
	return (c == 0 ? (char *)(s + i) : temp);
}
