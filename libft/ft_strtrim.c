/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 17:49:22 by rmenegau          #+#    #+#             */
/*   Updated: 2015/12/07 10:56:00 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	aux_espace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char		*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	start;

	if (!s)
		return (NULL);
	start = 0;
	while (aux_espace(s[start]))
		start++;
	len = ft_strlen(s + start);
	while (aux_espace(s[start + len - 1]) && len)
		len--;
	return (ft_strsub(s, start, len));
}
