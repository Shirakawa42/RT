/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 10:32:13 by rmenegau          #+#    #+#             */
/*   Updated: 2016/02/23 12:25:55 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *temp;

	if (!s1)
		return (NULL);
	temp = ft_memalloc(ft_strlen(s1) + 1);
	return (ft_strcpy(temp, s1));
}
