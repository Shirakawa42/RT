/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:19:22 by lvasseur          #+#    #+#             */
/*   Updated: 2016/11/14 16:51:26 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*t;
	int		i;
	int		j;

	t = (char*)s;
	i = ft_strlen(s);
	j = i;
	while (i != 0)
	{
		t++;
		i--;
	}
	while (i <= j)
	{
		if (*t == c)
			return (t);
		t--;
		i++;
	}
	return (NULL);
}
