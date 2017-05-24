/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:27:20 by rmenegau          #+#    #+#             */
/*   Updated: 2015/12/04 16:07:30 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (i < n && s1[i] == s2[i] && s1[i])
		i++;
	i = i == n ? i - 1 : i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
