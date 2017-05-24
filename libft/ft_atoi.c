/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:34:18 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/10 11:18:58 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mp(char c)
{
	return (c == '-' || c == '+');
}

int			ft_atoi(const char *str)
{
	int	result;

	result = 0;
	if ((mp(*str) && ft_isdigit(str[1])) || ft_isspace(*str))
		return (*str == '-' ? -ft_atoi(str + 1) : ft_atoi(str + 1));
	while (*str != '\0' && ft_isdigit(*str))
		result = (result * 10) + (*str++ - '0');
	return (result);
}
