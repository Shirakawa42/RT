/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:23:31 by lvasseur          #+#    #+#             */
/*   Updated: 2017/02/23 20:13:35 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		len(const char *str, int i, char c)
{
	int x;

	x = 0;
	while (str[i] != c && str[i])
	{
		x++;
		i++;
	}
	return (x);
}

static int		nbwd(char *str, char c)
{
	int i;
	int nbwords;

	i = 0;
	nbwords = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			nbwords++;
		while (str[i] != c && str[i])
			i++;
	}
	return (nbwords);
}

char			**ft_strsplit(const char *s, char c)
{
	char	**res;
	int		i;
	int		x;
	int		h;

	i = 0;
	x = 0;
	if (((res = malloc(sizeof(char*) * (nbwd((char*)s, c) + 1))) == 0) || !s)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			h = 0;
			if ((res[x] = (char*)malloc(sizeof(char) * len(s, i, c) + 1)) == 0)
				return (NULL);
			while (s[i] != c && s[i])
				res[x][h++] = s[i++];
			res[x++][h] = '\0';
		}
	}
	res[x] = NULL;
	return (res);
}
