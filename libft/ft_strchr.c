/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:27:47 by rmenegau          #+#    #+#             */
/*   Updated: 2016/01/12 13:42:58 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if ((char)c == '\0')
		return (((char *)s) + ft_strlen(s));
	while (s[i])
		if (s[i++] == (char)c)
			return (((char *)s) + i - 1);
	return (NULL);
}
