/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 11:38:00 by rmenegau          #+#    #+#             */
/*   Updated: 2015/12/04 16:04:21 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
			cpy[i] = (*f)(i, cpy[i]);
			i++;
		}
	}
	return (cpy);
}
