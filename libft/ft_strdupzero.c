/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupzero.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 18:41:47 by yismail           #+#    #+#             */
/*   Updated: 2017/05/18 18:42:16 by yismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdupzero(const char *src)
{
	char	*cpy;
	size_t	i;

	i = 0;
	if ((cpy = (char*)malloc(sizeof(char) * ft_strlen(src) + 1)) == 0)
		return (NULL);
	while (src[i])
    {
        cpy[i] = '\0';
        i++;
    }
	i = 0;
	while (src[i])
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
