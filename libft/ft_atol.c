/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 11:14:13 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/10 11:19:41 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mp(char c)
{
	return (c == '-' || c == '+');
}

long		ft_atol(const char *str)
{
	long	result;

	result = 0;
	if ((mp(*str) && ft_isdigit(str[1])) || ft_isspace(*str))
		return (*str == '-' ? -ft_atoi(str + 1) : ft_atoi(str + 1));
	while (*str != '\0' && ft_isdigit(*str))
		result = (result * 10) + (*str++ - '0');
	return (result);
}
