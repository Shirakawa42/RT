/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 18:23:07 by rmenegau          #+#    #+#             */
/*   Updated: 2015/12/07 10:59:12 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	aux_nbmots(char const *s, char c)
{
	size_t	i;
	size_t	nbmots;

	i = 0;
	nbmots = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			nbmots++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nbmots);
}

static size_t	aux_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	mot;

	if (!s)
		return (NULL);
	tab = (char **)ft_memalloc(sizeof(char *) * (aux_nbmots(s, c) + 1));
	i = 0;
	mot = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			tab[mot] = ft_strsub(s, i, aux_len(s + i, c));
			mot++;
		}
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	tab[mot] = NULL;
	return (tab);
}
