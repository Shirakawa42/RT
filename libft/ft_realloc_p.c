/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:45:32 by rmenegau          #+#    #+#             */
/*   Updated: 2016/01/14 13:23:14 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc_p(char **s, size_t new_size)
{
	char	*temp;

	if (s == NULL)
		return (NULL);
	if (*s)
	{
		temp = *s;
		*s = ft_strnew(ft_strlen(temp) + new_size);
		ft_strcpy(*s, temp);
		free(temp);
	}
	else
		*s = ft_strnew(ft_strlen(*s) + new_size);
	return (*s);
}
