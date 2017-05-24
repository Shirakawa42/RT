/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 11:28:06 by rmenegau          #+#    #+#             */
/*   Updated: 2015/12/04 14:19:56 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*cpy;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	cpy = ft_strnew(ft_strlen(s));
	if (cpy != NULL)
	{
		ft_strcpy(cpy, s);
		while (cpy[i])
		{
			cpy[i] = (*f)(cpy[i]);
			i++;
		}
	}
	return (cpy);
}
