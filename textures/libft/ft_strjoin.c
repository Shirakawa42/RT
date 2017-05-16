/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:49:05 by lvasseur          #+#    #+#             */
/*   Updated: 2017/02/23 20:14:06 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 && s2)
	{
		if ((str = (char*)malloc(sizeof(char) * (ft_strlen(s1) +
						ft_strlen(s2) + 1))) == 0)
			return (NULL);
		i = 0;
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		j = 0;
		while (s2[j])
			str[i++] = s2[j++];
		str[i] = '\0';
		return (str);
	}
	else
		return (NULL);
}
